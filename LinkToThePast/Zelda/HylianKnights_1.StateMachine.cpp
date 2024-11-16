#include "PreCompile.h"
#include "HylianKnights.h"
#include "PlayerCharacter.h"
#include "EffectEnemyDeath.h"

#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/SpriteRenderer.h>

void AHylianKnight::Patrol(float DeltaTime)
{
	AEnemyCharacter::Patrol(DeltaTime);

	if (this->TurningLocations[CurTurningIndex].DistanceTo(GetActorLocation()) < 10.0f)
	{
		// ��ȯ�� ���ؼ� ���� �ε����� ������ �ε������ 0���� �ʱ�ȭ
		if (this->CurTurningIndex == this->TurningLocations.size() - 1)
		{
			this->CurTurningIndex = 0;
		}
		else
		{
			this->CurTurningIndex++;
		}
		SetCurDirection(GetDirectionToTargetLocation(this->TurningLocations[CurTurningIndex]));
		ChangeMoveAnimation(GetCurDirection());
	}
	else
	{
		FVector2D CurEnemyLocation = GetActorLocation();
		FVector2D TurningLocation = this->TurningLocations[CurTurningIndex];

		FVector2D MoveDir = TurningLocation - CurEnemyLocation;
		MoveDir.Normalize();

		AddActorLocation(MoveDir * DeltaTime * Speed);
		this->SpriteRenderer->SetOrder(this->SpriteRenderer->GetOrder() + (GetActorLocation().iY() / 100));
		SetCurDirection(GetDirectionToTargetLocation(this->TurningLocations[CurTurningIndex]));
		ChangeMoveAnimation(GetCurDirection());
	}

	if (IsRangeToPlayer())
	{
		if (GetCurDirection() == FVector2D::RIGHT)
		{
			if (GetActorLocation().Y < PlayerCharacter->GetActorLocation().Y + 200.0f &&
				GetActorLocation().Y > PlayerCharacter->GetActorLocation().Y - 200.0f)
			{
				CurEnemyState = EEnemyState::Trace;
			}

		}
		else if (GetCurDirection() == FVector2D::LEFT)
		{
			if (GetActorLocation().Y < PlayerCharacter->GetActorLocation().Y + 200.0f &&
				GetActorLocation().Y > PlayerCharacter->GetActorLocation().Y - 200.0f)
			{
				CurEnemyState = EEnemyState::Trace;
			}

		}
		else if (GetCurDirection() == FVector2D::UP)
		{
			if (GetActorLocation().X < PlayerCharacter->GetActorLocation().X + 200.0f &&
				GetActorLocation().X > PlayerCharacter->GetActorLocation().X - 200.0f &&
				GetActorLocation().Y > PlayerCharacter->GetActorLocation().Y)
			{
				CurEnemyState = EEnemyState::Trace;
			}

		}
		else if (GetCurDirection() == FVector2D::DOWN)
		{
			if (GetActorLocation().X < PlayerCharacter->GetActorLocation().X + 100.0f &&
				GetActorLocation().X > PlayerCharacter->GetActorLocation().X - 100.0f &&
				GetActorLocation().Y < PlayerCharacter->GetActorLocation().Y)
			{
				CurEnemyState = EEnemyState::Trace;
			}

		}
	}
}

void AHylianKnight::Trace(float DeltaTime)
{
	AttackCoolTime += DeltaTime;

	FVector2D PlayerLocation = this->PlayerCharacter->GetActorLocation();
	FVector2D EnemeyLocation = this->GetActorLocation();

	FVector2D TraceDir = PlayerLocation - EnemeyLocation;
	TraceDir.Normalize();

	AddActorLocation(TraceDir * DeltaTime * GetSpeed());
	this->SpriteRenderer->SetOrder(this->SpriteRenderer->GetOrder() + (GetActorLocation().iY() / 100));

	SetCurDirection(GetDirectionToTargetLocation(PlayerLocation));

	ChangeMoveAnimation(GetCurDirection());

	if (GetDistanceToTargetLocation(PlayerLocation) < AttackRange)
	{
		CurEnemyState = EEnemyState::Attack;
	}
}

void AHylianKnight::Attack(float DeltaTime)
{
	if (GetDistanceToTargetLocation(this->PlayerCharacter->GetActorLocation()) > AttackRange)
	{
		CurEnemyState = EEnemyState::Trace;
		return;
	}

	if (GetCurDirection() == FVector2D::RIGHT)
	{
		APlayerCharacter* Result = dynamic_cast<APlayerCharacter*>(AttackCollisions[0]->CollisionOnce(ECollisionGroup::PlayerBody));
		if (nullptr != Result)
		{
			Result->TakeDamage(10, this);
		}
	}
	else if (GetCurDirection() == FVector2D::LEFT)
	{
		APlayerCharacter* Result = dynamic_cast<APlayerCharacter*>(AttackCollisions[1]->CollisionOnce(ECollisionGroup::PlayerBody));
		if (nullptr != Result)
		{
			Result->TakeDamage(10, this);
		}
	}
	else if (GetCurDirection() == FVector2D::DOWN)
	{
		APlayerCharacter* Result = dynamic_cast<APlayerCharacter*>(AttackCollisions[2]->CollisionOnce(ECollisionGroup::PlayerBody));
		if (nullptr != Result)
		{
			Result->TakeDamage(10, this);
		}
	}
	else if (GetCurDirection() == FVector2D::UP)
	{
		APlayerCharacter* Result = dynamic_cast<APlayerCharacter*>(AttackCollisions[3]->CollisionOnce(ECollisionGroup::PlayerBody));
		if (nullptr != Result)
		{
			Result->TakeDamage(10, this);
		}
	}
}

void AHylianKnight::KnockBack(float DeltaTime)
{
	if (KnockBackCnt > 30)
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
	this->SpriteRenderer->SetOrder(this->SpriteRenderer->GetOrder() + (GetActorLocation().iY() / 100));

	SetCurDirection(GetDirectionToTargetLocation(PlayerLocation));

	ChangeHitAnimation(GetCurDirection());

	KnockBackCnt++;
}