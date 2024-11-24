#include "PreCompile.h"
#include "EnemyKnight.h"
#include "PlayerCharacter.h"
#include "EffectEnemyDeath.h"
#include "Room.h"
#include "DropKey.h"
#include "DropItem.h"

#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/SpriteRenderer.h>

void AEnemyKnight::Patrol(float DeltaTime)
{
	AEnemyCharacter::Patrol(DeltaTime);

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
		SetCurDirection(GetDirectionToTargetLocation(this->TurningLocations[CurTurningIndex]));
		ChangeMoveAnimation(GetCurDirection());
	}
	else
	{
		FVector2D CurEnemyLocation = GetActorLocation();
		FVector2D TurningLocation = this->TurningLocations[CurTurningIndex];

		FVector2D MoveDir = TurningLocation - CurEnemyLocation;
		MoveDir.Normalize();

		AddCharacterLocation(MoveDir * DeltaTime * Speed);
		SetCurDirection(GetDirectionToTargetLocation(this->TurningLocations[CurTurningIndex]));
		ChangeMoveAnimation(GetCurDirection());
	}

	if (IsRangeToPlayer() && PlayerCharacter->GetCurRoomFloor() == GetCurRoomFloor())
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

void AEnemyKnight::Trace(float DeltaTime)
{
	AttackCoolTime += DeltaTime;

	FVector2D PlayerLocation = this->PlayerCharacter->GetActorLocation();
	FVector2D EnemeyLocation = this->GetActorLocation();

	FVector2D TraceDir = PlayerLocation - EnemeyLocation;
	TraceDir.Normalize();

	AddCharacterLocation(TraceDir * DeltaTime * GetSpeed());
	//this->SpriteRenderer->SetOrder(this->SpriteRenderer->GetOrder() + (GetActorLocation().iY() / 100));

	SetCurDirection(GetDirectionToTargetLocation(PlayerLocation));

	ChangeMoveAnimation(GetCurDirection());

	if (GetDistanceToTargetLocation(PlayerLocation) < AttackRange)
	{
		CurEnemyState = EEnemyState::Attack;
	}
}

void AEnemyKnight::Attack(float DeltaTime)
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
			Result->TakeDamage(1, this);
		}
	}
	else if (GetCurDirection() == FVector2D::LEFT)
	{
		APlayerCharacter* Result = dynamic_cast<APlayerCharacter*>(AttackCollisions[1]->CollisionOnce(ECollisionGroup::PlayerBody));
		if (nullptr != Result)
		{
			Result->TakeDamage(1, this);
		}
	}
	else if (GetCurDirection() == FVector2D::DOWN)
	{
		APlayerCharacter* Result = dynamic_cast<APlayerCharacter*>(AttackCollisions[2]->CollisionOnce(ECollisionGroup::PlayerBody));
		if (nullptr != Result)
		{
			Result->TakeDamage(1, this);
		}
	}
	else if (GetCurDirection() == FVector2D::UP)
	{
		APlayerCharacter* Result = dynamic_cast<APlayerCharacter*>(AttackCollisions[3]->CollisionOnce(ECollisionGroup::PlayerBody));
		if (nullptr != Result)
		{
			Result->TakeDamage(1, this);
		}
	}
}

void AEnemyKnight::KnockBack(float DeltaTime)
{
	//KnockBackDir += FVector2D



	if (KnockBackCnt > 30)
	{
		CurEnemyState = PrevEnemyState;
		KnockBackCnt = 0;

		if (CurrentHP <= 0)
		{
			DeathEffect = GetWorld()->SpawnActor<AEffectEnemyDeath>();
			DeathEffect->SetActorLocation(GetActorLocation());
			GetCurRoom()->AddEnemyCount(-1);
			DeathEffect->SetOwnerActor(this);

			ADropItem* DropItem = nullptr;

			switch (DropItemType)
			{
			case EDropItemType::KEY:
				DropItem = GetWorld()->SpawnActor<ADropKeyItem>();
				DropItem->SetEventActorRenderOrder(SpriteRenderer->GetOrder() + 1);
				DropItem->SetActorLocation(GetActorLocation());
				break;
			case EDropItemType::LANTERN:
				break;
			case EDropItemType::HEART:
				break;
			case EDropItemType::BOW:
				break;
			default:
				break;
			}
		}

		return;
	}

	FVector2D PlayerLocation = this->PlayerCharacter->GetActorLocation();
	FVector2D EnemeyLocation = this->GetActorLocation();

	FVector2D KnockBackDir = EnemeyLocation - PlayerLocation;
	KnockBackDir.Normalize();

	AddCharacterLocation(KnockBackDir * DeltaTime * 1000.0f);

	FVector2D CheckLocation = GetActorLocation();
	CheckLocation -= GetCurRoom()->GetActorLocation();

	if (GetCollisionImage() != nullptr)
	{
		UColor CenterColor = GetCollisionImage()->GetColor(CheckLocation, UColor::PINK);
		UColor LeftTopColor = GetCollisionImage()->GetColor(CheckLocation + FVector2D{ -CollisionSize.X, 0.0f }, UColor::PINK);
		UColor LeftBottomColor = GetCollisionImage()->GetColor(CheckLocation + FVector2D{ -CollisionSize.X, CollisionSize.Y }, UColor::PINK);
		UColor RightTopColor = GetCollisionImage()->GetColor(CheckLocation + FVector2D{ CollisionSize.X, 0.0f }, UColor::PINK);
		UColor RightBottomColor = GetCollisionImage()->GetColor(CheckLocation + FVector2D{ CollisionSize.X, CollisionSize.Y }, UColor::PINK);

		if (CenterColor == UColor::FALL &&
			LeftTopColor == UColor::FALL &&
			LeftBottomColor == UColor::FALL &&
			RightTopColor == UColor::FALL &&
			RightBottomColor == UColor::FALL)
		{
			this->Fall();
			return;
		}
	}

	SetCurDirection(GetDirectionToTargetLocation(PlayerLocation));

	ChangeHitAnimation(GetCurDirection());

	KnockBackCnt++;
}