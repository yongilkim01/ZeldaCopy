#include "PreCompile.h"
#include "HylianKnights.h"

#include "PlayerCharacter.h"
#include "ContentsEnum.h"

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

		SpriteRenderer->ChangeAnimation("Move_Down");

	}
	{
		UCollision2D* CollisionComponent = CreateDefaultSubObject<UCollision2D>();
		CollisionComponent->SetComponentLocation({ 0, 0 });
		CollisionComponent->SetComponentScale({ 60, 75 });
		CollisionComponent->SetCollisionGroup(ECollisionGroup::EnemyBody);
		CollisionComponent->SetCollisionType(ECollisionType::Rect);
		//DebugOn();
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
	//2332, 1724
}

void AHylianKnights::Tick(float DeltaTime)
{
	AEnemyCharacter::Tick(DeltaTime);
}

void AHylianKnights::Patrol(float DeltaTime)
{
	AEnemyCharacter::Patrol(DeltaTime);

	UEngineDebug::CoreOutPutString("Enemy State : Idle");
	UEngineDebug::CoreOutPutString("Player to Distance : " + std::to_string(CheckDistanceToPlayer()));

	//if (IsRangeToPlayer())
	//{
	//	SetCurEnemyState(EEnemyState::Trace);
	//}
	//UEngineDebug::CoreOutPutString("Player to Distance : " + std::to_string(CheckDistanceToPlayer()));

	FVector2D KnightDir = GetDirectionToTargetLocation(PlayerCharacter->GetActorLocation());

	if (KnightDir == FVector2D::RIGHT)
	{
		this->SpriteRenderer->ChangeAnimation("Move_Right");
	}
	else if (KnightDir == FVector2D::LEFT)
	{
		this->SpriteRenderer->ChangeAnimation("Move_Left");

	}
	else if (KnightDir == FVector2D::UP)
	{
		this->SpriteRenderer->ChangeAnimation("Move_Up");

	}
	else if (KnightDir == FVector2D::DOWN)
	{
		this->SpriteRenderer->ChangeAnimation("Move_Down");

	}
}


void AHylianKnights::Attack(float DeltaTime)
{
	UEngineDebug::CoreOutPutString("Enemy State : Attack");
}

void AHylianKnights::KnockBack(float DeltaTime)
{
	if (KnockBackCnt > 80)
	{
		SetCurEnemyState(EEnemyState::Patrol);
		return;
	}
	UEngineDebug::CoreOutPutString("Enemy State : KnockBack");
	FVector2D PlayerLocation = this->PlayerCharacter->GetActorLocation();
	FVector2D EnemeyLocation = this->GetActorLocation();

	FVector2D KnockBackDir = EnemeyLocation - PlayerLocation;
	KnockBackDir.Normalize();

	AddActorLocation(KnockBackDir * DeltaTime * 1000.0f);

	KnockBackCnt++;
}

void AHylianKnights::Trace(float DeltaTime)
{
	FVector2D PlayerLocation = this->PlayerCharacter->GetActorLocation();
	FVector2D EnemeyLocation = this->GetActorLocation();

	FVector2D TraceDir = PlayerLocation - EnemeyLocation;
	TraceDir.Normalize();

	AddActorLocation(TraceDir * DeltaTime * GetSpeed());
}

void AHylianKnights::TakeDamage(int Damage)
{
	AEnemyCharacter::TakeDamage(Damage);
}