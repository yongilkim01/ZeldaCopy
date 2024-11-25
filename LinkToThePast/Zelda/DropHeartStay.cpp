#include "PreCompile.h"
#include "DropHeartStay.h"
#include "ContentsEnum.h"
#include "PlayerCharacter.h"
#include "PlayerDataManager.h"

#include <EngineBase/EngineMath.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision2D.h>
#include <EngineCore/EngineCoreDebug.h>

ADropHeartStayItem::ADropHeartStayItem()
{
	// 스프라이트 컴포넌트 생성
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("DropFullHeart.png");
		FVector2D SpriteScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(FVector2D::ZERO);
		SpriteRenderer->SetComponentScale(SpriteScale);
	}
	{
		// 충돌 컴포넌트 생성
		Collision = CreateDefaultSubObject<UCollision2D>();
		Collision->SetComponentLocation({ 0, 0 });
		Collision->SetComponentScale({ 24, 21 });
		Collision->SetCollisionGroup(ECollisionGroup::EventTarget);
		Collision->SetActive(true);

	}
}

ADropHeartStayItem::~ADropHeartStayItem()
{
}

void ADropHeartStayItem::BeginPlay()
{
	ADropItem::BeginPlay();
	ChangeState(EDropItemState::PICKUP);
}

void ADropHeartStayItem::Tick(float DeltaTime)
{
	ADropItem::Tick(DeltaTime);
}

void ADropHeartStayItem::StartDrop()
{
	CurDropPower = FVector2D::UP * 300.0f;
}

void ADropHeartStayItem::StartPickup()
{
	SpriteRenderer->SetSprite("DropFullHeart.png");
}

void ADropHeartStayItem::Drop(float DeltaTime)
{
	CurDropPower += FVector2D::DOWN * 2000.0f * DeltaTime;
	SpriteRenderer->AddComponentLocation(CurDropPower * DeltaTime);

	if (10.0f <= SpriteRenderer->GetComponentLocation().Y)
	{
		ChangeState(EDropItemState::PICKUP);
	}
}

void ADropHeartStayItem::Pickup(float DeltaTime)
{
	AActor* Result = Collision->CollisionOnce(ECollisionGroup::PlayerBody);
	if (nullptr != Result)
	{
		PlayerDataManager::GetInstance().AddHP(2);
		Destroy();
	}
}