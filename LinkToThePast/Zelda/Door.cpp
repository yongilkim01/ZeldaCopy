#include "PreCompile.h"
#include "Door.h"

#include "ContentsEnum.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.h"

#include <EngineBase/EngineDebug.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision2D.h>
#include <EngineCore/EngineCoreDebug.h>

ADoor::ADoor()
{
	// 스프라이트 컴포넌트 생성
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("DoorDown.png", 0);

		SpriteRenderer->CreateAnimation("DoorDownClose", "DoorDown.png", 0, 0, 0.05f);
		SpriteRenderer->CreateAnimation("DownDoorOpening", "DoorDown.png", 0, 2, 0.01f, false);
		SpriteRenderer->CreateAnimation("DownDoorOpen", "DoorDown.png", 2, 2, 0.05f);

		SpriteRenderer->SetAnimationEvent("DownDoorOpening", 2, [this]()
			{
				SpriteRenderer->ChangeAnimation("DownDoorOpen");
				ImmuneCollision->SetActive(false);
			});

		SpriteRenderer->ChangeAnimation("DoorDownClose");

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
		ImmuneCollision->SetComponentScale({ 96, 48 });
		ImmuneCollision->SetCollisionGroup(ECollisionGroup::NOTMOVEABLE);
		ImmuneCollision->SetActive(true);

	}

	//DebugOn();
}

ADoor::~ADoor()
{
}

void ADoor::BeginPlay()
{
	AEventActor::BeginPlay();

	ChangeState(EDoorState::CLOSE);
}

void ADoor::Tick(float DeltaTime)
{
	AEventActor::Tick(DeltaTime);

	switch (CurDoorState)
	{
	case EDoorState::NONE:
		break;
	case EDoorState::CLOSE:
		Close(DeltaTime);
		break;
	case EDoorState::OPEN:
		Open(DeltaTime);
		break;
	default:
		break;
	}
}

int ADoor::Interact(ABaseCharacter* Character)
{
	SpriteRenderer->SetOrder(Character->GetSpriteOrder() + 1);
	Owner = dynamic_cast<APlayerCharacter*>(Character);

	if (nullptr == Owner)
	{
		MSGASSERT("문의 캐릭터가 nullptr입니다.");
		return 0;
	}

	ChangeState(EDoorState::OPEN);

	return 0;
}

void ADoor::ChangeState(EDoorState DoorState)
{
	switch (DoorState)
	{
	case EDoorState::NONE:
		break;
	case EDoorState::CLOSE:
		StartClose();
		break;
	case EDoorState::OPEN:
		StartOpen();
		break;
	default:
		break;
	}

	CurDoorState = DoorState;
}

void ADoor::StartClose()
{
	SpriteRenderer->ChangeAnimation("DoorDownClose");
}

void ADoor::StartOpen()
{
	SpriteRenderer->ChangeAnimation("DownDoorOpening");
}

void ADoor::Close(float DeltaTime)
{

}

void ADoor::Open(float DeltaTime)
{

}

void ADoor::SetDoorRenderOrder(int Order)
{
	this->SpriteRenderer->SetOrder(Order);

}
