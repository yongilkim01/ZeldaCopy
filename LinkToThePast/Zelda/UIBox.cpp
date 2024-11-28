#include "PreCompile.h"
#include "UIBox.h"
#include "ContentsEnum.h"
#include "UIText.h"
#include "EventManager.h"

#include <EngineCore/SpriteRenderer.h>

AUIBox::AUIBox()
{
	BoxRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BoxRenderer->SetSprite("UIBox2.png");
	FVector2D BoxScale = BoxRenderer->SetSpriteScale(1.0f);
	BoxRenderer->SetComponentLocation(FVector2D::ZERO);
	BoxRenderer->SetComponentScale(BoxScale);
	BoxRenderer->SetOrder(ERenderOrder::UI);
	BoxRenderer->SetCameraEffect(false);
	BoxRenderer->SetAlphafloat(0.0f);
}

AUIBox::~AUIBox()
{
}

void AUIBox::BeginPlay()
{
	Super::BeginPlay();

	ChangeState(EUIBoxState::SHOW);

}

void AUIBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (CurState)
	{
	case EUIBoxState::SHOW:
		Show(DeltaTime);
		break;
	case EUIBoxState::END:
		End(DeltaTime);
		break;
	case EUIBoxState::SKIP:
		Skip(DeltaTime);
		break;
	default:
		break;
	}

}

void AUIBox::CreateUIText(std::string_view StrValue, float Time)
{
	// s20_02
	AUIText* NewUIText = GetWorld()->SpawnActor<AUIText>();
	NewUIText->BeginPlayUIText(StrValue, Time);
	NewUIText->SetActive(false);
	UITextes.push_back(NewUIText);
}

void AUIBox::CreateUIText(const std::vector<std::string>& StrValues, float Time)
{
	this->Time = Time;

	for (std::string StrValue : StrValues)
	{
		AUIText* NewUIText = GetWorld()->SpawnActor<AUIText>();
		NewUIText->BeginPlayUIText(StrValue, 0.0f);
		NewUIText->SetActive(false);
		UITextes.push_back(NewUIText);
	}
}

void AUIBox::SetUIText(std::string_view StrValue, int Index, float Time)
{
	if (Index < UITextes.size()) 
	{
		UITextes[Index]->BeginPlayUIText(StrValue, Time);
	}
}

void AUIBox::SetUIText(const std::vector<std::string>& StrValues, int Index, float Time)
{
	if (Index < UITextes.size()) 
	{
		UITextes[Index]->BeginPlayUIText(StrValues, Time);
	}
}


void AUIBox::HideUI()
{
	BoxRenderer->SetAlphafloat(0.0f);

	for (size_t i = 0; i < UITextes.size(); i++)
	{
		UITextes[i]->SetActive(false);
	}
	MaxLineCount = 0;
	CurLineCount = 0;
}

void AUIBox::SetTextsCount(int Count)
{
	for (int i = 0; i < Count; i++)
	{
		CreateUIText("");
	}
}

void AUIBox::StartShow()
{
	UEventManager::GetInstance().SetEventPause(true);
	BoxRenderer->SetAlphafloat(IsShowFrame);
	MaxLineCount = static_cast<int>(UITextes.size());
}

void AUIBox::StartEnd()
{
	TimeEventer.PushEvent(1.0f, [this]()
		{
			UEventManager::GetInstance().SetEventPause(false);
			BoxRenderer->SetAlphafloat(0.0f);
			for (size_t i = 0; i < UITextes.size(); i++)
			{
				UITextes[i]->SetActive(false);
			}
			MaxLineCount = 0;
			CurLineCount = 0;
		}
	);
}

void AUIBox::StartSkip()
{
	for (size_t i = 0; i < MaxLineCount; i++)
	{
		UITextes[i]->SetActive(false);
	}

	FVector2D Location = GetActorLocation() - FVector2D(250, 70);

	//int Index = 0;

	for (size_t i = MaxLineCount - 3; i < MaxLineCount; i++)
	{
		UITextes[i]->SetActive(true);
		UITextes[i]->ShowUIText(0.0f);
		UITextes[i]->SetActorLocation(Location);
		Location += FVector2D(0.0f, 35.0f);
		//UITextes[i]->ChangeState(EUITExtState::IDLE);
	}
}

void AUIBox::Show(float DeltaTime)
{
	FVector2D Location = GetActorLocation() - FVector2D(250, 70);
	
	if (CurLineCount <= 2)
	{
		Location += FVector2D(0, CurLineCount * 35);
	}
	else
	{
		Location += FVector2D(0, 2 * 35);
	}
	//Location += FVector2D(0, CurLineCount * 35);

	CurTime += DeltaTime;

	if (CurTime > Time)
	{

		UITextes[CurLineCount]->SetActive(true);
		UITextes[CurLineCount]->ShowUIText(0.0f);
		UITextes[CurLineCount]->SetActorLocation(Location);

		
		if (CurLineCount >= 3)
		{
			UITextes[CurLineCount - 3]->SetActive(false);
			UITextes[CurLineCount - 3]->HideUIText(0.0f);

			UITextes[CurLineCount - 2]->ChangeState(EUITExtState::MOVE);
			UITextes[CurLineCount - 1]->ChangeState(EUITExtState::MOVE);
		}

		CurTime = 0.0f;
		++CurLineCount;

		if (CurLineCount == MaxLineCount)
		{
			ChangeState(EUIBoxState::END);
		}

	}

}

void AUIBox::End(float DeltaTime)
{
}

void AUIBox::Skip(float DeltaTime)
{
}

void AUIBox::ChangeState(EUIBoxState State)
{
	if (State == CurState) return;

	switch (State)
	{
	case EUIBoxState::SHOW:
		StartShow();
		break;
	case EUIBoxState::END:
		StartEnd();
		break;
	case EUIBoxState::SKIP:
		StartSkip();
		break;
	default:
		break;
	}

	CurState = State;
}
