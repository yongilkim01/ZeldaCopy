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
		SpriteRenderer->SetSpriteScale(3.0f);
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

	CurJumpPower = FVector2D::UP * 100.0f;

}

void AArmosKnight::Tick(float _DeltaTime)
{
	ABossCharacter::Tick(_DeltaTime);

	// 지정해준 위치로 가고
	{
		FVector2D MoveDir = TargetLoc - GetActorLocation();
		MoveDir.Normalize();
		AddActorLocation(MoveDir * 300.0f * _DeltaTime);
	}

	{
		// 중력
		CurJumpPower += FVector2D::DOWN * 2000.0f * _DeltaTime;
		SpriteRenderer->AddComponentLocation(CurJumpPower * _DeltaTime);

		if (0.0f <= SpriteRenderer->GetComponentLocation().Y)
		{
			CurJumpPower = FVector2D::UP * 500.0f;
		}

	}
}








