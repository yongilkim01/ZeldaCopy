#include "PreCompile.h"
#include "HyruleCastleGameMode.h"
#include "ContentsEnum.h"

#include "PlayerCharacter.h"
#include "EnemyCharacter.h"
#include "CastleKnight.h"
#include "HylianKnights.h"

#include "Room.h"
#include "LevelMove.h"
#include "Fade.h"

#include "StatueFire.h"
#include "StatueStone.h"
#include "Pot.h"

#include <EngineCore/EngineAPICore.h>


AHyruleCastleGameMode::AHyruleCastleGameMode()
{
}

AHyruleCastleGameMode::~AHyruleCastleGameMode()
{
}

void AHyruleCastleGameMode::BeginPlay()
{
	AZeldaGameMode::BeginPlay();

	EffectSoundPlayer.Loop(100);
	EffectSoundPlayer = UEngineSound::Play("Hyrule Castle.mp3");

	// ·ë °´Ã¼¿Í UIµéµé ÃÊ±âÈ­
	BeginPlayRoomActor();
	BeginPlayUI();

	ALevelMove* LevelMove1 = GetWorld()->SpawnActor<ALevelMove>();
	LevelMove1->SetActorLocation({ 1532, 220 });
	LevelMove1->SetMoveLevelName("CastleDungeon");

	BeginPlayEnvActor();
	BeginPlayEnemyActor();
}

void AHyruleCastleGameMode::Tick(float DeltaTime)
{
	AZeldaGameMode::Tick(DeltaTime);

	CheckCollisionRoom();
}

void AHyruleCastleGameMode::BeginPlayRoomActor()
{
	Roomes.reserve(10);
	RoomDataes.reserve(10);

	RoomDataes.push_back({ { 0, 0 } ,{ 765, 1554 } });				// Castle1	
	RoomDataes.push_back({ { 765, 0 } ,{ 1536, 804 } });			// Castle2
	RoomDataes.push_back({ { 2301, 0 } ,{ 1152, 1554 } });			// Castle3
	RoomDataes.push_back({ { 2301, 1554 } ,{ 1152, 1536 } });		// Castle4
	RoomDataes.push_back({ { 765, 1554 } ,{ 1536, 1536 } });		// Castle5
	RoomDataes.push_back({ { 0, 1554 } ,{ 765, 1536 } });			// Castle6

	CreateRoomActor("Castle", 0);

	this->Roomes[0]->CreateEnvSprite("Castle1Door1.png", FVector2D(285, 1389), FVector2D(195, 165), ERenderOrder::FIRST_FLOOR_OBJ);
	this->Roomes[0]->CreateEnvSprite("Castle1Door2.png", FVector2D(624, 324), FVector2D(81, 174), ERenderOrder::FIRST_FLOOR_OBJ);

	this->Roomes[1]->CreateEnvSprite("Castle2Door1.png", FVector2D(0, 255), FVector2D(141, 288), ERenderOrder::FIRST_FLOOR_OBJ);
	this->Roomes[1]->CreateEnvSprite("Castle2Door2.png", FVector2D(1395, 300), FVector2D(140, 219), ERenderOrder::FIRST_FLOOR_OBJ);
	this->Roomes[1]->CreateEnvSprite("Castle2Door3.png", FVector2D(692, 171), FVector2D(152, 87), ERenderOrder::FIRST_FLOOR_OBJ);

	this->Roomes[2]->SetIsSecondFloor(true);
	this->Roomes[2]->GetColSpriteRenderer2F()->SetOrder(ERenderOrder::COLMAP);
	this->Roomes[2]->GetColSpriteRenderer2F()->SetSprite("Castle3Collision2F.png");
	FVector2D ColMap1Scale = this->Roomes[2]->GetColSpriteRenderer2F()->SetSpriteScale(1.0f);
	this->Roomes[2]->GetColSpriteRenderer2F()->SetComponentLocation(ColMap1Scale.Half());
	this->Roomes[2]->CreateEnvSprite("Castle3Door1.png", FVector2D(57, 252), FVector2D(84, 270), ERenderOrder::FIRST_FLOOR_OBJ);
	this->Roomes[2]->CreateEnvSprite("Castle3Door2.png", FVector2D(288, 1389), FVector2D(195, 165), ERenderOrder::FIRST_FLOOR_OBJ);
	this->Roomes[2]->CreateEnvSprite("Castle3Door3.png", FVector2D(635, 1458), FVector2D(268, 96), ERenderOrder::SECOND_FLOOR_OBJ);

	this->Roomes[3]->SetIsSecondFloor(true);
	this->Roomes[3]->GetColSpriteRenderer2F()->SetOrder(ERenderOrder::COLMAP);
	this->Roomes[3]->GetColSpriteRenderer2F()->SetSprite("Castle4Collision2F.png");
	FVector2D ColMap2Scale = this->Roomes[3]->GetColSpriteRenderer2F()->SetSpriteScale(1.0f);
	this->Roomes[3]->GetColSpriteRenderer2F()->SetComponentLocation(ColMap2Scale.Half());
	this->Roomes[3]->CreateEnvSprite("Castle4Bridge.png", FVector2D(528, 384), FVector2D(192, 552), ERenderOrder::SECOND_FLOOR);
	this->Roomes[3]->CreateEnvSprite("Castle4Door1.png", FVector2D(288, 0), FVector2D(194, 168), ERenderOrder::FIRST_FLOOR_OBJ);
	this->Roomes[3]->CreateEnvSprite("Castle4Door2.png", FVector2D(655, 0), FVector2D(212, 96), ERenderOrder::SECOND_FLOOR_OBJ);
	this->Roomes[3]->CreateEnvSprite("Castle4Door3.png", FVector2D(0, 669), FVector2D(144, 195), ERenderOrder::FIRST_FLOOR_OBJ);
	this->Roomes[3]->CreateEnvSprite("Castle4Door4.png", FVector2D(183, 1440), FVector2D(396, 96), ERenderOrder::SECOND_FLOOR_OBJ);

	this->Roomes[4]->SetIsSecondFloor(true);
	this->Roomes[4]->GetColSpriteRenderer2F()->SetOrder(ERenderOrder::COLMAP);
	this->Roomes[4]->GetColSpriteRenderer2F()->SetSprite("Castle5Collision2F.png");
	FVector2D ColMap3Scale = this->Roomes[4]->GetColSpriteRenderer2F()->SetSpriteScale(1.0f);
	this->Roomes[4]->GetColSpriteRenderer2F()->SetComponentLocation(ColMap3Scale.Half());
	this->Roomes[4]->CreateEnvSprite("Castle5Door1.png", FVector2D(0, 645), FVector2D(141, 243), ERenderOrder::FIRST_FLOOR_OBJ);
	this->Roomes[4]->CreateEnvSprite("Castle5Door2.png", FVector2D(1395, 653), FVector2D(81, 235), ERenderOrder::FIRST_FLOOR_OBJ);
	this->Roomes[4]->CreateEnvSprite("Castle5Door3.png", FVector2D(688, 0), FVector2D(160, 96), ERenderOrder::SECOND_FLOOR_OBJ);
	this->Roomes[4]->CreateEnvSprite("Castle5Door4.png", FVector2D(0, 318), FVector2D(69, 135), ERenderOrder::SECOND_FLOOR_OBJ);

	this->Roomes[5]->SetIsSecondFloor(true);
	this->Roomes[5]->GetColSpriteRenderer2F()->SetOrder(ERenderOrder::COLMAP);
	this->Roomes[5]->GetColSpriteRenderer2F()->SetSprite("Castle6Collision2F.png");
	FVector2D ColMap4Scale = this->Roomes[5]->GetColSpriteRenderer2F()->SetSpriteScale(1.0f);
	this->Roomes[5]->GetColSpriteRenderer2F()->SetComponentLocation(ColMap4Scale.Half());
	this->Roomes[5]->CreateEnvSprite("Castle6Bridge.png", FVector2D(261, 336), FVector2D(243, 192), ERenderOrder::SECOND_FLOOR);
	this->Roomes[5]->CreateEnvSprite("Castle6Door1.png", FVector2D(624, 687), FVector2D(141, 165), ERenderOrder::FIRST_FLOOR_OBJ);
	this->Roomes[5]->CreateEnvSprite("Castle6Door2.png", FVector2D(696, 273), FVector2D(69, 225), ERenderOrder::SECOND_FLOOR_OBJ);
	this->Roomes[5]->CreateEnvSprite("Castle6Door3.png", FVector2D(288, 0), FVector2D(189, 165), ERenderOrder::FIRST_FLOOR_OBJ);
}

void AHyruleCastleGameMode::BeginPlayEnvActor()
{
	{
		AStatueFire* StatueFire = GetWorld()->SpawnActor<AStatueFire>();
		StatueFire->SetActorLocation({ 765 + 672, 1554 + 744 });
		StatueFire->SetCurRoom(Roomes[4]);

		AStatueFire* StatueFire2 = GetWorld()->SpawnActor<AStatueFire>();
		StatueFire2->SetActorLocation({ 765 + 816, 1554 + 744 });
		StatueFire2->SetCurRoom(Roomes[4]);

		AStatueStone* StatueStone1 = GetWorld()->SpawnActor<AStatueStone>();
		StatueStone1->SetActorLocation({ 765 + 288, 1554 + 648 });
		StatueStone1->SetCurRoom(Roomes[4]);

		AStatueStone* StatueStone2 = GetWorld()->SpawnActor<AStatueStone>();
		StatueStone2->SetActorLocation({ 765 + 384, 1554 + 648 });
		StatueStone2->SetCurRoom(Roomes[4]);

		AStatueStone* StatueStone3 = GetWorld()->SpawnActor<AStatueStone>();
		StatueStone3->SetActorLocation({ 765 + 480, 1554 + 648 });
		StatueStone3->SetCurRoom(Roomes[4]);

		AStatueStone* StatueStone4 = GetWorld()->SpawnActor<AStatueStone>();
		StatueStone4->SetActorLocation({ 765 + 1008, 1554 + 648 });
		StatueStone4->SetCurRoom(Roomes[4]);

		AStatueStone* StatueStone5 = GetWorld()->SpawnActor<AStatueStone>();
		StatueStone5->SetActorLocation({ 765 + 1104, 1554 + 648 });
		StatueStone5->SetCurRoom(Roomes[4]);

		AStatueStone* StatueStone6 = GetWorld()->SpawnActor<AStatueStone>();
		StatueStone6->SetActorLocation({ 765 + 1200, 1554 + 648 });
		StatueStone6->SetCurRoom(Roomes[4]);
	}

	{
		APot* Pot1 = GetWorld()->SpawnActor<APot>();
		Pot1->SetActorLocation({ 405, 305 });
		Pot1->SetCurRoom(Roomes[0], ERoomFloor::FLOOR_1F);

		APot* Pot2 = GetWorld()->SpawnActor<APot>();
		Pot2->SetActorLocation({ 453, 305 });
		Pot2->SetCurRoom(Roomes[0], ERoomFloor::FLOOR_1F);

		APot* Pot3 = GetWorld()->SpawnActor<APot>();
		Pot3->SetActorLocation({ 2445, 185 });
		Pot3->SetCurRoom(Roomes[2], ERoomFloor::FLOOR_2F);

		APot* Pot4 = GetWorld()->SpawnActor<APot>();
		Pot4->SetActorLocation({ 3117, 1289 });
		Pot4->SetCurRoom(Roomes[2], ERoomFloor::FLOOR_2F);
	
		APot* Pot5 = GetWorld()->SpawnActor<APot>();
		Pot5->SetActorLocation({ 3286, 2585 });
		Pot5->SetCurRoom(Roomes[3], ERoomFloor::FLOOR_2F);

		APot* Pot6 = GetWorld()->SpawnActor<APot>();
		Pot6->SetActorLocation({ 597, 1745 });
		Pot6->SetCurRoom(Roomes[5], ERoomFloor::FLOOR_2F);

		APot* Pot7 = GetWorld()->SpawnActor<APot>();
		Pot7->SetActorLocation({ 165, 1745 });
		Pot7->SetCurRoom(Roomes[5], ERoomFloor::FLOOR_2F);
	}
}

void AHyruleCastleGameMode::BeginPlayEnemyActor()
{
	ACastleKnight* EnemyCharacter = GetWorld()->SpawnActor<ACastleKnight>();
	EnemyCharacter->SetActorLocation({ 1358, 2449 });
	EnemyCharacter->SetSpeed(100.0f);
	EnemyCharacter->AddTurningLocation(FVector2D(1358, 2449));
	EnemyCharacter->AddTurningLocation(FVector2D(1547, 2449));
	EnemyCharacter->AddTurningLocation(FVector2D(1547, 2216));
	EnemyCharacter->AddTurningLocation(FVector2D(1358, 2216));
	CheckCharacterInRoom(EnemyCharacter);


	ACastleKnight* EnemyCharacter2 = GetWorld()->SpawnActor<ACastleKnight>();
	EnemyCharacter2->SetActorLocation({ 1681, 2384 });
	EnemyCharacter2->SetSpeed(100.0f);
	EnemyCharacter2->AddTurningLocation(FVector2D(1680, 2384));
	EnemyCharacter2->AddTurningLocation(FVector2D(1680, 2241));
	EnemyCharacter2->AddTurningLocation(FVector2D(1460, 2241));
	EnemyCharacter2->AddTurningLocation(FVector2D(1460, 2100));
	EnemyCharacter2->AddTurningLocation(FVector2D(1460, 2241));
	EnemyCharacter2->AddTurningLocation(FVector2D(1680, 2241));
	EnemyCharacter2->AddTurningLocation(FVector2D(1680, 2384));
	CheckCharacterInRoom(EnemyCharacter2);

	ACastleKnight* EnemyCharacter3 = GetWorld()->SpawnActor<ACastleKnight>();
	EnemyCharacter3->SetActorLocation({ 1640, 2200 });
	EnemyCharacter3->SetSpeed(100.0f);
	EnemyCharacter3->AddTurningLocation(FVector2D(1640, 2200));
	EnemyCharacter3->AddTurningLocation(FVector2D(1480, 2200));
	CheckCharacterInRoom(EnemyCharacter3);

	AHylianKnight* EnemyCharacter4 = GetWorld()->SpawnActor<AHylianKnight>();
	EnemyCharacter4->SetActorLocation({ 160, 1880 });
	EnemyCharacter4->SetSpeed(100.0f);
	EnemyCharacter4->AddTurningLocation(FVector2D(160, 1880));
	EnemyCharacter4->AddTurningLocation(FVector2D(160, 2800));
	EnemyCharacter4->SetCurRoomFloor(ERoomFloor::FLOOR_2F);
	CheckCharacterInRoom(EnemyCharacter4);

	ACastleKnight* EnemyCharacter5 = GetWorld()->SpawnActor<ACastleKnight>();
	EnemyCharacter5->SetActorLocation({ 350, 592 });
	EnemyCharacter5->SetSpeed(100.0f);
	EnemyCharacter5->AddTurningLocation(FVector2D(350, 592));
	EnemyCharacter5->AddTurningLocation(FVector2D(350, 892));
	CheckCharacterInRoom(EnemyCharacter5);
}
