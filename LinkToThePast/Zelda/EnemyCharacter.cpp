#include "PreCompile.h"
#include "EnemyCharacter.h"

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