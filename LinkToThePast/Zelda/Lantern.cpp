#include "PreCompile.h"
#include "Lantern.h"
#include "ContentsEnum.h"

#include <EngineCore/SpriteRenderer.h>

ALantern::ALantern()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Lantern.png");
		FVector2D SpriteScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(FVector2D::ZERO);
		SpriteRenderer->SetComponentScale(SpriteScale);
		SpriteRenderer->SetOrder(ERenderOrder::FIRST_FLOOR_OBJ);
	}
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("UILantern.png");
		FVector2D SpriteScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(FVector2D::ZERO);
		SpriteRenderer->SetComponentScale(SpriteScale);
		SpriteRenderer->SetOrder(ERenderOrder::FIRST_FLOOR_OBJ);
		SpriteRenderer->SetActive(false);
	}
}

ALantern::~ALantern()
{
}

void ALantern::BeginPlay()
{
	AWeaponItem::BeginPlay();
}

void ALantern::Tick(float DeltaTime)
{
	AWeaponItem::Tick(DeltaTime);
	int a = 0;
}

