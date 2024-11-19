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

AHylianKnight::AHylianKnight()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("HylianKnightMoveDown.png");
		SpriteRenderer->SetComponentScale(FVector2D(1.0f, 1.0f));
		SpriteRenderer->SetOrder(ERenderOrder::FIRST_FLOOR_OBJ);
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

		SpriteRenderer->CreateAnimation("Fall", "HylianKnightFall.png", 0, 3, 0.3f);

		SpriteRenderer->SetAnimationEvent("Fall", 3, std::bind(&AHylianKnight::EndFallAnimation, this));

		SpriteRenderer->ChangeAnimation("Move_Down");

	}
	{
		CollisionComponent = CreateDefaultSubObject<UCollision2D>();
		CollisionComponent->SetComponentLocation({ 0, 0 });
		CollisionComponent->SetComponentScale({ 80, 80 });
		CollisionComponent->SetCollisionGroup(ECollisionGroup::EnemyBody);
		CollisionComponent->SetCollisionType(ECollisionType::Rect);
	}
	{
		// 공격 충돌 컴포넌트 생성
		AttackCollisions.reserve(4);

		UCollision2D* RightAttackCollision = CreateDefaultSubObject<UCollision2D>();
		RightAttackCollision->SetComponentLocation({ 50, 0 });
		RightAttackCollision->SetComponentScale({ 50, 80 });
		RightAttackCollision->SetCollisionGroup(ECollisionGroup::EnemyAttack);
		AttackCollisions.push_back(RightAttackCollision);

		UCollision2D* LeftAttackCollision = CreateDefaultSubObject<UCollision2D>();
		LeftAttackCollision->SetComponentLocation({ -50, 0 });
		LeftAttackCollision->SetComponentScale({ 50, 80 });
		LeftAttackCollision->SetCollisionGroup(ECollisionGroup::EnemyAttack);
		AttackCollisions.push_back(LeftAttackCollision);

		UCollision2D* DownAttackCollision = CreateDefaultSubObject<UCollision2D>();
		DownAttackCollision->SetComponentLocation({ 0, 50 });
		DownAttackCollision->SetComponentScale({ 80, 50 });
		DownAttackCollision->SetCollisionGroup(ECollisionGroup::EnemyAttack);
		AttackCollisions.push_back(DownAttackCollision);

		UCollision2D* UpAttackCollision = CreateDefaultSubObject<UCollision2D>();
		UpAttackCollision->SetComponentLocation({ 0, -50 });
		UpAttackCollision->SetComponentScale({ 80, 50 });
		UpAttackCollision->SetCollisionGroup(ECollisionGroup::EnemyAttack);
		AttackCollisions.push_back(UpAttackCollision);

	}

	CollisionSize = { 10.0f, 30.0f };


	//DebugOn();
}

AHylianKnight::~AHylianKnight()
{
}

void AHylianKnight::BeginPlay()
{
	AEnemyKnight::BeginPlay();

}

void AHylianKnight::Tick(float DeltaTime)
{
	AEnemyKnight::Tick(DeltaTime);

}