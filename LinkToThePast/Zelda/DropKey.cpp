#include "PreCompile.h"
#include "DropKey.h"
#include "ContentsEnum.h"

#include <EngineBase/EngineMath.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision2D.h>

ADropKeyItem::ADropKeyItem()
{
	// 스프라이트 컴포넌트 생성
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("NormalKey.png");
		FVector2D SpriteScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(FVector2D::ZERO);
		SpriteRenderer->SetComponentScale(SpriteScale);

	}
	{
		// 충돌 컴포넌트 생성
		Collision = CreateDefaultSubObject<UCollision2D>();
		Collision->SetComponentLocation({ 0, 0 });
		Collision->SetComponentScale({ 24, 45 });
		Collision->SetCollisionGroup(ECollisionGroup::EventTarget);
		Collision->SetActive(true);

		ImmuneCollision = CreateDefaultSubObject<UCollision2D>();
		ImmuneCollision->SetComponentLocation({ 0, 0 });
		ImmuneCollision->SetComponentScale({ 24, 45 });
		ImmuneCollision->SetCollisionGroup(ECollisionGroup::NOTMOVEABLE);
		ImmuneCollision->SetActive(false);

	}
}

ADropKeyItem::~ADropKeyItem()
{
}

void ADropKeyItem::BeginPlay()
{
	ADropItem::BeginPlay();
	ChangeState(EDropItemState::DROP);
}

void ADropKeyItem::Tick(float DeltaTime)
{
	ADropItem::Tick(DeltaTime);
}

void ADropKeyItem::StartDrop()
{
}

void ADropKeyItem::StartPickup()
{
}

void ADropKeyItem::Drop(float DeltaTime)
{
	FVector2D CurLocation = GetActorLocation();
	CurLocation.Y = DropSpeed + DropLength * UEngineMath::Sin(2 * PI * DropFrequency * DeltaTime);
	//SetActorLocation(CurLocation);
}

void ADropKeyItem::Pickup(float DeltaTime)
{
}
