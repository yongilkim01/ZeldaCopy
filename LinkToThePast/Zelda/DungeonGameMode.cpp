#include "PreCompile.h"
#include "DungeonGameMode.h"
#include "PlayerCharacter.h"
#include "Room.h"
#include "RoomMove.h"
#include "EnemyCharacter.h"
#include "HylianKnights.h"
#include "Fade.h"
#include "Pot.h"
#include "LevelMove.h"
#include <EngineCore/EngineAPICore.h>

ACastleDungeonGameMode::ACastleDungeonGameMode()
{
}

ACastleDungeonGameMode::~ACastleDungeonGameMode()
{
}

void ACastleDungeonGameMode::BeginPlay()
{
	AZeldaGameMode::BeginPlay();

	BeginPlayRoomActor();
	UIBeginPlay();

	CheckCollisionRoom();

	{
		AHylianKnight* EnemyCharacter = GetWorld()->SpawnActor<AHylianKnight>();
		EnemyCharacter->SetActorLocation({ 2332, 1724 });
		EnemyCharacter->SetSpeed(150.0f);
		EnemyCharacter->AddTurningLocation(FVector2D(2332, 1974));
		EnemyCharacter->AddTurningLocation(FVector2D(2332, 1724));

		CheckCharacterInRoom(EnemyCharacter);

	}

	AFade* FadeActor = GetWorld()->SpawnActor<AFade>();

	FadeActor->GetBackSpriteRenderer()->SetAnimationEvent("FadeOut", 7, []()
		{
			int a = 0;
		});

	FadeActor->GetBackSpriteRenderer()->SetAnimationEvent("FadeIn", 7, []()
		{
			UEngineAPICore::GetCore()->OpenLevel("HyruleCastle");
		});


	FadeActor->SetActorLocation({ 0, 0 });
	FadeActor->FadeOut();

	ALevelMove* LevelMove1 = GetWorld()->SpawnActor<ALevelMove>();
	LevelMove1->SetActorLocation({ 2305, 115 });
	LevelMove1->SetFade(FadeActor);

	{
		APot* Pot1 = GetWorld()->SpawnActor<APot>();
		Pot1->SetActorLocation({ 2473, 2369 });
		Pot1->SetCurRoom(Roomes[5], ERoomFloor::FLOOR_1F);

		APot* Pot2 = GetWorld()->SpawnActor<APot>();
		Pot2->SetActorLocation({ 2161, 1985 });
		Pot2->SetCurRoom(Roomes[5], ERoomFloor::FLOOR_1F);

		APot* Pot3 = GetWorld()->SpawnActor<APot>();
		Pot3->SetActorLocation({ 2161, 1743 });
		Pot3->SetCurRoom(Roomes[5], ERoomFloor::FLOOR_1F);
	}

}

void ACastleDungeonGameMode::Tick(float DeltaTime)
{
	AZeldaGameMode::Tick(DeltaTime);

	CheckCollisionRoom();
}

void ACastleDungeonGameMode::BeginPlayRoomActor()
{
	Roomes.reserve(10);
	RoomDataes.reserve(10);

	RoomDataes.push_back({ { 0, 0 } ,{ 780, 720 } });			// Dungeon1	
	RoomDataes.push_back({ { 0, 720 } ,{ 780, 760 } });			// Dungeon2
	RoomDataes.push_back({ { 780, 720 } ,{ 760, 760 } });		// Dungeon3
	RoomDataes.push_back({ { 1546, 720 } ,{ 1406, 709 } });		// Dungeon4
	RoomDataes.push_back({ { 1752, 0 } ,{ 1200, 720 } });		// Dungeon5
	RoomDataes.push_back({ { 1546, 1429 } ,{ 1406, 1496 } });	// Dungeon6
	RoomDataes.push_back({ { 0, 1480 } ,{ 1546, 1444 } });		// Dungeon7

	CreateRoomActor("CastleDungeon", 0);

	{
		this->Roomes[0]->SetIsSecondFloor(true);
		this->Roomes[0]->GetColSpriteRenderer2F()->SetSprite("CastleDungeon1Collision2F.png");
		this->Roomes[0]->CreateEnvSprite("CastleDungeon1Door1.png", FVector2D(384, 0), FVector2D(267, 138), ERenderOrder::FIRST_FLOOR_OBJ);
		this->Roomes[0]->CreateEnvSprite("CastleDungeon1Door2.png", FVector2D(246, 642), FVector2D(273, 78), ERenderOrder::SECOND_FLOOR_OBJ);
	}
	{
		this->Roomes[1]->SetIsSecondFloor(true);
		this->Roomes[1]->GetColSpriteRenderer2F()->SetOrder(ERenderOrder::COLMAP);
		this->Roomes[1]->GetColSpriteRenderer2F()->SetSprite("CastleDungeon2Collision2F.png");
		FVector2D ColMap2Scale = this->Roomes[1]->GetColSpriteRenderer2F()->SetSpriteScale(1.0f);
		this->Roomes[1]->GetColSpriteRenderer2F()->SetComponentLocation(ColMap2Scale.Half());
		this->Roomes[1]->CreateEnvSprite("CastleDungeon2Door1.png", FVector2D(249, 0), FVector2D(270, 114), ERenderOrder::SECOND_FLOOR_OBJ);
		this->Roomes[1]->CreateEnvSprite("CastleDungeon2Door2.png", FVector2D(624, 296), FVector2D(156, 210), ERenderOrder::FIRST_FLOOR_OBJ);
		this->Roomes[1]->CreateEnvSprite("CastleDungeon2Door3.png", FVector2D(229, 618), FVector2D(323, 142), ERenderOrder::FIRST_FLOOR_OBJ);

	}
	{
		this->Roomes[2]->CreateEnvSprite("CastleDungeon3Door1.png", FVector2D(0, 288), FVector2D(132, 236), ERenderOrder::FIRST_FLOOR_OBJ);

	}
	{
		this->Roomes[3]->SetIsSecondFloor(true);
		this->Roomes[3]->GetColSpriteRenderer2F()->SetOrder(ERenderOrder::COLMAP);
		this->Roomes[3]->GetColSpriteRenderer2F()->SetSprite("CastleDungeon4Collision2F.png");
		FVector2D ColMap2Scale = this->Roomes[3]->GetColSpriteRenderer2F()->SetSpriteScale(1.0f);
		this->Roomes[3]->GetColSpriteRenderer2F()->SetComponentLocation(ColMap2Scale.Half());
		this->Roomes[3]->CreateEnvSprite("CastleDungeon4Door1.png", FVector2D(612, 0), FVector2D(313, 114), ERenderOrder::SECOND_FLOOR_OBJ);

	}
	{
		this->Roomes[4]->CreateEnvSprite("CastleDungeon5Door1.png", FVector2D(371, 0), FVector2D(338, 138), ERenderOrder::SECOND_FLOOR_OBJ);
		this->Roomes[4]->CreateEnvSprite("CastleDungeon5Door2.png", FVector2D(408, 642), FVector2D(298, 78), ERenderOrder::SECOND_FLOOR_OBJ);
		this->Roomes[4]->SetOnlySecondFloor(true);
	}
	{
		this->Roomes[5]->SetIsSecondFloor(true);
		this->Roomes[5]->GetColSpriteRenderer2F()->SetOrder(ERenderOrder::COLMAP);
		this->Roomes[5]->GetColSpriteRenderer2F()->SetSprite("CastleDungeon6Collision2F.png");
		FVector2D ColMap2Scale = this->Roomes[5]->GetColSpriteRenderer2F()->SetSpriteScale(1.0f);
		this->Roomes[5]->GetColSpriteRenderer2F()->SetComponentLocation(ColMap2Scale.Half());
	}
	{
		this->Roomes[6]->SetIsSecondFloor(true);
		this->Roomes[6]->GetColSpriteRenderer2F()->SetOrder(ERenderOrder::COLMAP);
		this->Roomes[6]->GetColSpriteRenderer2F()->SetSprite("CastleDungeon7Collision2F.png");
		FVector2D ColMap8Scale = this->Roomes[6]->GetColSpriteRenderer2F()->SetSpriteScale(1.0f);
		this->Roomes[6]->GetColSpriteRenderer2F()->SetComponentLocation(ColMap8Scale.Half());
		this->Roomes[6]->CreateEnvSprite("CastleDungeon7Bridge.png", FVector2D(1008, 410), FVector2D(144, 500), ERenderOrder::SECOND_FLOOR);
		this->Roomes[6]->CreateEnvSprite("CastleDungeon7Door1.png", FVector2D(238, 0), FVector2D(311, 191), ERenderOrder::FIRST_FLOOR_OBJ);

	}
}