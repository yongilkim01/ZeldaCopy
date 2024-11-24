#include "PreCompile.h"
#include "DropHeart.h"
#include "ContentsEnum.h"
#include "PlayerCharacter.h"
#include "PlayerDataManager.h"

#include <EngineBase/EngineMath.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision2D.h>
#include <EngineCore/EngineCoreDebug.h>

ADropHeartItem::ADropHeartItem()
{
	// 스프라이트 컴포넌트 생성
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("DropFullHeart.png");
		FVector2D SpriteScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(FVector2D::ZERO);
		SpriteRenderer->SetComponentScale(SpriteScale);

		SpriteRenderer->CreateAnimation("Drop", "DropHeart.png", 0, 4, 0.3f, false);

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

ADropHeartItem::~ADropHeartItem()
{
}

void ADropHeartItem::BeginPlay()
{
	ADropItem::BeginPlay();
	ChangeState(EDropItemState::DROP);
}

void ADropHeartItem::Tick(float DeltaTime)
{
	ADropItem::Tick(DeltaTime);
}

void ADropHeartItem::StartDrop()
{
	CurDropPower = FVector2D::UP * 300.0f;
}

void ADropHeartItem::StartPickup()
{
	SpriteRenderer->SetSprite("DropHeart.png", 0);
	FVector2D SpriteScale = SpriteRenderer->SetSpriteScale(0.8f);
	//SpriteRenderer->SetComponentLocation(FVector2D::ZERO);
	SpriteRenderer->SetComponentScale(SpriteScale);
	SpriteRenderer->ChangeAnimation("Drop");
}

void ADropHeartItem::Drop(float DeltaTime)
{
	CurDropPower += FVector2D::DOWN * 2000.0f * DeltaTime;
	SpriteRenderer->AddComponentLocation(CurDropPower * DeltaTime);

	if (10.0f <= SpriteRenderer->GetComponentLocation().Y)
	{
		ChangeState(EDropItemState::PICKUP);
	}
}

void ADropHeartItem::Pickup(float DeltaTime)
{
	if (DropSpeed > 0.0f)
	{
		CurrentDeltaTime += DeltaTime;
		AddActorLocation(FVector2D(DropSpeed * UEngineMath::Sin(CurrentDeltaTime * DropFrequency), 0.0f));
		DropSpeed -= 0.0005;
	}
	else
	{
		AActor* Result = Collision->CollisionOnce(ECollisionGroup::PlayerBody);
		if (nullptr != Result)
		{
			PlayerDataManager::GetInstance().AddHP(2);
			Destroy();
		}
	}
}