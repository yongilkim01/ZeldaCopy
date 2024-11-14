#include "PreCompile.h"
#include "ArmosKnight.h"
#include "ContentsEnum.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision2D.h>

AArmosKnight::AArmosKnight()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("HylianKnightMoveDown.png");
		SpriteRenderer->SetComponentScale(FVector2D(1.0f, 1.0f));
		SpriteRenderer->SetOrder(ERenderOrder::FIRST_FLOOR_OBJ);
		SpriteRenderer->SetSpriteScale(1.5f);
		SpriteRenderer->CreateAnimation("Idle", "ArmosKnightIdle.png", 0, 0, 0.1f);

		SpriteRenderer->ChangeAnimation("Idle");

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

void AArmosKnight::BeginPlay()
{
	ABossCharacter::BeginPlay();

}

void AArmosKnight::Tick(float DeltaTime)
{
	ABossCharacter::Tick(DeltaTime);
}

