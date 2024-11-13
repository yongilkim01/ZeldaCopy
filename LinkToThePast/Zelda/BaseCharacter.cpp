#include "PreCompile.h"
#include "BaseCharacter.h"

ABaseCharacter::ABaseCharacter()
{

}

ABaseCharacter::~ABaseCharacter()
{

}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ABaseCharacter::AddCharacterLocation(FVector2D Location)
{

}
