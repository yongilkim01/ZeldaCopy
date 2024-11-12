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

void AEnemyCharacter::TakeDamage(int Damage)
{
	CurrentHP -= Damage;

	if (CurrentHP <= 0)
	{
		this->Destroy();
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

	float DirY = EngineMath::Abs(ResultDir.Y);
	float DirX = EngineMath::Abs(ResultDir.X);
	UEngineDebug::CoreOutPutString("Player to enemy vector : " + ResultDir.ToString());
	
	if (DirY > DirX) // Up 또는 Down
	{
		if (ResultDir.Y > 0.0f)
		{
			UEngineDebug::CoreOutPutString("Player position is down");
			return FVector2D::DOWN;
		}
		else
		{
			UEngineDebug::CoreOutPutString("Player position is up");
			return FVector2D::UP;
		}
	}
	else // Right 또는 Left
	{
		if (ResultDir.X > 0.0f)
		{
			UEngineDebug::CoreOutPutString("Player position is right");
			return FVector2D::RIGHT;
		}
		else
		{
			UEngineDebug::CoreOutPutString("Player position is left");
			return FVector2D::LEFT;
		}
	}

	return FVector2D::ZERO;
}

void AEnemyCharacter::PrintEnemyDebugInfo()
{
	UEngineDebug::CoreOutPutString("Enemy HP : " + std::to_string(this->CurrentHP));
	UEngineDebug::CoreOutPutString("Enemy Speed : " + std::to_string(this->Speed));
}