#include "PreCompile.h"
#include "RoomManageMode.h"
#include "Room.h"

ARoomManageMode::ARoomManageMode()
{
}

ARoomManageMode::~ARoomManageMode()
{
}

void ARoomManageMode::BeginPlay()
{
	ARoom* Dungeon1 = GetWorld()->SpawnActor<ARoom>();
	ARoom* Dungeon2 = GetWorld()->SpawnActor<ARoom>();
}

