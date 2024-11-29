#include "PreCompile.h"
#include "LightWorldGameMode.h"
#include "ContentsEnum.h"
#include "Room.h"
#include "HouseBed.h"
#include "UIBox.h"
#include "Fade.h"
#include "PlayerCharacter.h"
#include "LinkFather.h"
#include "Grass.h"
#include "Chest.h"
#include "SoundManager.h"
#include "LevelMove.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>

ALightWorldGameMode::ALightWorldGameMode()
{

}

ALightWorldGameMode::~ALightWorldGameMode()
{
}

void ALightWorldGameMode::BeginPlay()
{
	AZeldaGameMode::BeginPlay();

	Player = GetWorld()->GetPawn<APlayerCharacter>();

	BeginPlayRoomActor();
	BeginPlayEnvActor();
	BeginPlayEnemyActor();
	BeginPlayUI();

	ALevelMove* LevelMove1 = GetWorld()->SpawnActor<ALevelMove>();
	LevelMove1->SetActorLocation({ 1532, 220 });
	LevelMove1->SetMoveLevelName("CastleDungeon");

	Fade = GetWorld()->SpawnActor<AFade>();
	Fade->SetFadeSize(EFadeSize::BIG);
	Fade->FadeOut();

}


void ALightWorldGameMode::BeginPlayRoomActor()
{
	Roomes.reserve(2);
	RoomDataes.reserve(2);

	RoomDataes.push_back({ { 0, 0 } ,{ 3072, 3072 } });
	RoomDataes.push_back({ { 1536, 3072 } ,{ 1533, 1536 } });

	CreateRoomActor("LightWorld", 1);

	this->Roomes[1]->SetIsSecondFloor(true);
	this->Roomes[1]->GetColSpriteRenderer2F()->SetOrder(ERenderOrder::COLMAP);
	this->Roomes[1]->GetColSpriteRenderer2F()->SetSprite("LightWorld2Collision2F.png");
	FVector2D ColMap2Scale = this->Roomes[1]->GetColSpriteRenderer2F()->SetSpriteScale(1.0f);
	this->Roomes[1]->GetColSpriteRenderer2F()->SetComponentLocation(ColMap2Scale.Half());
	this->Roomes[1]->SetStartSecondFloor(true);

	SetCurRoom(1);
}

void ALightWorldGameMode::BeginPlayEnvActor()
{
	{
		AGrass* Grass1 = GetWorld()->SpawnActor<AGrass>();
		Grass1->SetActorLocation({ Roomes[1]->GetActorLocation().iX() + 697, Roomes[1]->GetActorLocation().iY() + 842});
		Grass1->SetCurRoom(Roomes[1], ERoomFloor::FLOOR_2F);

		AGrass* Grass2 = GetWorld()->SpawnActor<AGrass>();
		Grass2->SetActorLocation({ Roomes[1]->GetActorLocation().iX() + 697, Roomes[1]->GetActorLocation().iY() + 842 + 48 });
		Grass2->SetCurRoom(Roomes[1], ERoomFloor::FLOOR_2F);

		AGrass* Grass3 = GetWorld()->SpawnActor<AGrass>();
		Grass3->SetActorLocation({ Roomes[1]->GetActorLocation().iX() + 697 + 48, Roomes[1]->GetActorLocation().iY() + 842 });
		Grass3->SetCurRoom(Roomes[1], ERoomFloor::FLOOR_2F);

		AGrass* Grass4 = GetWorld()->SpawnActor<AGrass>();
		Grass4->SetActorLocation({ Roomes[1]->GetActorLocation().iX() + 697 + 48, Roomes[1]->GetActorLocation().iY() + 842 + 48 });
		Grass4->SetCurRoom(Roomes[1], ERoomFloor::FLOOR_2F);
	}
	//{
	//	APot* Pot = GetWorld()->SpawnActor<APot>();
	//	Pot->SetActorLocation({ 144, 285 });
	//	Pot->SetCurRoom(Roomes[0], ERoomFloor::FLOOR_1F);
	//}
	//{
	//	APot* Pot = GetWorld()->SpawnActor<APot>();
	//	Pot->SetActorLocation({ 144, 333 });
	//	Pot->SetCurRoom(Roomes[0], ERoomFloor::FLOOR_1F);
	//}
	//{
	//	AChest* Chest = GetWorld()->SpawnActor<AChest>();
	//	Chest->SetActorLocation({ 600, 500 });
	//	Chest->SetCurRoom(Roomes[0], ERoomFloor::FLOOR_1F);
	//	Chest->SetDropItemType(EDropItemType::LANTERN);
	//}
}

void ALightWorldGameMode::Tick(float DeltaTime)
{
	AZeldaGameMode::Tick(DeltaTime);

}