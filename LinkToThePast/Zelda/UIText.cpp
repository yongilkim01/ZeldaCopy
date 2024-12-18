#include "PreCompile.h"
#include "UIText.h"
#include "ContentsEnum.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineMath.h>

AUIText::AUIText()
{
}

AUIText::~AUIText()
{
}

void AUIText::BeginPlay()
{
	Super::BeginPlay();

}

void AUIText::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (CurState)
	{
	case EUITExtState::IDLE:
		Idle(DeltaTime);
		break;
	case EUITExtState::MOVE:
		Move(DeltaTime);
		break;
	default:
		break;
	}

}

void AUIText::BeginPlayUIText(std::string_view StrValue, float Time)
{
	this->Time = Time;
	this->StrValue = StrValue;

	Reserve(static_cast<int>(this->StrValue.size()));

	this->CurCount = 0;

	for (size_t i = 0; i < this->StrValue.size(); i++)
	{
		char CharValue = this->StrValue[i];
		int TextIndex = ConvertCharToIndex(CharValue);
		TextRendereres[i]->SetSprite("UIText.png", TextIndex);
		TextRendereres[i]->SetSpriteScale(0.75f);
		TextRendereres[i]->SetComponentLocation(FVector2D( TextSize.X * i, TextSize.Y ));
		TextRendereres[i]->SetActive(false);
	}
}

void AUIText::BeginPlayUIText(const AUIText* UIText)
{
	this->StrValue = UIText->GetUIStrValue();
	this->Time = UIText->GetTime();

	Reserve(static_cast<int>(this->StrValue.size()));

	CurCount = 0;
	for (size_t i = 0; i < this->StrValue.size(); i++)
	{
		char CharValue = this->StrValue[i];
		int TextIndex = ConvertCharToIndex(CharValue);
		TextRendereres[i]->SetSprite(UIText->TextRendereres[i]->GetCurSpriteName(), TextIndex);
		TextRendereres[i]->SetSpriteScale();
		TextRendereres[i]->SetComponentLocation(FVector2D(TextSize.X * i, TextSize.Y));
		TextRendereres[i]->SetActive(false);
	}
}

void AUIText::BeginPlayUIText(const std::vector<std::string>& StrValues, float Time)
{
	this->Time = Time;
	this->StrValue.clear();

	for (const std::string& Str : StrValues)
	{
		StrValue += Str;
	}

	Reserve(static_cast<int>(this->StrValue.size()));

	CurCount = 0;
	int Index = 0;

	for (size_t i = 0; i < StrValues.size(); i++)
	{
		const std::string& StrVal = StrValues[i];

		for (size_t j = 0; j < StrVal.size(); j++)
		{
			char CharValue = StrVal[j];
			int TextIndex = ConvertCharToIndex(CharValue);
			TextRendereres[Index]->SetSprite("UIText.png", TextIndex);
			TextRendereres[Index]->SetSpriteScale();
			TextRendereres[Index]->SetComponentLocation(FVector2D(TextSize.X * Index, TextSize.Y));
			TextRendereres[Index]->SetActive(false);
			Index++;
		}
	}
}

void AUIText::ShowUIText(float DeltaTime)
{
	int Size = static_cast<int>(StrValue.size());

	for (size_t i = 0; i < Size; i++)
	{
		TextRendereres[i]->SetActive(false);
	}

	if (0.0f == Time) 
	{
		CurCount = Size;
	}

	CurTime += DeltaTime;

	if (CurTime > Time) 
	{
		++CurCount;
		CurTime = 0.0f;
	}

	if (CurCount >= Size) 
	{
		CurCount = Size;
		Time = 0.0f;
	}

	for (size_t i = 0; i < CurCount; i++)
	{
		TextRendereres[i]->SetActive(true);
	}
}

void AUIText::HideUIText(float DeltaTime)
{
	for (size_t i = 0; i < TextRendereres.size(); i++)
	{
		TextRendereres[i]->SetActive(false);
	}
}

void AUIText::SetOrder(ERenderOrder Order)
{
	for (size_t i = 0; i < TextRendereres.size(); i++)
	{
		TextRendereres[i]->SetOrder(Order);
	}
}

int AUIText::ConvertCharToIndex(char CharValue)
{
	if (CharValue >= 'A' && CharValue <= 'Z')
	{
		return(CharValue - 'A');
	}
	else if (CharValue >= 'a' && CharValue <= 'z')
	{
		return (CharValue - 'a' + 26);
	}
	else if (CharValue  >= '1' && CharValue <= '9') 
	{
		return (CharValue - '1' + 53);
	}
	else if (CharValue == '0')
	{
		return 52;
	}
	else
	{
		switch (CharValue)
		{
		case '!':
			return static_cast<int>(ETextIndex::EXCLAMATION);
			break;
		case '?': 
			return static_cast<int>(ETextIndex::QUESTION);
			break;
		case '<':
			return static_cast<int>(ETextIndex::LEFT_ARROW);
			break;
		case '>': 
			return static_cast<int>(ETextIndex::RIGHT_ARROW);
			break;
		case '(':
			return static_cast<int>(ETextIndex::LEFT_PARENT);
			break;
		case ')':
			return static_cast<int>(ETextIndex::RIGHT_PARENT);
			break;
		case '_':
			return static_cast<int>(ETextIndex::UNDERBAR);
			break;
		case '.':
			return static_cast<int>(ETextIndex::DOT);
			break;
		case ',': 
			return static_cast<int>(ETextIndex::COMMA_DOWN);
			break;
		default: 
			return static_cast<int>(ETextIndex::MAX);
			break;
		}
	}
}

void AUIText::Reserve(int Count)
{
	for (size_t i = 0; i < TextRendereres.size(); i++)
	{
		TextRendereres[i]->SetActive(false);
	}

	TextRendereres.resize(Count);

	for (size_t i = 0; i < TextRendereres.size(); i++)
	{
		USpriteRenderer* TextRenderer = CreateDefaultSubObject<USpriteRenderer>();
		TextRenderer->SetOrder(ERenderOrder::UI);
		TextRenderer->SetCameraEffect(false);
		TextRendereres[i] = TextRenderer;
	}
}

void AUIText::StartIdle()
{
	
}

void AUIText::StartMove()
{
	StartLocation = GetActorLocation();
	EndLocation = StartLocation + (MoveDir * HorizontalPadding);
	CurTime = 0.0f;
}

void AUIText::Idle(float DeltaTime)
{
}

void AUIText::Move(float DeltaTime)
{
	CurTime += DeltaTime;

	SetActorLocation(FVector2D::LerpClimp(StartLocation, EndLocation, CurTime / MoveFrequency));

	if (UEngineMath::Abs(GetActorLocation().Y - EndLocation.Y) <= 0.1f)
	{
		ChangeState(EUITExtState::IDLE);
	}

}

void AUIText::ChangeState(EUITExtState State)
{
	if (CurState == State) return;

	switch (State)
	{
	case EUITExtState::IDLE:
		StartIdle();
		break;
	case EUITExtState::MOVE:
		StartMove();
		break;
	default:
		break;
	}

	CurState = State;
}
