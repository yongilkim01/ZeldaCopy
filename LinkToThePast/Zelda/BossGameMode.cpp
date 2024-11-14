#include "PreCompile.h"
#include "BossGameMode.h"
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

	RoomBeginPlay();
	UIBeginPlay();

	CheckCollisionRoom();

	{
		FVector2D WindowHalfSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half();
		AArmosKngiht_Control* Control = GetWorld()->SpawnActor<AArmosKngiht_Control>();
		Control->SetActorLocation(WindowHalfSize);
	}

}

void ABossGameMode::Tick(float DeltaTime)
{
	AZeldaGameMode::Tick(DeltaTime);
}

void ABossGameMode::RoomBeginPlay()
{
	Roomes.reserve(10);
	RoomDataes.reserve(10);

	RoomDataes.push_back({ { 0, 0 } ,{ 768, 672 } });

	CreateRoomActor("CastleDungeonBoss", 0);
}
