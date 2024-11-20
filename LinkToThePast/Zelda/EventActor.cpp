#include "PreCompile.h"
#include "EventActor.h"

AEventActor::AEventActor()
{

}

AEventActor::~AEventActor()
{
}

void AEventActor::BeginPlay()
{
	Super::BeginPlay();
}

void AEventActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEventActor::HoldToCharacter(FVector2D CharacterDirction)
{
	if (CharacterDirction == FVector2D::RIGHT)
	{

	}
	else if (CharacterDirction == FVector2D::LEFT)
	{

	}
	else if (CharacterDirction == FVector2D::UP)
	{

	}
	else if (CharacterDirction == FVector2D::DOWN)
	{

	}
}

