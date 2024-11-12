#include "PreCompile.h"
#include "HylianKnights.h"
#include "PlayerCharacter.h"
#include "ContentsEnum.h"
#include "EffectEnemyDeath.h"

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/Collision2D.h>

AHylianKnights::AHylianKnights()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("HylianKnightMoveDown.png");
		SpriteRenderer->SetComponentScale(FVector2D(1.0f, 1.0f));
		SpriteRenderer->SetSpriteScale(3.0f);
		SpriteRenderer->CreateAnimation("Idle_Down", "HylianKnightMoveDown.png", 0, 0, 0.1f);

		SpriteRenderer->CreateAnimation("Move_Right", "HylianKnightMoveRight.png", 0, 2, 0.3f);
		SpriteRenderer->CreateAnimation("Move_Left", "HylianKnightMoveLeft.png", 0, 2, 0.3f);
		SpriteRenderer->CreateAnimation("Move_Up", "HylianKnightMoveUp.png", 0, 2, 0.3f);
		SpriteRenderer->CreateAnimation("Move_Down", "HylianKnightMoveDown.png", 0, 2, 0.3f);

		SpriteRenderer->CreateAnimation("Hit_Right", "HylianKnightHit.png", 4, 7, 0.05f);
		SpriteRenderer->CreateAnimation("Hit_Left", "HylianKnightHit.png", 8, 11, 0.05f);
		SpriteRenderer->CreateAnimation("Hit_Up", "HylianKnightHit.png", 12, 15, 0.05f);
		SpriteRenderer->CreateAnimation("Hit_Down", "HylianKnightHit.png", 0, 3, 0.05f);

		SpriteRenderer->ChangeAnimation("Move_Down");

	}
	{
		CollisionComponent = CreateDefaultSubObject<UCollision2D>();
		CollisionComponent->SetComponentLocation({ 0, 0 });
		CollisionComponent->SetComponentScale({ 60, 75 });
		CollisionComponent->SetCollisionGroup(ECollisionGroup::EnemyBody);
		CollisionComponent->SetCollisionType(ECollisionType::Rect);
	}
}

AHylianKnights::~AHylianKnights()
{
}

void AHylianKnights::BeginPlay()
{
	AEnemyCharacter::BeginPlay();

	// TODO: Test code
	this->PlayerCharacter = GetWorld()->GetPawn<APlayerCharacter>();

	// Set base parameter
	SetSpeed(150.0f);

	// Set turning locations
	AddTurningLocation(FVector2D(2332, 1724));
	AddTurningLocation(FVector2D(2332, 1974));
}

void AHylianKnights::Tick(float DeltaTime)
{
	AEnemyCharacter::Tick(DeltaTime);
}

void AHylianKnights::TakeDamage(int Damage)
{
	if (CurEnemyState == EEnemyState::KnockBack) return;
	CurrentHP -= Damage;

	if (CurrentHP <= 0)
	{
		PrevEnemyState = CurEnemyState;
		CurEnemyState = EEnemyState::KnockBack;
	}
	PrevEnemyState = CurEnemyState;
	CurEnemyState = EEnemyState::KnockBack;
}