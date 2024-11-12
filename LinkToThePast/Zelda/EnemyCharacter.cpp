#include "PreCompile.h"
#include "EnemyCharacter.h"
#include "PlayerCharacter.h"

#include <EngineBase/EngineMath.h>

#include <EngineCore/EngineCoreDebug.h>

AEnemyCharacter::AEnemyCharacter()
{
}

AEnemyCharacter::~AEnemyCharacter()
{
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PrintEnemyDebugInfo();

	switch (CurEnemyState)
	{
	case EEnemyState::Patrol:
		Patrol(DeltaTime);
		break;
	case EEnemyState::Attack:
		Attack(DeltaTime);
		break;
	case EEnemyState::KnockBack:
		KnockBack(DeltaTime);
		break;
	case EEnemyState::Trace:
		Trace(DeltaTime);
		break;
	default:
		break;
	}
}

float AEnemyCharacter::CheckDistanceToPlayer()
{
	if (this->PlayerCharacter != nullptr)
	{
		float Distance = GetActorLocation().DistanceTo(this->PlayerCharacter->GetActorLocation());
		return GetActorLocation().DistanceTo(this->PlayerCharacter->GetActorLocation());
	}
	return 0.0f;
}

bool AEnemyCharacter::IsRangeToPlayer()
{
	return (CheckDistanceToPlayer()) < DetectionRange;
}

FVector2D AEnemyCharacter::GetDirectionToTargetLocation(FVector2D TargetLocation)
{
	FVector2D ResultDir = TargetLocation - GetActorLocation();
	ResultDir.Normalize();
	
	// Up 또는 Down
	if (EngineMath::Abs(ResultDir.Y) > EngineMath::Abs(ResultDir.X))
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

float AEnemyCharacter::GetDistanceToTargetLocation(FVector2D TargetLocation)
{
	return GetActorLocation().DistanceTo(TargetLocation);
}

void AEnemyCharacter::PrintEnemyDebugInfo()
{
	UEngineDebug::CoreOutPutString("Enemy HP : " + std::to_string(this->CurrentHP));
	UEngineDebug::CoreOutPutString("Enemy Speed : " + std::to_string(this->Speed));
}