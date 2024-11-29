#include "PreCompile.h"
#include "Fade.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>
#include "ContentsEnum.h"

AFade::AFade()
{
	// SpriteRenderer component √ ±‚»≠
	{
		AlphaRenderer = CreateDefaultSubObject<USpriteRenderer>();
		AlphaRenderer->SetOrder(ERenderOrder::FADE);
		AlphaRenderer->SetSprite("Fade.bmp");
		FVector2D AlphaScale = AlphaRenderer->SetSpriteScale(1.0f);
		AlphaRenderer->SetComponentLocation(FVector2D::ZERO);
		//AlphaRenderer->SetCameraEffect(false);
		AlphaRenderer->SetAlphafloat(0.0f);
		AlphaRenderer->SetActive(true);

		
		ZoomRenderer = CreateDefaultSubObject<USpriteRenderer>();
		ZoomRenderer->SetOrder(ERenderOrder::FADE);
		ZoomRenderer->SetSprite("FadeOut.png", 0);
		FVector2D ZoomScale = ZoomRenderer->SetSpriteScale(1.0f);
		ZoomRenderer->SetComponentLocation(FVector2D::ZERO);
		ZoomRenderer->CreateAnimation("FadeOut", "FadeOut.png", 0, 7, 0.08f, false);
		ZoomRenderer->CreateAnimation("FadeIn", "FadeIn.png", 0, 7, 0.08f, false);
		ZoomRenderer->CreateAnimation("BigFadeOut", "BigFadeOut.png", 0, 7, 0.08f, false);
		ZoomRenderer->CreateAnimation("BigFadeIn", "BigFadeIn.png", 0, 7, 0.08f, false);
		ZoomRenderer->SetAlphafloat(0.0f);

		ZoomRenderer->SetAnimationEvent("FadeOut", 7, [this]()
			{
				ZoomRenderer->SetAlphafloat(0.0f);
			}
		);

		ZoomRenderer->SetAnimationEvent("FadeIn", 7, [this]()
			{
				AlphaRenderer->SetAlphafloat(1.0f);
			}
		);

		ZoomRenderer->SetAnimationEvent("BigFadeOut", 7, [this]()
			{
				ZoomRenderer->SetAlphafloat(0.0f);
			}
		);

		ZoomRenderer->SetAnimationEvent("BigFadeIn", 7, [this]()
			{
				AlphaRenderer->SetAlphafloat(1.0f);
			}
		);
	}
}

AFade::~AFade()
{
}

void AFade::BeginPlay()
{
	Super::BeginPlay();
}

void AFade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFade::LevelChangeStart()
{
	Super::LevelChangeStart();
}

void AFade::LevelChangeEnd()
{
	Super::LevelChangeEnd();
}

void AFade::FadeChange()
{
	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();
	FadeValue += DeltaTime * 0.5f * FadeDir;
	//AlphaRenderer->SetAlphafloat(FadeValue);

}

// 0 => 1
void AFade::FadeIn()
{
	if (false == IsFading)
	{
		IsFading = true;
		ZoomRenderer->SetAlphafloat(1.0f);

		switch (FadeSize)
		{
		case EFadeSize::NORMAL:
			ZoomRenderer->SetSprite("FadeIn.png", 0);
			ZoomRenderer->SetSpriteScale(1.0f);
			ZoomRenderer->ChangeAnimation("FadeIn");
			break;
		case EFadeSize::BIG:
			ZoomRenderer->SetSprite("BigFadeIn.png", 0);
			ZoomRenderer->SetSpriteScale(1.0f);
			ZoomRenderer->ChangeAnimation("BigFadeIn");
			break;
		default:
			break;
		}

	}
}

// 1 => 0
void AFade::FadeOut()
{
	if (true == IsFadeOn())
	{
		ZoomRenderer->SetAlphafloat(1.0f);

		switch (FadeSize)
		{
		case EFadeSize::NORMAL:
			ZoomRenderer->SetSprite("FadeOut.png", 0);
			ZoomRenderer->SetSpriteScale(1.0f);
			ZoomRenderer->ChangeAnimation("FadeOut");
			break;
		case EFadeSize::BIG:
			ZoomRenderer->SetSprite("BigFadeOut.png", 0);
			ZoomRenderer->SetSpriteScale(1.0f);
			ZoomRenderer->ChangeAnimation("BigFadeOut");
			break;
		default:
			break;
		}
	}
}