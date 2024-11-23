#include "PreCompile.h"
#include "ArmosKnight.h"
#include "ArmosKngiht_Control.h"
#include "ContentsEnum.h"
#include "PlayerCharacter.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision2D.h>
#include <EngineCore/EngineCoreDebug.h>

AArmosKnight::AArmosKnight()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("HylianKnightMoveDown.png");
		SpriteRenderer->SetComponentScale(FVector2D(1.0f, 1.0f));
		SpriteRenderer->SetOrder(ERenderOrder::FIRST_FLOOR_OBJ);
		SpriteRenderer->SetSpriteScale(3.0f);
		SpriteRenderer->CreateAnimation("Move", "ArmosKnightIdle.png", 0, 0, 0.1f);
		SpriteRenderer->CreateAnimation("Hit", "ArmosKnightHit.png", 0, 7, 0.0011f);
		SpriteRenderer->CreateAnimation("Death", "ArmosKnightDeath.png", 0, 4, 0.1f);
		SpriteRenderer->CreateAnimation("Berserk", "ArmosKnightBerserk.png", 0, 0, 0.1f);

		SpriteRenderer->SetAnimationEvent("Death", 4, std::bind(&AArmosKnight::Death, this));

		SpriteRenderer->ChangeAnimation("Move");

	}
	{
		HitCollision = CreateDefaultSubObject<UCollision2D>();
		HitCollision->SetComponentLocation({ 0, 0 });
		HitCollision->SetComponentScale({ 80, 80 });
		HitCollision->SetCollisionGroup(ECollisionGroup::EnemyBody);
		HitCollision->SetCollisionType(ECollisionType::Rect);
	}

	{
		AttackCollision = CreateDefaultSubObject<UCollision2D>();
		AttackCollision->SetComponentScale({ 80, 50 });
		AttackCollision->SetCollisionGroup(ECollisionGroup::EnemyAttack);
		AttackCollision->SetCollisionType(ECollisionType::Rect);

		BodyCollision = CreateDefaultSubObject<UCollision2D>();
		BodyCollision->SetComponentLocation({ 0, 10 });
		BodyCollision->SetComponentScale({ 50,55 });
		BodyCollision->SetCollisionGroup(ECollisionGroup::MOVEABLE);
		BodyCollision->SetActive(true);
	}

	DebugOn();
	
	CurrentHP = 10;
}

AArmosKnight::~AArmosKnight()
{
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

	//PrintDebugInfo();

	switch (CurBossState)
	{
	case EBossState::MOVE:
		Move(DeltaTime);
		break;
	case EBossState::KNOCKBACK:
		Knockback(DeltaTime);
		break;
	case EBossState::BERSERK_WAIT:
		BerserkWait(DeltaTime);
		break;
	case EBossState::BERSERK_MOVE:
		BerserkMove(DeltaTime);
		break;
	case EBossState::BERSERK_ATTACK:
		BerserkAttack(DeltaTime);
		break;
	default:
		break;
	}
}