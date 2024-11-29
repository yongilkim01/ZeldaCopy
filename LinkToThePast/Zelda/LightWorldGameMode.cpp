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
	{
		WeatherRenderer = CreateDefaultSubObject<USpriteRenderer>();
		WeatherRenderer->SetSprite("Rain.png", 0);
		WeatherRenderer->CreateAnimation("Rain", "Rain.png", 0, 3, 0.1f);
		WeatherRenderer->ChangeAnimation("Rain");
		FVector2D Location = WeatherRenderer->SetSpriteScale(1.0f);
		WeatherRenderer->SetComponentLocation(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half());
		WeatherRenderer->SetOrder(ERenderOrder::FADE_FIRST);
		WeatherRenderer->SetCameraEffect(false);
		WeatherRenderer->SetActive(true);
	}

	{
		FadeRenderer = CreateDefaultSubObject<USpriteRenderer>();
		FadeRenderer->SetSprite("Fade.bmp");
		FVector2D Location = FadeRenderer->SetSpriteScale(1.0f);
		FadeRenderer->SetComponentLocation(Location.Half());
		FadeRenderer->SetOrder(ERenderOrder::FADE_FIRST);
		FadeRenderer->SetAlphafloat(0.6f);
		FadeRenderer->SetCameraEffect(false);
		FadeRenderer->SetActive(true);
	}
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
	LevelMove1->SetActorLocation({ 2712, 504 });
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
		Grass1->SetActorLocation({ 2712, 504 });
		Grass1->SetCurRoom(Roomes[0], ERoomFloor::FLOOR_1F);

		/////////////////////////////////////////////////

		AGrass* Grass2 = GetWorld()->SpawnActor<AGrass>();
		Grass2->SetActorLocation({ 2184, 840 });
		Grass2->SetCurRoom(Roomes[0], ERoomFloor::FLOOR_1F);

		AGrass* Grass3 = GetWorld()->SpawnActor<AGrass>();
		Grass3->SetActorLocation({ 2184 - 48 , 840 });
		Grass3->SetCurRoom(Roomes[0], ERoomFloor::FLOOR_1F);

		/////////////////////////////////////////////////

		AGrass* Grass4 = GetWorld()->SpawnActor<AGrass>();
		Grass4->SetActorLocation({ 2184, 936 });
		Grass4->SetCurRoom(Roomes[0], ERoomFloor::FLOOR_1F);

		AGrass* Grass5 = GetWorld()->SpawnActor<AGrass>();
		Grass5->SetActorLocation({ 2184 - 48 , 936 });
		Grass5->SetCurRoom(Roomes[0], ERoomFloor::FLOOR_1F);

		AGrass* Grass6 = GetWorld()->SpawnActor<AGrass>();
		Grass6->SetActorLocation({ 2184, 936 + 48 });
		Grass6 ->SetCurRoom(Roomes[0], ERoomFloor::FLOOR_1F);

		AGrass* Grass7 = GetWorld()->SpawnActor<AGrass>();
		Grass7->SetActorLocation({ 2184 - 48 , 936 + 48 });
		Grass7->SetCurRoom(Roomes[0], ERoomFloor::FLOOR_1F);

		AGrass* Grass8 = GetWorld()->SpawnActor<AGrass>();
		Grass8->SetActorLocation({ 2184, 936 + 96});
		Grass8->SetCurRoom(Roomes[0], ERoomFloor::FLOOR_1F);

		AGrass* Grass9 = GetWorld()->SpawnActor<AGrass>();
		Grass9->SetActorLocation({ 2184 - 48 , 936 + 96});
		Grass9->SetCurRoom(Roomes[0], ERoomFloor::FLOOR_1F);

		AGrass* Grass10 = GetWorld()->SpawnActor<AGrass>();
		Grass10->SetActorLocation({ 2184, 936 + 144 });
		Grass10->SetCurRoom(Roomes[0], ERoomFloor::FLOOR_1F);

		AGrass* Grass11 = GetWorld()->SpawnActor<AGrass>();
		Grass11->SetActorLocation({ 2184 - 48 , 936 + 144 });
		Grass11->SetCurRoom(Roomes[0], ERoomFloor::FLOOR_1F);
		
		//////////////////////////////////////////////////

		AGrass* Grass12 = GetWorld()->SpawnActor<AGrass>();
		Grass12->SetActorLocation({ 2184, 1224 });
		Grass12->SetCurRoom(Roomes[0], ERoomFloor::FLOOR_1F);

		AGrass* Grass13 = GetWorld()->SpawnActor<AGrass>();
		Grass13->SetActorLocation({ 2184 - 48 , 1224 });
		Grass13->SetCurRoom(Roomes[0], ERoomFloor::FLOOR_1F);

		AGrass* Grass14 = GetWorld()->SpawnActor<AGrass>();
		Grass14->SetActorLocation({ 2184 - 96, 1224 });
		Grass14->SetCurRoom(Roomes[0], ERoomFloor::FLOOR_1F);

		AGrass* Grass15 = GetWorld()->SpawnActor<AGrass>();
		Grass15->SetActorLocation({ 2184 - 144 , 1224 });
		Grass15->SetCurRoom(Roomes[0], ERoomFloor::FLOOR_1F);

		//////////////////////////////////////////////////

		AGrass* Grass16 = GetWorld()->SpawnActor<AGrass>();
		Grass16->SetActorLocation({ 2040, 1224 });
		Grass16->SetCurRoom(Roomes[0], ERoomFloor::FLOOR_1F);

		AGrass* Grass17 = GetWorld()->SpawnActor<AGrass>();
		Grass17->SetActorLocation({ 2040 - 48 , 1224 });
		Grass17->SetCurRoom(Roomes[0], ERoomFloor::FLOOR_1F);

		AGrass* Grass18 = GetWorld()->SpawnActor<AGrass>();
		Grass18->SetActorLocation({ 2040 - 96, 1224 });
		Grass18->SetCurRoom(Roomes[0], ERoomFloor::FLOOR_1F);

		AGrass* Grass19 = GetWorld()->SpawnActor<AGrass>();
		Grass19->SetActorLocation({ 2040 - 144 , 1224 });
		Grass19->SetCurRoom(Roomes[0], ERoomFloor::FLOOR_1F);

		AGrass* Grass20 = GetWorld()->SpawnActor<AGrass>();
		Grass20->SetActorLocation({ 2040 - 96 , 1224 + 48});
		Grass20->SetCurRoom(Roomes[0], ERoomFloor::FLOOR_1F);

		AGrass* Grass21 = GetWorld()->SpawnActor<AGrass>();
		Grass21->SetActorLocation({ 2040 - 144 , 1224 + 48 });
		Grass21->SetCurRoom(Roomes[0], ERoomFloor::FLOOR_1F);

		//////////////////////////////////////////////////

		AGrass* Grass22 = GetWorld()->SpawnActor<AGrass>();
		Grass22->SetActorLocation({ 1848, 840 });
		Grass22->SetCurRoom(Roomes[0], ERoomFloor::FLOOR_1F);

		AGrass* Grass23 = GetWorld()->SpawnActor<AGrass>();
		Grass23->SetActorLocation({ 1848 , 840 + 48	 });
		Grass23->SetCurRoom(Roomes[0], ERoomFloor::FLOOR_1F);

	}

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

		AGrass* Grass5 = GetWorld()->SpawnActor<AGrass>();
		Grass5->SetActorLocation({ Roomes[1]->GetActorLocation().iX() + 456, Roomes[1]->GetActorLocation().iY() + 842});
		Grass5->SetCurRoom(Roomes[1], ERoomFloor::FLOOR_2F);

		AGrass* Grass6 = GetWorld()->SpawnActor<AGrass>();
		Grass6->SetActorLocation({ Roomes[1]->GetActorLocation().iX() + 456, Roomes[1]->GetActorLocation().iY() + 842 + 48 });
		Grass6->SetCurRoom(Roomes[1], ERoomFloor::FLOOR_2F);

		AGrass* Grass7 = GetWorld()->SpawnActor<AGrass>();
		Grass7->SetActorLocation({ Roomes[1]->GetActorLocation().iX() + 456 - 48, Roomes[1]->GetActorLocation().iY() + 842 });
		Grass7->SetCurRoom(Roomes[1], ERoomFloor::FLOOR_2F);

		AGrass* Grass8 = GetWorld()->SpawnActor<AGrass>();
		Grass8->SetActorLocation({ Roomes[1]->GetActorLocation().iX() + 456 - 48, Roomes[1]->GetActorLocation().iY() + 842 + 48 });
		Grass8->SetCurRoom(Roomes[1], ERoomFloor::FLOOR_2F);

		AGrass* Grass9 = GetWorld()->SpawnActor<AGrass>();
		Grass9->SetActorLocation({ Roomes[1]->GetActorLocation().iX() + 456 - 96, Roomes[1]->GetActorLocation().iY() + 842 });
		Grass9->SetCurRoom(Roomes[1], ERoomFloor::FLOOR_2F);

		AGrass* Grass10 = GetWorld()->SpawnActor<AGrass>();
		Grass10->SetActorLocation({ Roomes[1]->GetActorLocation().iX() + 456 - 96, Roomes[1]->GetActorLocation().iY() + 842 + 48 });
		Grass10->SetCurRoom(Roomes[1], ERoomFloor::FLOOR_2F);
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