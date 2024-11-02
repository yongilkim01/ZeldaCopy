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
}

void ARoomManageMode::BeginPlay()
{
	float RoomScale = 1.0f;
	ARoom* Dungeon1 = GetWorld()->SpawnActor<ARoom>();
	Dungeon1->SetRoomSprite("Dungeon1.png", ERenderOrder::BACKGROUND, { 0, 0 }, RoomScale);
	Dungeon1->SetRoomSize(1406, 824);
	//Dungeon1->AddMonster("Orc");

	ARoom* Dungeon2 = GetWorld()->SpawnActor<ARoom>();
	Dungeon2->SetRoomSprite("Dungeon2.png", ERenderOrder::BACKGROUND, { 0, 720 }, RoomScale);
	Dungeon2->SetRoomSize(1406, 824);

	ARoom* Dungeon3 = GetWorld()->SpawnActor<ARoom>();
	Dungeon3->SetRoomSprite("Dungeon3.png", ERenderOrder::BACKGROUND, { 780, 720 }, RoomScale);
	Dungeon3->SetRoomSize(1406, 824);

	ARoom* Dungeon4 = GetWorld()->SpawnActor<ARoom>();
	Dungeon4->SetRoomSprite("Dungeon4.png", ERenderOrder::BACKGROUND, { 1540, 720 }, RoomScale);
	Dungeon4->SetRoomSize(1406, 824);

	ARoom* Dungeon5 = GetWorld()->SpawnActor<ARoom>();
	Dungeon5->SetRoomSprite("Dungeon5.png", ERenderOrder::BACKGROUND, { 1752, 0 }, RoomScale);
	Dungeon5->SetRoomSize(1406, 824);

	ARoom* Dungeon6 = GetWorld()->SpawnActor<ARoom>();
	Dungeon6->SetRoomSprite("Dungeon6.png", ERenderOrder::BACKGROUND, { 1546, 1480 }, RoomScale);
	Dungeon6->SetRoomSize(1406, 824);

	ARoom* Dungeon7 = GetWorld()->SpawnActor<ARoom>();
	Dungeon7->SetRoomSprite("Dungeon7.png", ERenderOrder::BACKGROUND, { 1546, 2100 }, RoomScale);
	Dungeon7->SetRoomSize(1406, 824);

	ARoom* Dungeon8 = GetWorld()->SpawnActor<ARoom>();
	Dungeon8->SetRoomSprite("Dungeon8.png", ERenderOrder::BACKGROUND, { 0, 1480 }, RoomScale);
	Dungeon8->SetRoomSize(1406, 824);
	//780, 720

	//APlayer::StaticPlayer->CurRoom = Dungeon7;
	//FVector2D Size = Dungeon7->GetRoomSize();
	//GetWorld()->SetCameraPivot(Size.Half() * -1.0f);
}

