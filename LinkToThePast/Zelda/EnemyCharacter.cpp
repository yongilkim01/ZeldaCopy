#include "PreCompile.h"
#include "EnemyCharacter.h"
#include "PlayerCharacter.h"
#include "EffectEnemyDeath.h"

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
	ABaseCharacter::BeginPlay();
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	ABaseCharacter::Tick(DeltaTime);

	if (this->DeathEffect != nullptr && GetDeathEffectAnimationIsEnd() == false) return;

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

bool AEnemyCharacter::GetDeathEffectAnimationIsEnd()
{
	return this->DeathEffect->GetAnimationIsEnd();
}