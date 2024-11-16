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
		SpriteComponent->CreateAnimation("Idle", "ArmosKnightIdle.png", 0, 0, 0.1f);

		SpriteComponent->ChangeAnimation("Idle");

	}
	{
		CollisionComponent = CreateDefaultSubObject<UCollision2D>();
		CollisionComponent->SetComponentLocation({ 0, 0 });
		CollisionComponent->SetComponentScale({ 80, 80 });
		CollisionComponent->SetCollisionGroup(ECollisionGroup::EnemyBody);
		CollisionComponent->SetCollisionType(ECollisionType::Rect);
	}
}

AArmosKnight::~AArmosKnight()
{
}


void AArmosKnight::TakeDamage(int Damage, ABaseCharacter* Character)
{
	ChangeState(EBossState::KNOCKBACK);
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

void AArmosKnight::Knockback(float DetlaTime)
{
}

void AArmosKnight::PrintDebugInfo()
{
	UEngineDebug::CoreOutPutString("///////////////////////// Armos knight Debug /////////////////////////");

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
