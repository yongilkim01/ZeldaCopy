#include "PreCompile.h"
#include "DropItem.h"
#include "PlayerCharacter.h"

ADropItem::ADropItem()
{
	
}

ADropItem::~ADropItem()
{
}

void ADropItem::BeginPlay()
{
	AEventActor::BeginPlay();

	PlayerCharacter = dynamic_cast<APlayerCharacter*>(GetWorld()->GetPawn());
}

void ADropItem::Tick(float DeltaTime)
{
	AEventActor::Tick(DeltaTime);

	switch (CurDropItemState)
	{
	case EDropItemState::DROP:
		Drop(DeltaTime);
		break;
	case EDropItemState::PICKUP:
		Pickup(DeltaTime);
		break;
	default:
		break;
	}
}

void ADropItem::StartDrop()
{
}

void ADropItem::StartPickup()
{
}

void ADropItem::Drop(float DeltaTime)
{
}

void ADropItem::Pickup(float DeltaTime)
{
}

void ADropItem::ChangeState(EDropItemState State)
{
	switch (State)
	{
	case EDropItemState::DROP:
		StartDrop();
		break;
	case EDropItemState::PICKUP:
		StartPickup();
		break;
	default:
		break;
	}

	CurDropItemState = State;
}
