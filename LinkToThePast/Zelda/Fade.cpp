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
		ZoomRenderer->SetSprite("BigFadeOut.png", 0);
		FVector2D ZoomScale = ZoomRenderer->SetSpriteScale(1.0f);
		ZoomRenderer->SetComponentLocation(FVector2D::ZERO);
		ZoomRenderer->CreateAnimation("FadeOut", "BigFadeOut.png", 0, 7, 0.08f, false);
		ZoomRenderer->CreateAnimation("FadeIn", "BigFadeIn.png", 0, 7, 0.08f, false);
		ZoomRenderer->SetAlphafloat(0.0f);

		ZoomRenderer->SetAnimationEvent("FadeOut", 7, [this]()
			{
				ZoomRenderer->SetAlphafloat(0.0f);
			}
		);

		ZoomRenderer->SetAnimationEvent("FadeIn", 7, [this]()
			{
				AlphaRenderer->SetAlphafloat(1.0f);
				//TimeEvent
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

void AFade::ResetFade()
{
	AlphaRenderer->SetAlphafloat(0.0f);
	ZoomRenderer->SetAlphafloat(0.0f);
}

// 0 => 1
void AFade::FadeIn()
{
	if (true == IsFadeInOn())
	{

		if (false == IsFading)
		{
			IsFading = true;
			ZoomRenderer->SetAlphafloat(1.0f);
			ZoomRenderer->ChangeAnimation("FadeIn");
		}
	}
}

// 1 => 0
void AFade::FadeOut()
{
	if (true == IsFadeOutOn())
	{
		ZoomRenderer->SetAlphafloat(1.0f);
		ZoomRenderer->ChangeAnimation("FadeOut");

	}
}