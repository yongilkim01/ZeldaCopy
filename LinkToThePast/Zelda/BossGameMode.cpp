#include "PreCompile.h"
#include "BossGameMode.h"
#include "Room.h"
#include "ArmosKngiht_Control.h"

#include <EngineCore/EngineAPICore.h>

ABossGameMode::ABossGameMode()
{

}

ABossGameMode::~ABossGameMode()
{
}

void ABossGameMode::BeginPlay()
{
	AZeldaGameMode::BeginPlay();

	BeginPlayRoomActor();
	BeginPlayUI();

	CheckCollisionRoom();

	{
		FVector2D WindowHalfSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half();
		AArmosKngiht_Control* Control = GetWorld()->SpawnActor<AArmosKngiht_Control>();
		Control->SetCurRoom(Roomes[0], false);
		Control->SetPlayerCharacter(PlayerCharacter);
		Control->SetActorLocation(WindowHalfSize);
	}

}

void ABossGameMode::Tick(float DeltaTime)
{
	AZeldaGameMode::Tick(DeltaTime);
}

void ABossGameMode::BeginPlayRoomActor()
{
	Roomes.reserve(10);
	RoomDataes.reserve(10);

	RoomDataes.push_back({ { 0, 0 } ,{ 768, 672 } });

	CreateRoomActor("CastleDungeonBoss", 0);

	Roomes[0]->CreateEnvSprite("CastleDungeonBoss1Door1.png", FVector2D(320, 615), FVector2D(128, 57), ERenderOrder::FIRST_FLOOR_OBJ);
}
