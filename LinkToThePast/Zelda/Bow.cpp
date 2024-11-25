#include "PreCompile.h"
#include "Bow.h"
#include "ContentsEnum.h"
#include "Arrow.h"
#include "PlayerCharacter.h"
#include "Room.h"

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
	SpriteRenderer->SetAlphafloat(0.0f);
}

void ABow::Tick(float DeltaTime)
{
	AWeaponItem::Tick(DeltaTime);
	int a = 0;
}

void ABow::Action(float DeltaTime)
{
	AArrow* Arrow = GetWorld()->SpawnActor<AArrow>();
	Arrow->SetDirection(OwnerPlayer->GetCurDirection());
	Arrow->SetCollisionImage(OwnerPlayer->GetCollisionImage());
	Arrow->SetCurRoom(OwnerPlayer->GetCurRoom());
	switch (OwnerPlayer->GetCurRoomFloor())
	{
	case ERoomFloor::FLOOR_1F:
		Arrow->SetOrder(static_cast<int>(ERenderOrder::FIRST_FLOOR_OBJ) + 1000);
		break;
	case ERoomFloor::FLOOR_2F:
		Arrow->SetOrder(static_cast<int>(ERenderOrder::SECOND_FLOOR_OBJ) + 1000);
		break;
	default:
		break;

	}
	float DistanceToOwner = OwnerPlayer->GetChildDistance();
	Arrow->SetActorLocation(GetActorLocation() + (OwnerPlayer->GetCurDirection() * DistanceToOwner));
}

