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
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("KnightMoveDown.png");
		SpriteRenderer->SetComponentScale(FVector2D(1.0f, 1.0f));
		SpriteRenderer->SetSpriteScale(3.0f);
		SpriteRenderer->CreateAnimation("Idle_Down", "KnightMoveDown.png", 0, 0, 0.1f);
		SpriteRenderer->CreateAnimation("Run_Down", "KnightMoveDown.png", 0, 3, 0.3f);

		SpriteRenderer->ChangeAnimation("Run_Down");

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

void AHylianKnights::Idle(float DeltaTime)
{
	AEnemyCharacter::Idle(DeltaTime);

	UEngineDebug::CoreOutPutString("Enemy State : Idle");
	UEngineDebug::CoreOutPutString("Player to Distance : " + std::to_string(CheckDistanceToPlayer()));
	if (IsRangeToPlayer())
	{
		SetCurEnemyState(EEnemyState::Trace);
	}
	
}

void AHylianKnights::Move(float DeltaTime)
{
	UEngineDebug::CoreOutPutString("Enemy State : Move");
}

void AHylianKnights::Attack(float DeltaTime)
{
	UEngineDebug::CoreOutPutString("Enemy State : Attack");
}

void AHylianKnights::KnockBack(float DeltaTime)
{
	if (KnockBackCnt > 80)
	{
		SetCurEnemyState(EEnemyState::Idle);
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