#include "PreCompile.h"
#include "Fade.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>
#include "ContentsEnum.h"


AFade* AFade::Instance = nullptr;

AFade::AFade()
{
	BackSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BackSpriteRenderer->SetOrder(ERenderOrder::FADE);
	BackSpriteRenderer->SetSprite("FadeIn.png");
	FVector2D MapScale = BackSpriteRenderer->SetSpriteScale(1.0f);
	BackSpriteRenderer->SetComponentLocation(MapScale.Half());
	BackSpriteRenderer->SetCameraEffect(false);
	//BackSpriteRenderer->SetAlphaChar(200);

	BackSpriteRenderer->CreateAnimation("FadeOut", "FadeOut.png", 0, 7, 0.1f);
	BackSpriteRenderer->CreateAnimation("FadeIn", "FadeIn.png", 0, 7, 0.1f);
	BackSpriteRenderer->CreateAnimation("Black", "BlackBlankSprite.png", 0, 0, 0.1f);

	BackSpriteRenderer->SetAnimationEvent("FadeOut", 7, std::bind(&AFade::FadeOutEnd, this));
	BackSpriteRenderer->SetAnimationEvent("FadeIn", 7, std::bind(&AFade::FadeInEnd, this));

	BackSpriteRenderer->SetAlphafloat(0.0f);

	FVector2D Pos = GetActorLocation();
}

AFade::~AFade()
{
}

void AFade::FadeChange()
{
	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();
	FadeValue += DeltaTime * 0.5F * FadeDir;
	BackSpriteRenderer->SetAlphafloat(FadeValue);

}

// 0 => 1
void AFade::FadeIn()
{
	if (false == IsFading)
	{
		IsFading = true;
		BackSpriteRenderer->SetAlphafloat(1.0f);
		BackSpriteRenderer->ChangeAnimation("FadeIn");
	}
}

void AFade::FadeOut()
{
	BackSpriteRenderer->SetAlphafloat(1.0f);
	BackSpriteRenderer->ChangeAnimation("FadeOut");
	//UEngineAPICore::GetCore()->OpenLevel("CastleDungeon");
}

void AFade::FadeInEnd()
{
	BackSpriteRenderer->ChangeAnimation("Black");
	UEngineAPICore::GetCore()->OpenLevel("CastleDungeon");
	TimeEventer.PushEvent(4.0f, std::bind(&AFade::FadeOut, this), false, false);
}

void AFade::FadeOutEnd()
{
	this->BackSpriteRenderer->SetAlphafloat(0.0f);
	IsFading = false;
}

void AFade::LevelChangeStart()
{
	Instance = this;
}