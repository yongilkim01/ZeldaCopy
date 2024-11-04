#include "PreCompile.h"
#include "RoomManageMode.h"
#include "Room.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "UserInterface.h"

#include <EngineCore/SpriteRenderer.h>

ARoomManageMode::ARoomManageMode()
{

}

ARoomManageMode::~ARoomManageMode()
{
}

void ARoomManageMode::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = APlayer::StaticPlayer;

	RoomesBeginPlay();
	UIBeginPlay();
}

void ARoomManageMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RommesTick();
}

void ARoomManageMode::RoomesBeginPlay()
{
	Roomes.reserve(10);
	RoomLocations.reserve(10);
	RoomSizes.reserve(10);

	RoomLocations.push_back({ 0, 0 });				// Dungeon1
	RoomLocations.push_back({ 0, 720 });			// Dungeon2
	RoomLocations.push_back({ 780, 720 });			// Dungeon3
	RoomLocations.push_back({ 1540, 720 });			// Dungeon4
	RoomLocations.push_back({ 1752, 0 });			// Dungeon5
	RoomLocations.push_back({ 1546, 1480 });		// Dungeon6
	RoomLocations.push_back({ 1546, 2100 });		// Dungeon7
	RoomLocations.push_back({ 0, 1480 });			// Dungeon8

	RoomSizes.push_back({ 780, 720 });				// Dungeon1
	RoomSizes.push_back({ 780, 760 });				// Dungeon2
	RoomSizes.push_back({ 760, 760 });				// Dungeon3
	RoomSizes.push_back({ 1412, 760 });				// Dungeon4
	RoomSizes.push_back({ 1200, 720 });				// Dungeon5
	RoomSizes.push_back({ 1406, 620 });				// Dungeon6
	RoomSizes.push_back({ 1406, 824 });				// Dungeon7
	RoomSizes.push_back({ 1546, 1444 });			// Dungeon8

	for (int i = 0; i < RoomCount; i++)
	{
		ARoom* DungeonRoom = GetWorld()->SpawnActor<ARoom>();
		std::string DungeonName = "Dungeon";
		DungeonName.append(std::to_string(i + 1));
		std::string FileName = DungeonName + ".png";
		DungeonRoom->SetRoomSprite(FileName, ERenderOrder::BACKGROUND, RoomLocations[i], 1.0f);
		DungeonRoom->SetRoomSize(RoomSizes[i]);
		DungeonRoom->SetName(DungeonName);

		Roomes.push_back(DungeonRoom);
	}

	FindRoomToName("Dungeon1")->LinkRoom(FindRoomToName("Dungeon2"));
	int a = 0;
}

void ARoomManageMode::RommesTick()
{
	for (int i = 0; i < RoomCount; i++)
	{
		if (CheckRoomInPlayer(Roomes[i]))
		{
			APlayer::StaticPlayer->CurRoom->SetPlayer(nullptr);
			APlayer::StaticPlayer->CurRoom = Roomes[i];
		}
	}
}

void ARoomManageMode::UIBeginPlay()
{
	UI = GetWorld()->SpawnActor<AUserInterface>();
	UI->SetPlayer(this->PlayerCharacter);
}

void ARoomManageMode::UITick()
{
}

bool ARoomManageMode::CheckRoomInPlayer(ARoom* CheckRoom)
{
	return (PlayerCharacter->GetActorLocation().iX() > CheckRoom->LeftTopPos.iX()
		&& PlayerCharacter->GetActorLocation().iY() > CheckRoom->LeftTopPos.iY()
		&& PlayerCharacter->GetActorLocation().iX() < CheckRoom->RightBottomPos.iX()
		&& PlayerCharacter->GetActorLocation().iY() < CheckRoom->RightBottomPos.iY());
}

ARoom* ARoomManageMode::FindRoomToName(std::string_view RoomName)
{
	for (int i = 0; i < RoomCount; i++)
	{
		if (Roomes[i]->GetName() == RoomName)
		{
			return Roomes[i];
		}
	}

	return nullptr;
}
