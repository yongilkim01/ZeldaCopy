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
		DebugOn();
	}
}

AHylianKnights::~AHylianKnights()
{
}

void AHylianKnights::BeginPlay()
{
	AEnemyCharacter::BeginPlay();
}

void AHylianKnights::Tick(float DeltaTime)
{
	AEnemyCharacter::Tick(DeltaTime);
}

void AHylianKnights::Idle(float DeltaTime)
{
	UEngineDebug::CoreOutPutString("Enemy State : Idle");
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
	UEngineDebug::CoreOutPutString("Enemy State : KnockBack");
}

