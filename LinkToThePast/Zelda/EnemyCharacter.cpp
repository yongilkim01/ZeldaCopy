#include "PreCompile.h"
#include "EnemyCharacter.h"
#include "PlayerCharacter.h"

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
	case EEnemyState::Idle:
		Idle(DeltaTime);
		break;
	case EEnemyState::Move:
		Move(DeltaTime);
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

void AEnemyCharacter::Idle(float DeltaTime)
{
	//if (this->TurningLocations[CurTurningIndex].DistanceTo(GetActorLocation()) < 10.0f)
	//{
	//	this->CurTurningIndex++;
	//	if (this->CurTurningIndex == this->TurningLocations.size())
	//	{
	//		this->CurTurningIndex = 0;
	//	}
	//}
	//else
	//{ 
	//	FVector2D CurEnemyLocation = GetActorLocation();
	//	FVector2D TurningLocation = this->TurningLocations[CurTurningIndex];

	//	FVector2D MoveDir = TurningLocation - CurEnemyLocation;
	//	MoveDir.Normalize();

	//	AddActorLocation(MoveDir * DeltaTime * Speed);
	//}
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

float AEnemyCharacter::GetDegree(FVector2D TargetLocation)
{
	FVector2D ResultDir = TargetLocation - GetActorLocation();
	ResultDir.Normalize();

	int DirY = EngineMath::Abs(ResultDir.iY());
	int DirX = EngineMath::Abs(ResultDir.iX());
	UEngineDebug::CoreOutPutString("Player to enemy vector : " + ResultDir.ToString());
	
	if (ResultDir.iY() > ResultDir.iX()) // Up 또는 Down
	{
		UEngineDebug::CoreOutPutString("Player position up or down");
	}
	else // Right 또는 Left
	{
		UEngineDebug::CoreOutPutString("Player position right or left");
	}

	return 0.0f;
}

void AEnemyCharacter::PrintEnemyDebugInfo()
{
	UEngineDebug::CoreOutPutString("Enemy HP : " + std::to_string(this->CurrentHP));
	UEngineDebug::CoreOutPutString("Enemy Speed : " + std::to_string(this->Speed));
}