#include "PreCompile.h"
#include "DungeonGameMode.h"
#include "PlayerCharacter.h"
#include "Room.h"
#include "RoomMove.h"

DungeonGameMode::DungeonGameMode()
{
}

DungeonGameMode::~DungeonGameMode()
{
}

void DungeonGameMode::BeginPlay()
{
	ARoomManageMode::BeginPlay();

	RoomBeginPlay();
	UIBeginPlay();

	PlayerCharacter->SetCurRoom(Roomes[0]);
	this->CurRoom = Roomes[0];

}

void DungeonGameMode::Tick(float DeltaTime)
{
	ARoomManageMode::Tick(DeltaTime);
}

void DungeonGameMode::RoomBeginPlay()
{
	Roomes.reserve(10);
	RoomDataes.reserve(10);

	RoomDataes.push_back({ { 0, 0 } ,{ 780, 720 } });			// Dungeon1	
	RoomDataes.push_back({ { 0, 720 } ,{ 780, 760 } });			// Dungeon2
	RoomDataes.push_back({ { 780, 720 } ,{ 760, 760 } });		// Dungeon3
	RoomDataes.push_back({ { 1540, 720 } ,{ 1412, 760 } });		// Dungeon4
	RoomDataes.push_back({ { 1752, 0 } ,{ 1200, 720 } });		// Dungeon5
	RoomDataes.push_back({ { 1546, 1480 } ,{ 1406, 620 } });	// Dungeon6
	RoomDataes.push_back({ { 1546, 2100 } ,{ 1406, 824 } });	// Dungeon7
	RoomDataes.push_back({ { 0, 1480 } ,{ 1546, 1444 } });		// Dungeon8

	CreateRoomActor("CastleDungeon", 0);
}

