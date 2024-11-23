#include "PreCompile.h"
#include "WeaponItem.h"
#include "ContentsEnum.h"
#include "PlayerCharacter.h"

#include <EngineCore/SpriteRenderer.h>

AWeaponItem::AWeaponItem()
{
}

AWeaponItem::~AWeaponItem()
{
}

void AWeaponItem::BeginPlay()
{
	ABaseItem::BeginPlay();
}

void AWeaponItem::Tick(float DeltaTime)
{
	ABaseItem::Tick(DeltaTime);
	SetActorLocation(OwnerPlayer->GetActorLocation());
}

