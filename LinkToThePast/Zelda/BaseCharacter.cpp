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

FVector2D ABaseCharacter::GetDirectionToTargetLocation(FVector2D TargetLocation)
{
	FVector2D ResultDir = TargetLocation - GetActorLocation();
	ResultDir.Normalize();

	// Up 또는 Down
	if (UEngineMath::Abs(ResultDir.Y) > UEngineMath::Abs(ResultDir.X))
	{
		if (ResultDir.Y > 0.0f)
		{
			return FVector2D::DOWN;
		}
		else
		{
			return FVector2D::UP;
		}
	}
	else // Right 또는 Left
	{
		if (ResultDir.X > 0.0f)
		{
			return FVector2D::RIGHT;
		}
		else
		{
			return FVector2D::LEFT;
		}
	}

	return FVector2D::ZERO;
}

FVector2D ABaseCharacter::GetNormalDirectionToTargetLocation(FVector2D TargetLocation)
{
	FVector2D ResultDir = TargetLocation - GetActorLocation();
	ResultDir.Normalize();
	return ResultDir;
}

FVector2D ABaseCharacter::GetNormalDirectionToThisLocation(FVector2D TargetLocation)
{
	FVector2D ResultDir = GetActorLocation() - TargetLocation;
	ResultDir.Normalize();
	return ResultDir;
}

float ABaseCharacter::GetDistanceToTargetLocation(FVector2D TargetLocation)
{
	return GetActorLocation().DistanceTo(TargetLocation);
}