#include "PreCompile.h"
#include "DropKey.h"
#include "ContentsEnum.h"
#include "PlayerCharacter.h"
#include "PlayerDataManager.h"

#include <EngineBase/EngineMath.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision2D.h>
#include <EngineCore/EngineCoreDebug.h>

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
	//UEngineDebug::CoreOutPutString("location Y : " + std::to_string(SpriteRenderer->GetComponentLocation().Y));
}

void ADropKeyItem::StartDrop()
{
	CurDropPower = FVector2D::UP * 100.0f;
}

void ADropKeyItem::StartPickup()
{
}

void ADropKeyItem::Drop(float DeltaTime)
{
	CurDropPower += FVector2D::DOWN * 2000.0f * DeltaTime;
	SpriteRenderer->AddComponentLocation(CurDropPower * DeltaTime);

	if (0.0f <= SpriteRenderer->GetComponentLocation().Y)
	{
		ChangeState(EDropItemState::PICKUP);
	}
}

void ADropKeyItem::Pickup(float DeltaTime)
{
	if (DropSpeed > 0.0f)
	{
		CurrentDeltaTime += DeltaTime;
		SpriteRenderer->AddComponentLocation(FVector2D(0.0f, DropSpeed * UEngineMath::Sin(CurrentDeltaTime * DropFrequency)));
		if (UEngineMath::Sin(CurrentDeltaTime * DropFrequency) < -0.99f && false == IsSoundCheck)
		{
			SoundPlayer = UEngineSound::Play("tink.wav");
			IsSoundCheck = true;
		}

		if (UEngineMath::Sin(CurrentDeltaTime * DropFrequency) > 0.98f)
		{
			IsSoundCheck = false;
		}
		DropSpeed -= 0.0006;

	}

	AActor* Result = Collision->CollisionOnce(ECollisionGroup::PlayerBody);
	if (nullptr != Result)
	{
		PlayerDataManager::GetInstance().AddKey(1);
		SoundPlayer = UEngineSound::Play("key 1.wav");
		Destroy();
	}
}
