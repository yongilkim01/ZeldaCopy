#include "PreCompile.h"
#include "Lantern.h"
#include "ContentsEnum.h"
#include "PlayerCharacter.h"

#include "EffectFire.h"

#include <EngineCore/SpriteRenderer.h>

ALantern::ALantern()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Lantern.png");
		FVector2D SpriteScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(FVector2D::ZERO);
		SpriteRenderer->SetComponentScale(SpriteScale);
		SpriteRenderer->SetAlphafloat(0.0f);
		SpriteRenderer->SetOrder(ERenderOrder::FIRST_FLOOR_OBJ);
		SpriteRenderer->SetActive(false);
	}
	{
		UISpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		UISpriteRenderer->SetSprite("UILantern.png");
		UISpriteName = "UILantern.png";
		FVector2D SpriteScale = UISpriteRenderer->SetSpriteScale(1.0f);
		UISpriteRenderer->SetComponentLocation(FVector2D::ZERO);
		UISpriteRenderer->SetComponentScale(SpriteScale);
		UISpriteRenderer->SetOrder(ERenderOrder::FIRST_FLOOR_OBJ);
		UISpriteRenderer->SetActive(false);
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
	SpriteRenderer->SetAlphafloat(0.0f);
}

void ALantern::Action(float Tick)
{
	AEffectFire* FireEffect = GetWorld()->SpawnActor<AEffectFire>();
	FVector2D Direction = OwnerPlayer->GetCurDirection();
	float DistanceToOwner = OwnerPlayer->GetChildDistance();
	FireEffect->SetActorLocation(GetActorLocation() + (Direction * DistanceToOwner));
}

