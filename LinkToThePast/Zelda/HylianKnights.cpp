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

		SpriteRenderer->CreateAnimation("Hit_Right", "HylianKnightHit.png", 4, 7, 0.05f);
		SpriteRenderer->CreateAnimation("Hit_Left", "HylianKnightHit.png", 8, 11, 0.05f);
		SpriteRenderer->CreateAnimation("Hit_Up", "HylianKnightHit.png", 12, 15, 0.05f);
		SpriteRenderer->CreateAnimation("Hit_Down", "HylianKnightHit.png", 0, 3, 0.05f);

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

////////////////////////////////////// State Machine //////////////////////////////////////

void AHylianKnights::StartPatrol()
{
}

void AHylianKnights::StartAttack()
{
}

void AHylianKnights::StartKnockBack()
{
}

void AHylianKnights::StartTrace()
{
}

void AHylianKnights::Patrol(float DeltaTime)
{
	AEnemyCharacter::Patrol(DeltaTime);

	if (this->TurningLocations[CurTurningIndex].DistanceTo(GetActorLocation()) < 10.0f)
	{
		this->CurTurningIndex++;
		if (this->CurTurningIndex == this->TurningLocations.size())
		{
			this->CurTurningIndex = 0;
		}
		ChangeAnimation(
			GetDirectionToTargetLocation(this->TurningLocations[CurTurningIndex])
		);
	}
	else
	{
		FVector2D CurEnemyLocation = GetActorLocation();
		FVector2D TurningLocation = this->TurningLocations[CurTurningIndex];

		FVector2D MoveDir = TurningLocation - CurEnemyLocation;
		MoveDir.Normalize();

		AddActorLocation(MoveDir * DeltaTime * Speed);
		ChangeAnimation(
			GetDirectionToTargetLocation(this->TurningLocations[CurTurningIndex])
			);
	}

	UEngineDebug::CoreOutPutString("Enemy State : Idle");
	UEngineDebug::CoreOutPutString("Player to Distance : " + std::to_string(CheckDistanceToPlayer()));

	if (IsRangeToPlayer())
	{
		SetCurEnemyState(EEnemyState::Trace);
	}

}

void AHylianKnights::Trace(float DeltaTime)
{
	FVector2D PlayerLocation = this->PlayerCharacter->GetActorLocation();
	FVector2D EnemeyLocation = this->GetActorLocation();

	FVector2D TraceDir = PlayerLocation - EnemeyLocation;
	TraceDir.Normalize();

	AddActorLocation(TraceDir * DeltaTime * GetSpeed());

	CurrentDirection = GetDirectionToTargetLocation(PlayerLocation);

	ChangeAnimation(CurrentDirection);
}


void AHylianKnights::Attack(float DeltaTime)
{
	UEngineDebug::CoreOutPutString("Enemy State : Attack");
}

void AHylianKnights::KnockBack(float DeltaTime)
{
	if (KnockBackCnt > 80)
	{
		CurEnemyState = PrevEnemyState;
		KnockBackCnt = 0;
		return;
	}
	this->SpriteRenderer->ChangeAnimation("Hit_Left");
	UEngineDebug::CoreOutPutString("Enemy State : KnockBack");
	FVector2D PlayerLocation = this->PlayerCharacter->GetActorLocation();
	FVector2D EnemeyLocation = this->GetActorLocation();

	FVector2D KnockBackDir = EnemeyLocation - PlayerLocation;
	KnockBackDir.Normalize();

	AddActorLocation(KnockBackDir * DeltaTime * 1000.0f);

	KnockBackCnt++;
}

///////////////////////////////////////////////////////////////////////////////////////////


void AHylianKnights::TakeDamage(int Damage)
{
	if (CurEnemyState == EEnemyState::KnockBack) return;
	CurrentHP -= Damage;

	if (CurrentHP <= 0)
	{
		this->Destroy();
	}
	PrevEnemyState = CurEnemyState;
	CurEnemyState = EEnemyState::KnockBack;
}


void AHylianKnights::ChangeAnimation(FVector2D Direction)
{
	if (Direction == FVector2D::RIGHT)
	{
		this->SpriteRenderer->ChangeAnimation("Move_Right");
	}
	else if (Direction == FVector2D::LEFT)
	{
		this->SpriteRenderer->ChangeAnimation("Move_Left");
	}
	else if (Direction == FVector2D::UP)
	{
		this->SpriteRenderer->ChangeAnimation("Move_Up");
	}
	else if (Direction == FVector2D::DOWN)
	{
		this->SpriteRenderer->ChangeAnimation("Move_Down");
	}
}
