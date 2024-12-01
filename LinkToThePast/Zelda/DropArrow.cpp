#include "PreCompile.h"
#include "DropArrow.h"
#include "ContentsEnum.h"
#include "PlayerCharacter.h"
#include "PlayerDataManager.h"

#include <EngineBase/EngineMath.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision2D.h>
#include <EngineCore/EngineCoreDebug.h>

ADropArrowItem::ADropArrowItem()
{
	// 스프라이트 컴포넌트 생성
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("DropArrow.png");
		FVector2D SpriteScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(FVector2D::ZERO);
		SpriteRenderer->SetComponentScale(SpriteScale);

		SpriteRenderer->CreateAnimation("Drop", "DropArrow.png", 0, 0, 0.3f);
		SpriteRenderer->ChangeAnimation("Drop");

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

ADropArrowItem::~ADropArrowItem()
{
}

void ADropArrowItem::BeginPlay()
{
	ADropItem::BeginPlay();
	ChangeState(EDropItemState::DROP);
}

void ADropArrowItem::Tick(float DeltaTime)
{
	ADropItem::Tick(DeltaTime);
}

void ADropArrowItem::StartDrop()
{
	CurDropPower = FVector2D::UP * 300.0f;
}

void ADropArrowItem::StartPickup()
{
	//SpriteRenderer->ChangeAnimation("Drop");
}

void ADropArrowItem::Drop(float DeltaTime)
{
	CurDropPower += FVector2D::DOWN * 2000.0f * DeltaTime;
	SpriteRenderer->AddComponentLocation(CurDropPower * DeltaTime);

	if (10.0f <= SpriteRenderer->GetComponentLocation().Y)
	{
		ChangeState(EDropItemState::PICKUP);
	}
}

void ADropArrowItem::Pickup(float DeltaTime)
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
			PlayerDataManager::GetInstance().AddArrow(10);
			Destroy();
		}
	}
}