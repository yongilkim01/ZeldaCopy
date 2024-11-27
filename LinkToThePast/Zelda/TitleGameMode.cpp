#include "PreCompile.h"
#include "TitleGameMode.h"
#include "TitleManager.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>

#include "TitleLogo.h"

ATitleGameMode::ATitleGameMode()
{
}

ATitleGameMode::~ATitleGameMode()
{
}

void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();
	ManagerActor = GetWorld()->SpawnActor<ATitleManager>();
	ManagerActor->SetActorLocation(FVector2D::ZERO);
}


void ATitleGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (true == UEngineInput::GetInst().IsDown(VK_SPACE))
	{
		ManagerActor->ChangeState(ETitleState::TITLE);
	}

	if (true == UEngineInput::GetInst().IsDown(VK_SPACE))
	{
		UEngineAPICore::GetCore()->OpenLevel("CastleDungeon");
		ManagerActor->StopSound();
	}

}