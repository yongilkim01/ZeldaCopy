#include "PreCompile.h"
#include "HylianKnights.h"
#include "PlayerCharacter.h"
#include "EffectEnemyDeath.h"

#include <EngineCore/EngineCoreDebug.h>

void AHylianKnights::Patrol(float DeltaTime)
{
	AEnemyCharacter::Patrol(DeltaTime);

	UEngineDebug::CoreOutPutString("Enemy State : Patrol");

	if (this->TurningLocations[CurTurningIndex].DistanceTo(GetActorLocation()) < 10.0f)
	{
		this->CurTurningIndex++;
		if (this->CurTurningIndex == this->TurningLocations.size())
		{
			this->CurTurningIndex = 0;
		}
		ChangeMoveAnimation(
			GetDirectionToTargetLocation(this->TurningLocations[CurTurningIndex])
		);
	}
	else
	{
		FVector2D CurEnemyLocation = GetActorLocation();
		FVector2D TurningLocation = this->TurningLocations[CurTurningIndex];

		FVector2D MoveDir = TurningLocation - CurEnemyLocation;
		MoveDir.Normalize();

		AddActorLocation(MoveDir * DeltaTime * Speed);
		ChangeMoveAnimation(
			GetDirectionToTargetLocation(this->TurningLocations[CurTurningIndex])
			);
	}

	if (IsRangeToPlayer())
	{
		SetCurEnemyState(EEnemyState::Trace);
	}
}

void AHylianKnights::Trace(float DeltaTime)
{
	UEngineDebug::CoreOutPutString("Enemy State : Trace");

	FVector2D PlayerLocation = this->PlayerCharacter->GetActorLocation();
	FVector2D EnemeyLocation = this->GetActorLocation();

	FVector2D TraceDir = PlayerLocation - EnemeyLocation;
	TraceDir.Normalize();

	AddActorLocation(TraceDir * DeltaTime * GetSpeed());

	CurrentDirection = GetDirectionToTargetLocation(PlayerLocation);

	ChangeMoveAnimation(CurrentDirection);

	if (GetDistanceToTargetLocation(PlayerLocation) < AttackRange)
	{
		CurEnemyState = EEnemyState::Attack;
	}
}

void AHylianKnights::Attack(float DeltaTime)
{
	UEngineDebug::CoreOutPutString("Enemy State : Attack");

	if (GetDistanceToTargetLocation(this->PlayerCharacter->GetActorLocation()) > AttackRange)
	{
		CurEnemyState = EEnemyState::Trace;
	}
}

void AHylianKnights::KnockBack(float DeltaTime)
{
	UEngineDebug::CoreOutPutString("Enemy State : KnockBack");

	if (KnockBackCnt > 80)
	{
		CurEnemyState = PrevEnemyState;
		KnockBackCnt = 0;

		if (CurrentHP <= 0)
		{
			DeathEffect = GetWorld()->SpawnActor<AEffectEnemyDeath>();
			DeathEffect->SetActorLocation(GetActorLocation());
			DeathEffect->SetOwnerActor(this);
		}

		return;
	}

	FVector2D PlayerLocation = this->PlayerCharacter->GetActorLocation();
	FVector2D EnemeyLocation = this->GetActorLocation();

	FVector2D KnockBackDir = EnemeyLocation - PlayerLocation;
	KnockBackDir.Normalize();

	AddActorLocation(KnockBackDir * DeltaTime * 1000.0f);

	CurrentDirection = GetDirectionToTargetLocation(PlayerLocation);

	ChangeHitAnimation(CurrentDirection);

	KnockBackCnt++;
}