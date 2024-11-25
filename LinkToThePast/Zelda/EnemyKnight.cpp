#include "PreCompile.h"
#include "EnemyKnight.h"
#include "PlayerCharacter.h"
#include "ContentsEnum.h"
#include "EffectEnemyDeath.h"

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/Collision2D.h>

AEnemyKnight::AEnemyKnight()
{

}

AEnemyKnight::~AEnemyKnight()
{
}

void AEnemyKnight::BeginPlay()
{
	AEnemyCharacter::BeginPlay();

	// TODO: Test code
	this->PlayerCharacter = GetWorld()->GetPawn<APlayerCharacter>();
}

void AEnemyKnight::Tick(float DeltaTime)
{
	AEnemyCharacter::Tick(DeltaTime);

	PrintDebugInfo();
}

void AEnemyKnight::TakeDamage(int Damage, AActor* Character)
{
	if (CurEnemyState == EEnemyState::KnockBack) return;
	EffectSoundPlayer = UEngineSound::Play("enemy hit.wav");
	CurrentHP -= Damage;
	KnockBackDir = GetActorLocation() - Character->GetActorLocation();
	KnockBackDir.Normalize();
	KnockBackDir *= 100.0f;

	if (CurrentHP <= 0)
	{
		PrevEnemyState = CurEnemyState;
		CurEnemyState = EEnemyState::KnockBack;
	}
	PrevEnemyState = CurEnemyState;
	CurEnemyState = EEnemyState::KnockBack;
}

void AEnemyKnight::Fall()
{
	SetCurEnemyState(EEnemyState::Fall);
	SpriteRenderer->ChangeAnimation("Fall", true);

}
