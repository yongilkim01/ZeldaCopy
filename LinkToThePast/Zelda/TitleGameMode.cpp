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

	if (true == UEngineInput::GetInst().IsDown(VK_SPACE) ||
		true == UEngineInput::GetInst().IsDown(VK_RETURN))
	{
		ManagerActor->ChangeState(ETitleState::TITLE);
	}
}