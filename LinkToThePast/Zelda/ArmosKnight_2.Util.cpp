#include "PreCompile.h"
#include "ArmosKnight.h"
#include "ArmosKngiht_Control.h"
#include "BaseCharacter.h"
#include "ContentsEnum.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision2D.h>
#include <EngineCore/Actor.h>


void AArmosKnight::TakeDamage(int Damage, AActor* Character)
{
	if (CurBossState == EBossState::KNOCKBACK) return;

	CurrentHP -= Damage;

	if (CurrentHP <= 0)
	{
		SpriteRenderer->ChangeAnimation("Death", true);
		ChangeState(EBossState::NONE);
		return;
	}

	ChangeState(EBossState::KNOCKBACK);
	SpriteRenderer->ChangeAnimation("Hit");
}

void AArmosKnight::Death()
{
	Manager->DestoryArmosKnight(this);
}

void AArmosKnight::Fall()
{
}

FVector2D AArmosKnight::GetHitLocation()
{
	return GetActorLocation() + SpriteRenderer->GetComponentLocation();
}

void AArmosKnight::AddBossComponentLocation(FVector2D Location)
{
	SpriteRenderer->AddComponentLocation(Location);
}

void AArmosKnight::SetBossComponentLocation(FVector2D Location)
{
	SpriteRenderer->SetComponentLocation(Location);
}

void AArmosKnight::CheckAttackCollision()
{
	ABaseCharacter* Result = dynamic_cast<ABaseCharacter*>(AttackCollision->CollisionOnce(ECollisionGroup::PlayerBody));

	if (nullptr != Result)
	{
		Result->TakeDamage(10, this);
	}
}
