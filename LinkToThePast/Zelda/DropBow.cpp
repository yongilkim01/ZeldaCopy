#include "PreCompile.h"
#include "DropBow.h"
#include "ContentsEnum.h"
#include "PlayerCharacter.h"
#include "PlayerDataManager.h"

#include <EngineBase/EngineMath.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision2D.h>
#include <EngineCore/EngineCoreDebug.h>

ADropBowItem::ADropBowItem()
{
	// 스프라이트 컴포넌트 생성
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Bow.png");
		FVector2D SpriteScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(FVector2D::ZERO);
		SpriteRenderer->SetComponentScale(SpriteScale);

	}
	{
		// 충돌 컴포넌트 생성
		Collision = CreateDefaultSubObject<UCollision2D>();
		Collision->SetComponentLocation({ 0, 0 });
		Collision->SetComponentScale({ 21, 48 });
		Collision->SetCollisionGroup(ECollisionGroup::EventTarget);
		Collision->SetActive(true);

		ImmuneCollision = CreateDefaultSubObject<UCollision2D>();
		ImmuneCollision->SetComponentLocation({ 0, 0 });
		ImmuneCollision->SetComponentScale({ 21, 48 });
		ImmuneCollision->SetCollisionGroup(ECollisionGroup::NOTMOVEABLE);
		ImmuneCollision->SetActive(false);

	}
}

ADropBowItem::~ADropBowItem()
{
}

void ADropBowItem::BeginPlay()
{
	ADropItem::BeginPlay();
	ChangeState(EDropItemState::DROP);
}

void ADropBowItem::Tick(float DeltaTime)
{
	ADropItem::Tick(DeltaTime);
}

void ADropBowItem::StartDrop()
{
	//CurDropPower = FVector2D::UP * 300.0f;
}

void ADropBowItem::StartPickup()
{

}

void ADropBowItem::Drop(float DeltaTime)
{
	
	//CurDropPower += FVector2D::UP * 1.0f * DeltaTime;
	SpriteRenderer->AddComponentLocation(FVector2D::UP * 150.0f * DeltaTime);
	UEngineDebug::CoreOutPutString("location Y : " + std::to_string(SpriteRenderer->GetComponentLocation().Y));

	if (-30.0f > SpriteRenderer->GetComponentLocation().Y)
	{
		ChangeState(EDropItemState::PICKUP);
	}
}

void ADropBowItem::Pickup(float DeltaTime)
{
	CurrentTime += DeltaTime;
	if (CheckTime <= CurrentTime)
	{
		PlayerDataManager::GetInstance().SetWeaponActiveToIndex(1, true);
		Destroy();
	}
}