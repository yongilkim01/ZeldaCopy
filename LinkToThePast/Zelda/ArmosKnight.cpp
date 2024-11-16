#include "PreCompile.h"
#include "ArmosKnight.h"
#include "ContentsEnum.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision2D.h>
#include <EngineCore/EngineCoreDebug.h>

AArmosKnight::AArmosKnight()
{
	{
		SpriteComponent = CreateDefaultSubObject<USpriteRenderer>();
		SpriteComponent->SetSprite("HylianKnightMoveDown.png");
		SpriteComponent->SetComponentScale(FVector2D(1.0f, 1.0f));
		SpriteComponent->SetOrder(ERenderOrder::FIRST_FLOOR_OBJ);
		SpriteComponent->SetSpriteScale(3.0f);
		SpriteComponent->CreateAnimation("Move", "ArmosKnightIdle.png", 0, 0, 0.1f);
		SpriteComponent->CreateAnimation("Hit", "ArmosKnightHit.png", 0, 7, 0.0011f);
		SpriteComponent->CreateAnimation("Death", "ArmosKnightDeath.png", 0, 7, 0.0011f);

		SpriteComponent->ChangeAnimation("Move");

	}
	{
		CollisionComponent = CreateDefaultSubObject<UCollision2D>();
		CollisionComponent->SetComponentLocation({ 0, 0 });
		CollisionComponent->SetComponentScale({ 80, 80 });
		CollisionComponent->SetCollisionGroup(ECollisionGroup::EnemyBody);
		CollisionComponent->SetCollisionType(ECollisionType::Rect);
	}
	DebugOn();
}

AArmosKnight::~AArmosKnight()
{
}


void AArmosKnight::TakeDamage(int Damage, ABaseCharacter* Character)
{
	if (CurBossState == EBossState::KNOCKBACK) return;

	CurrentHP -= Damage;
	TargetCharacter = Character;

	if (CurrentHP <= 0)
	{
		CurBossState = EBossState::KNOCKBACK;
	}

	CurBossState = EBossState::KNOCKBACK;
	SpriteComponent->ChangeAnimation("Hit");
}

void AArmosKnight::BeginPlay()
{
	ABossCharacter::BeginPlay();

	CurJumpPower = FVector2D::UP * 100.0f;
	ChangeState(EBossState::MOVE);
	

}

void AArmosKnight::Tick(float DeltaTime)
{
	ABossCharacter::Tick(DeltaTime);

	PrintDebugInfo();

	switch (CurBossState)
	{
	case EBossState::MOVE:
		Move(DeltaTime);
		break;
	case EBossState::KNOCKBACK:
		Knockback(DeltaTime);
		break;
	default:
		break;
	}
}


void AArmosKnight::Move(float DeltaTime)
{
	// 관리자가 지정해준 위치로 이동
	{
		FVector2D MoveDir = TargetLoc - GetActorLocation();
		MoveDir.Normalize();
		AddActorLocation(MoveDir * 300.0f * DeltaTime);
	}
	// 자체 점프
	{
		// 중력
		CurJumpPower += FVector2D::DOWN * 2000.0f * DeltaTime;
		SpriteComponent->AddComponentLocation(CurJumpPower * DeltaTime);

		if (0.0f <= SpriteComponent->GetComponentLocation().Y)
		{
			CurJumpPower = FVector2D::UP * 500.0f;
		}
	}
}

void AArmosKnight::Knockback(float DeltaTime)
{
	if (KnockBackCount > 50 || TargetCharacter == nullptr)
	{
		//CurBossState = PrevEnemyState;
		KnockBackCount = 0;
		ChangeState(EBossState::MOVE);
		SpriteComponent->ChangeAnimation("Move");

		//if (CurrentHP <= 0)
		//{
		//	DeathEffect = GetWorld()->SpawnActor<AEffectEnemyDeath>();
		//	DeathEffect->SetActorLocation(GetActorLocation());
		//	DeathEffect->SetOwnerActor(this);
		//}

		return;
	}

	FVector2D PlayerLocation = this->TargetCharacter->GetActorLocation();

	AddActorLocation(TargetCharacter->GetCurDirection() * DeltaTime * 1000.0f);

	KnockBackCount++;

	// 자체 점프
	{
		// 중력
		CurJumpPower += FVector2D::DOWN * 2000.0f * DeltaTime;
		SpriteComponent->AddComponentLocation(CurJumpPower * DeltaTime);

		if (0.0f <= SpriteComponent->GetComponentLocation().Y)
		{
			CurJumpPower = FVector2D::UP * 500.0f;
		}
	}
}

void AArmosKnight::PrintDebugInfo()
{
	UEngineDebug::CoreOutPutString("///////////////////////// Armos knight Debug /////////////////////////");
	UEngineDebug::CoreOutPutString("Kncok back count : " + std::to_string(KnockBackCount));

	if (TargetCharacter != nullptr)
	{
		UEngineDebug::CoreOutPutString("Target location : " + TargetCharacter->GetActorLocation().ToString());
	}
	switch (CurBossState)
	{
	case EBossState::NONE:
		UEngineDebug::CoreOutPutString("Armos knight state : NONE");
		break;
	case EBossState::MOVE:
		UEngineDebug::CoreOutPutString("Armos knight state : MOVE");
		break;
	case EBossState::KNOCKBACK:
		UEngineDebug::CoreOutPutString("Armos knight state : KNOCKBACK");
		break;
	default:
		break;
	}
}
