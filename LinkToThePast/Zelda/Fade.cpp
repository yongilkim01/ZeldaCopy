#include "PreCompile.h"
#include "Fade.h"
#include "ContentsEnum.h"

#include <EngineCore/SpriteRenderer.h>

AFade* AFade::Instance = nullptr;

AFade::AFade()
{
	USpriteRenderer* BackSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BackSpriteRenderer->SetOrder(ERenderOrder::FADE);
	BackSpriteRenderer->SetSprite("Fade.bmp");
	FVector2D MapScale = BackSpriteRenderer->SetSpriteScale(1.0f);
	BackSpriteRenderer->SetComponentLocation(MapScale.Half());
	BackSpriteRenderer->SetCameraEffect(false);
}

AFade::~AFade()
{
}

void AFade::LevelChangeStart()
{
	Instance = this;
}

