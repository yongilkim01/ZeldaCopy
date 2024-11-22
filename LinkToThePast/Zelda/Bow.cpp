#include "PreCompile.h"
#include "Bow.h"
#include "ContentsEnum.h"

#include <EngineCore/SpriteRenderer.h>

ABow::ABow()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Bow.png");
		FVector2D SpriteScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(FVector2D::ZERO);
		SpriteRenderer->SetComponentScale(SpriteScale);
		SpriteRenderer->SetOrder(ERenderOrder::FIRST_FLOOR_OBJ);
	}
	{
		UISpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		UISpriteRenderer->SetSprite("UIBow.png");
		UISpriteName = "UIBow.png";
		FVector2D SpriteScale = UISpriteRenderer->SetSpriteScale(1.0f);
		UISpriteRenderer->SetComponentLocation(FVector2D::ZERO);
		UISpriteRenderer->SetComponentScale(SpriteScale);
		UISpriteRenderer->SetOrder(ERenderOrder::FIRST_FLOOR_OBJ);
		UISpriteRenderer->SetActive(false);
	}
}

ABow::~ABow()
{
}

void ABow::BeginPlay()
{
	AWeaponItem::BeginPlay();
}

void ABow::Tick(float DeltaTime)
{
	AWeaponItem::Tick(DeltaTime);
	int a = 0;
}

