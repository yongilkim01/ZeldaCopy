#include "PreCompile.h"
#include "Chest.h"

#include "ContentsEnum.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.h"

#include <EngineBase/EngineDebug.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision2D.h>
#include <EngineCore/EngineCoreDebug.h>

AChest::AChest()
{
	// 스프라이트 컴포넌트 생성
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Chest.png", 0);

		SpriteRenderer->CreateAnimation("ChestClose", "Chest.png", 1, 1, 0.05f);
		SpriteRenderer->CreateAnimation("ChestOepn", "Chest.png", 0, 0, 0.05f);

		SpriteRenderer->ChangeAnimation("ChestClose");

		SpriteRenderer->SetSpriteScale(1.0f);

	}
	{
		// 충돌 컴포넌트 생성
		Collision = CreateDefaultSubObject<UCollision2D>();
		Collision->SetComponentLocation({ 0, 0 });
		Collision->SetComponentScale({ 30, 30 });
		Collision->SetCollisionGroup(ECollisionGroup::EventTarget);
		Collision->SetActive(true);

		ImmuneCollision = CreateDefaultSubObject<UCollision2D>();
		ImmuneCollision->SetComponentLocation({ 0, 0 });
		ImmuneCollision->SetComponentScale({ 48, 48 });
		ImmuneCollision->SetCollisionGroup(ECollisionGroup::NOTMOVEABLE);
		ImmuneCollision->SetActive(true);

	}

	//DebugOn();
}

AChest::~AChest()
{
}

void AChest::BeginPlay()
{
	AEventActor::BeginPlay();

	ChangeState(EChestState::CLOSE);
}

void AChest::Tick(float DeltaTime)
{
	AEventActor::Tick(DeltaTime);

	switch (CurChestState)
	{
	case EChestState::NONE:
		break;
	case EChestState::CLOSE:
		Close(DeltaTime);
		break;
	case EChestState::OPEN:
		Open(DeltaTime);
		break;
	default:
		break;
	}
}

int AChest::Interact(ABaseCharacter* Character)
{
	if (FVector2D::DOWN == GetDirectionToTargetLocation(Character->GetActorLocation()))
	{
		SpriteRenderer->SetOrder(Character->GetSpriteOrder() + 1);
		Owner = dynamic_cast<APlayerCharacter*>(Character);

		if (nullptr == Owner)
		{
			MSGASSERT("보물상자의 소유주 플레이어가 nullptr입니다.");
			return 0;
		}

		ChangeState(EChestState::OPEN);
	}
	return 0;
}

void AChest::ChangeState(EChestState ChestState)
{
	switch (ChestState)
	{
	case EChestState::NONE:
		break;
	case EChestState::CLOSE:
		StartClose();
		break;
	case EChestState::OPEN:
		StartOpen();
		break;
	default:
		break;
	}

	CurChestState = ChestState;
}

void AChest::StartClose()
{
	SpriteRenderer->ChangeAnimation("ChestClose");
}

void AChest::StartOpen()
{
	SpriteRenderer->ChangeAnimation("ChestOepn");
}

void AChest::Close(float DeltaTime)
{
	
}

void AChest::Open(float DeltaTime)
{
	
}