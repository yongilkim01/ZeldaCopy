#include "PreCompile.h"
#include "RoomManageMode.h"
#include "Room.h"
#include "ContentsEnum.h"
#include <EngineCore/SpriteRenderer.h>
#include "Player.h"

ARoomManageMode::ARoomManageMode()
{
}

ARoomManageMode::~ARoomManageMode()
{
	for (int i = 0; i < RoomCount; i++)
	{
		//Roomes[i] = nullptr;
	}
}

void ARoomManageMode::BeginPlay()
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

	PlayerCharacter = APlayer::StaticPlayer;
	
	//Dungeon1 = GetWorld()->SpawnActor<ARoom>();
	//Dungeon1->SetRoomSprite("Dungeon1.png", ERenderOrder::BACKGROUND, { 0, 0 }, RoomScale);
	//Dungeon1->SetRoomSize(780, 720);
	//Dungeon1->SetName("Dungeon1");
	//Dungeon1->AddMonster("Orc");

	//Dungeon2 = GetWorld()->SpawnActor<ARoom>();
	//Dungeon2->SetRoomSprite("Dungeon2.png", ERenderOrder::BACKGROUND, { 0, 720 }, RoomScale);
	//Dungeon2->SetRoomSize(780, 760);
	//Dungeon2->SetName("Dungeon2");

	//Dungeon3 = GetWorld()->SpawnActor<ARoom>();
	//Dungeon3->SetRoomSprite("Dungeon3.png", ERenderOrder::BACKGROUND, { 780, 720 }, RoomScale);
	//Dungeon3->SetRoomSize(760, 760);
	//Dungeon3->SetName("Dungeon3");

	//Dungeon4 = GetWorld()->SpawnActor<ARoom>();
	//Dungeon4->SetRoomSprite("Dungeon4.png", ERenderOrder::BACKGROUND, { 1540, 720 }, RoomScale);
	//Dungeon4->SetRoomSize(1412, 760);
	//Dungeon4->SetName("Dungeon4");

	//Dungeon5 = GetWorld()->SpawnActor<ARoom>();
	//Dungeon5->SetRoomSprite("Dungeon5.png", ERenderOrder::BACKGROUND, { 1752, 0 }, RoomScale);
	//Dungeon5->SetRoomSize(1200, 720);
	//Dungeon5->SetName("Dungeon5");

	//Dungeon6 = GetWorld()->SpawnActor<ARoom>();
	//Dungeon6->SetRoomSprite("Dungeon6.png", ERenderOrder::BACKGROUND, { 1546, 1480 }, RoomScale);
	//Dungeon6->SetRoomSize(1406, 620);
	//Dungeon6->SetName("Dungeon6");

	//Dungeon7 = GetWorld()->SpawnActor<ARoom>();
	//Dungeon7->SetRoomSprite("Dungeon7.png", ERenderOrder::BACKGROUND, { 1546, 2100 }, RoomScale);
	//Dungeon7->SetRoomSize(1406, 824);
	//Dungeon7->SetName("Dungeon7");

	//Dungeon8 = GetWorld()->SpawnActor<ARoom>();
	//Dungeon8->SetRoomSprite("Dungeon8.png", ERenderOrder::BACKGROUND, { 0, 1480 }, RoomScale);
	//Dungeon8->SetRoomSize(1546, 1444);
	//Dungeon8->SetName("Dungeon8");
	
	//PlayerCharacter->CurRoom = Dungeon1;
}

void ARoomManageMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int i = 0; i < RoomCount; i++)
	{
		if (CheckRoomInPlayer(Roomes[i]))
		{
			APlayer::StaticPlayer->CurRoom->SetPlayer(nullptr);
			APlayer::StaticPlayer->CurRoom = Roomes[i];
		}
	}

	//if (PlayerCharacter->GetActorLocation().iX() > Dungeon1->LeftTopPos.iX()
	//	&& PlayerCharacter->GetActorLocation().iY() > Dungeon1->LeftTopPos.iY()
	//	&& PlayerCharacter->GetActorLocation().iX() < Dungeon1->RightBottomPos.iX()
	//	&& PlayerCharacter->GetActorLocation().iY() < Dungeon1->RightBottomPos.iY())
	//{
	//	APlayer::StaticPlayer->CurRoom->SetPlayer(nullptr);
	//	APlayer::StaticPlayer->CurRoom = Dungeon1;
	//}
	//else if (PlayerCharacter->GetActorLocation().iX() > Dungeon2->LeftTopPos.iX()
	//	&& PlayerCharacter->GetActorLocation().iY() > Dungeon2->LeftTopPos.iY()
	//	&& PlayerCharacter->GetActorLocation().iX() < Dungeon2->RightBottomPos.iX()
	//	&& PlayerCharacter->GetActorLocation().iY() < Dungeon2->RightBottomPos.iY())
	//{
	//	APlayer::StaticPlayer->CurRoom->SetPlayer(nullptr);
	//	APlayer::StaticPlayer->CurRoom = Dungeon2;
	//}
	//else if (Dungeon3->CheckPlayer(APlayer::StaticPlayer) && APlayer::StaticPlayer->CurRoom->GetName() != "Dungeon3")
	//{
	//	APlayer::StaticPlayer->CurRoom->SetPlayer(nullptr);
	//	APlayer::StaticPlayer->CurRoom = Dungeon3;
	//}
	//else if (Dungeon4->CheckPlayer(APlayer::StaticPlayer) && APlayer::StaticPlayer->CurRoom->GetName() != "Dungeon4")
	//{
	//	APlayer::StaticPlayer->CurRoom->SetPlayer(nullptr);
	//	APlayer::StaticPlayer->CurRoom = Dungeon4;
	//}
	//else if (Dungeon5->CheckPlayer(APlayer::StaticPlayer) && APlayer::StaticPlayer->CurRoom->GetName() != "Dungeon5")
	//{
	//	APlayer::StaticPlayer->CurRoom->SetPlayer(nullptr);
	//	APlayer::StaticPlayer->CurRoom = Dungeon5;
	//}
	//else if (Dungeon6->CheckPlayer(APlayer::StaticPlayer) && APlayer::StaticPlayer->CurRoom->GetName() != "Dungeon6")
	//{
	//	APlayer::StaticPlayer->CurRoom->SetPlayer(nullptr);
	//	APlayer::StaticPlayer->CurRoom = Dungeon6;
	//}
	//else if (Dungeon7->CheckPlayer(APlayer::StaticPlayer) && APlayer::StaticPlayer->CurRoom->GetName() != "Dungeon7")
	//{
	//	APlayer::StaticPlayer->CurRoom->SetPlayer(nullptr);
	//	APlayer::StaticPlayer->CurRoom = Dungeon7;
	//}
	//else if (Dungeon8->CheckPlayer(APlayer::StaticPlayer) && APlayer::StaticPlayer->CurRoom->GetName() != "Dungeon8")
	//{
	//	APlayer::StaticPlayer->CurRoom->SetPlayer(nullptr);
	//	APlayer::StaticPlayer->CurRoom = Dungeon8;
	//}
}

bool ARoomManageMode::CheckRoomInPlayer(ARoom* CheckRoom)
{
	return (PlayerCharacter->GetActorLocation().iX() > CheckRoom->LeftTopPos.iX()
		&& PlayerCharacter->GetActorLocation().iY() > CheckRoom->LeftTopPos.iY()
		&& PlayerCharacter->GetActorLocation().iX() < CheckRoom->RightBottomPos.iX()
		&& PlayerCharacter->GetActorLocation().iY() < CheckRoom->RightBottomPos.iY());
}

