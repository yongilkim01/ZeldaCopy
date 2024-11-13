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
		// 순환을 위해서 현재 인덱스가 마지막 인덱스라면 0으로 초기화
		if (this->CurTurningIndex == this->TurningLocations.size() - 1)
		{
			this->CurTurningIndex = 0;
		}
		else
		{
			this->CurTurningIndex++;
		}
		this->CurDir = GetDirectionToTargetLocation(this->TurningLocations[CurTurningIndex]);
		ChangeMoveAnimation(CurDir);
	}
	else
	{
		FVector2D CurEnemyLocation = GetActorLocation();
		FVector2D TurningLocation = this->TurningLocations[CurTurningIndex];

		FVector2D MoveDir = TurningLocation - CurEnemyLocation;
		MoveDir.Normalize();

		AddActorLocation(MoveDir * DeltaTime * Speed);
		this->CurDir = GetDirectionToTargetLocation(this->TurningLocations[CurTurningIndex]);
		ChangeMoveAnimation(CurDir);
	}

	if (IsRangeToPlayer())
	{
		if (CurDir == FVector2D::RIGHT)
		{
			UEngineDebug::CoreOutPutString("Enemy Direction : Right");

			if (GetActorLocation().Y < PlayerCharacter->GetActorLocation().Y + 200.0f &&
				GetActorLocation().Y > PlayerCharacter->GetActorLocation().Y - 200.0f)
			{
				CurEnemyState = EEnemyState::Trace;
			}

		}
		else if (CurDir == FVector2D::LEFT)
		{
			UEngineDebug::CoreOutPutString("Enemy Direction : Left");

			if (GetActorLocation().Y < PlayerCharacter->GetActorLocation().Y + 200.0f &&
				GetActorLocation().Y > PlayerCharacter->GetActorLocation().Y - 200.0f)
			{
				CurEnemyState = EEnemyState::Trace;
			}

		}
		else if (CurDir == FVector2D::UP)
		{
			UEngineDebug::CoreOutPutString("Enemy Direction : Up");

			if (GetActorLocation().X < PlayerCharacter->GetActorLocation().X + 200.0f &&
				GetActorLocation().X > PlayerCharacter->GetActorLocation().X - 200.0f &&
				GetActorLocation().Y > PlayerCharacter->GetActorLocation().Y)
			{
				CurEnemyState = EEnemyState::Trace;
			}

		}
		else if (CurDir == FVector2D::DOWN)
		{
			UEngineDebug::CoreOutPutString("Enemy Direction : Down");


			if (GetActorLocation().X < PlayerCharacter->GetActorLocation().X + 100.0f &&
				GetActorLocation().X > PlayerCharacter->GetActorLocation().X - 100.0f &&
				GetActorLocation().Y < PlayerCharacter->GetActorLocation().Y)
			{
				CurEnemyState = EEnemyState::Trace;
			}

		}
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

	if (this->CurDir == FVector2D::RIGHT)
	{
		IsAttack = true;
		APlayerCharacter* Result = dynamic_cast<APlayerCharacter*>(AttackCollisions[0]->CollisionOnce(ECollisionGroup::PlayerBody));
		if (nullptr != Result)
		{
			Result->TakeDamage(10, this);
		}
	}
	else if (this->CurDir == FVector2D::LEFT)
	{
		IsAttack = true;
		APlayerCharacter* Result = dynamic_cast<APlayerCharacter*>(AttackCollisions[1]->CollisionOnce(ECollisionGroup::PlayerBody));
		if (nullptr != Result)
		{
			Result->TakeDamage(10, this);
		}
	}
	else if (this->CurDir == FVector2D::DOWN)
	{
		IsAttack = true;
		APlayerCharacter* Result = dynamic_cast<APlayerCharacter*>(AttackCollisions[2]->CollisionOnce(ECollisionGroup::PlayerBody));
		if (nullptr != Result)
		{
			Result->TakeDamage(10, this);
		}
	}
	else if (this->CurDir == FVector2D::UP)
	{
		IsAttack = true;
		APlayerCharacter* Result = dynamic_cast<APlayerCharacter*>(AttackCollisions[3]->CollisionOnce(ECollisionGroup::PlayerBody));
		if (nullptr != Result)
		{
			Result->TakeDamage(10, this);
		}
	}
}

void AHylianKnights::KnockBack(float DeltaTime)
{
	UEngineDebug::CoreOutPutString("Enemy State : KnockBack");

	if (KnockBackCnt > 50)
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