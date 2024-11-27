#include "PreCompile.h"
#include "UIBox.h"
#include "ContentsEnum.h"
#include "UIText.h"

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

	for (AUIText* UIText : UITextes)
	{
		UIText->SetActive(false);
	}
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
	BoxRenderer->SetAlphafloat(1.0f);
	MaxLineCount = static_cast<int>(UITextes.size());
}

void AUIBox::StartEnd()
{
}

void AUIBox::Show(float DeltaTime)
{
	FVector2D Location = GetActorLocation() - FVector2D(250, 70);
	Location += FVector2D(0, CurLineCount * 40);

	CurTime += DeltaTime;

	if (CurTime > Time)
	{

		UITextes[CurLineCount]->SetActive(true);
		UITextes[CurLineCount]->ShowUIText(0.0f);
		UITextes[CurLineCount]->SetActorLocation(Location);

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
	default:
		break;
	}

	CurState = State;
}
