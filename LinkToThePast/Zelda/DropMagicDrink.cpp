#include "PreCompile.h"
#include "DropMagicDrink.h"
#include "ContentsEnum.h"
#include "PlayerCharacter.h"
#include "PlayerDataManager.h"

#include <EngineBase/EngineMath.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision2D.h>
#include <EngineCore/EngineCoreDebug.h>

ADropMagicDrinkItem::ADropMagicDrinkItem()
{
	// 스프라이트 컴포넌트 생성
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("DropMagicDrink.png");
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

ADropMagicDrinkItem::~ADropMagicDrinkItem()
{
}

void ADropMagicDrinkItem::BeginPlay()
{
	ADropItem::BeginPlay();
	ChangeState(EDropItemState::DROP);
}

void ADropMagicDrinkItem::Tick(float DeltaTime)
{
	ADropItem::Tick(DeltaTime);
}

void ADropMagicDrinkItem::StartDrop()
{
	CurDropPower = FVector2D::UP * 300.0f;
}

void ADropMagicDrinkItem::StartPickup()
{
	//SpriteRenderer->ChangeAnimation("Drop");
}

void ADropMagicDrinkItem::Drop(float DeltaTime)
{
	CurDropPower += FVector2D::DOWN * 2000.0f * DeltaTime;
	SpriteRenderer->AddComponentLocation(CurDropPower * DeltaTime);

	if (10.0f <= SpriteRenderer->GetComponentLocation().Y)
	{
		ChangeState(EDropItemState::PICKUP);
	}
}

void ADropMagicDrinkItem::Pickup(float DeltaTime)
{
	if (DropSpeed > 0.0f)
	{
		CurrentDeltaTime += DeltaTime;
		AddActorLocation(FVector2D(DropSpeed * UEngineMath::Sin(CurrentDeltaTime * DropFrequency), 0.0f));
		DropSpeed -= 0.0005f;
	}
	else
	{
		AActor* Result = Collision->CollisionOnce(ECollisionGroup::PlayerBody);
		if (nullptr != Result)
		{
			SoundPlayer = UEngineSound::Play("throw.wav");
			PlayerDataManager::GetInstance().AddMagicGaguge(10);
			Destroy();
		}
	}
}