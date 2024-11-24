#include "PreCompile.h"
#include "Door.h"

#include "ContentsEnum.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.h"
#include "PlayerDataManager.h"

#include <EngineBase/EngineDebug.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision2D.h>
#include <EngineCore/EngineCoreDebug.h>

ADoor::ADoor()
{
	// 스프라이트 컴포넌트 생성
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("DoorRightLeft2.png", 0);

		SpriteRenderer->CreateAnimation("KeyDownDoorOpening", "DoorDownUp.png", 0, 2, 0.1f, false);
		SpriteRenderer->CreateAnimation("KeyDownDoorOpen", "DoorDownUp.png", 2, 2, 0.05f);
		SpriteRenderer->CreateAnimation("KeyDownDoorClosing", "DoorDownUp.png", 3, 5, 0.1f, false);
		SpriteRenderer->CreateAnimation("KeyDownDoorClose", "DoorDownUp.png", 5, 5, 0.05f);

		SpriteRenderer->CreateAnimation("KeyUPDoorOpening", "DoorDownUp.png", 6, 8, 0.1f, false);
		SpriteRenderer->CreateAnimation("KeyUpDoorOpen", "DoorDownUp.png", 8, 8, 0.05f);
		SpriteRenderer->CreateAnimation("KeyUPDoorClosing", "DoorDownUp.png", 9, 11, 0.1f, false);
		SpriteRenderer->CreateAnimation("KeyUpDoorClose", "DoorDownUp.png", 11, 11, 0.05f);

		SpriteRenderer->SetAnimationEvent("KeyDownDoorOpening", 2, [this]()
			{
				SpriteRenderer->ChangeAnimation("KeyDownDoorOpen");
				ImmuneCollision->SetActive(false);
			});

		SpriteRenderer->SetAnimationEvent("KeyDownDoorClosing", 5, [this]()
			{
				SpriteRenderer->ChangeAnimation("KeyDownDoorClose");
				ImmuneCollision->SetActive(false);
			});

		SpriteRenderer->SetAnimationEvent("KeyUPDoorOpening", 8, [this]()
			{
				SpriteRenderer->ChangeAnimation("KeyUpDoorOpen");
				ImmuneCollision->SetActive(false);
			});

		SpriteRenderer->SetAnimationEvent("KeyUPDoorClosing", 11, [this]()
			{
				SpriteRenderer->ChangeAnimation("KeyUpDoorClose");
				ImmuneCollision->SetActive(false);
			});

		SpriteRenderer->CreateAnimation("GimmickRightDoorOpening", "DoorRightLeft2.png", 3, 5, 0.1f, false);
		SpriteRenderer->CreateAnimation("GimmickRightDoorOpen", "DoorRightLeft2.png", 5, 5, 0.05f);
		SpriteRenderer->CreateAnimation("GimmickRightDoorClosing", "DoorRightLeft2.png", 6, 8, 0.1f, false);
		SpriteRenderer->CreateAnimation("GimmickRightDoorClose", "DoorRightLeft2.png", 8, 8, 0.05f);

		SpriteRenderer->CreateAnimation("GimmickLeftDoorClosing", "DoorRightLeft2.png", 9, 11, 0.1f, false);
		SpriteRenderer->CreateAnimation("GimmickLeftDoorClose", "DoorRightLeft2.png", 0, 0, 0.05f);
		SpriteRenderer->CreateAnimation("GimmickLeftDoorOpening", "DoorRightLeft2.png", 0, 2, 0.1f, false);
		SpriteRenderer->CreateAnimation("GimmickLeftDoorOpen", "DoorRightLeft2.png", 2, 2, 0.05f);

		SpriteRenderer->CreateAnimation("GimmickUpDoorClosing", "DoorDownUp2.png", 6, 8, 0.1f, false);
		SpriteRenderer->CreateAnimation("GimmickUpDoorClose", "DoorDownUp2.png", 0, 0, 0.05f);
		SpriteRenderer->CreateAnimation("GimmickUpDoorOpening", "DoorDownUp2.png", 0, 2, 0.1f, false);
		SpriteRenderer->CreateAnimation("GimmickUpDoorOpen", "DoorDownUp2.png", 2, 2, 0.05f);

		SpriteRenderer->CreateAnimation("GimmickDownDoorClosing", "DoorDownUp2.png", 9, 11, 0.1f, false);
		SpriteRenderer->CreateAnimation("GimmickDownDoorClose", "DoorDownUp2.png", 3, 3, 0.05f);
		SpriteRenderer->CreateAnimation("GimmickDownDoorOpening", "DoorDownUp2.png", 3, 5, 0.1f, false);
		SpriteRenderer->CreateAnimation("GimmickDownDoorOpen", "DoorDownUp2.png", 5, 5, 0.05f);


		SpriteRenderer->SetAnimationEvent("GimmickRightDoorClosing", 8, [this]()
			{
				SpriteRenderer->ChangeAnimation("GimmickRightDoorClose");
				ImmuneCollision->SetActive(false);
			});

		SpriteRenderer->SetAnimationEvent("GimmickRightDoorOpening", 5, [this]()
			{
				SpriteRenderer->ChangeAnimation("GimmickRightDoorOpen");
				ImmuneCollision->SetActive(false);
			});


		SpriteRenderer->SetAnimationEvent("GimmickLeftDoorClosing", 11, [this]()
			{
				SpriteRenderer->ChangeAnimation("GimmickLeftDoorClose");
				ImmuneCollision->SetActive(false);
			});

		SpriteRenderer->SetAnimationEvent("GimmickLeftDoorOpening", 2, [this]()
			{
				SpriteRenderer->ChangeAnimation("GimmickLeftDoorOpen");
				ImmuneCollision->SetActive(false);
			});


		SpriteRenderer->SetAnimationEvent("GimmickUpDoorClosing", 8, [this]()
			{
				SpriteRenderer->ChangeAnimation("GimmickUpDoorClose");
				ImmuneCollision->SetActive(false);
			});

		SpriteRenderer->SetAnimationEvent("GimmickUpDoorOpening", 2, [this]()
			{
				SpriteRenderer->ChangeAnimation("GimmickUpDoorOpen");
				ImmuneCollision->SetActive(false);
			});

		SpriteRenderer->SetAnimationEvent("GimmickDownDoorClosing", 11, [this]()
			{
				SpriteRenderer->ChangeAnimation("GimmickDownDoorClose");
				ImmuneCollision->SetActive(false);
			});		
		
		SpriteRenderer->SetAnimationEvent("GimmickDownDoorOpening", 5, [this]()
			{
				SpriteRenderer->ChangeAnimation("GimmickDownDoorOpen");
				ImmuneCollision->SetActive(false);
			});

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

ADoor::~ADoor()
{
}

void ADoor::BeginPlay()
{
	AEventActor::BeginPlay();

	//ChangeState(EDoorState::CLOSE);
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
	if (0 < PlayerDataManager::GetInstance().GetKey())
	{
		PlayerDataManager::GetInstance().AddKey(-1);
		//SpriteRenderer->SetOrder(Character->GetSpriteOrder() + 1);
		Owner = dynamic_cast<APlayerCharacter*>(Character);

		if (nullptr == Owner)
		{
			MSGASSERT("문의 캐릭터가 nullptr입니다.");
			return 0;
		}

		ChangeState(EDoorState::OPEN);
	}

	return 0;
}

void ADoor::ChangeState(EDoorState DoorState)
{
	if (CurDoorState == DoorState) return;

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
	switch (DoorType)
	{
	case EDoorType::KEYTYPE:
		switch (DoorDirection)
		{
		case EDoorDirection::RIGHT:
			break;
		case EDoorDirection::LEFT:
			break;
		case EDoorDirection::UP:
			SpriteRenderer->ChangeAnimation("KeyUpDoorClosing");
			break;
		case EDoorDirection::DOWN:
			SpriteRenderer->ChangeAnimation("KeyDownDoorClosing");
			break;
		default:
			break;
		}
		break;
	case EDoorType::GIMMICK:
		switch (DoorDirection)
		{
		case EDoorDirection::RIGHT:
			SpriteRenderer->ChangeAnimation("GimmickRightDoorClosing");
			break;
		case EDoorDirection::LEFT:
			SpriteRenderer->ChangeAnimation("GimmickLeftDoorClosing");
			break;
		case EDoorDirection::UP:
			SpriteRenderer->ChangeAnimation("GimmickUpDoorClosing");
			break;
		case EDoorDirection::DOWN:
			SpriteRenderer->ChangeAnimation("GimmickDownDoorClosing");
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void ADoor::StartOpen()
{
	switch (DoorType)
	{
	case EDoorType::KEYTYPE:
		switch (DoorDirection)
		{
		case EDoorDirection::RIGHT:
			break;
		case EDoorDirection::LEFT:
			break;
		case EDoorDirection::UP:
			SpriteRenderer->ChangeAnimation("KeyUpDoorOpening");
			break;
		case EDoorDirection::DOWN:
			SpriteRenderer->ChangeAnimation("KeyDownDoorOpening");
			break;
		default:
			break;
		}
		break;
	case EDoorType::GIMMICK:
		switch (DoorDirection)
		{
		case EDoorDirection::RIGHT:
			SpriteRenderer->ChangeAnimation("GimmickRightDoorOpening");
			break;
		case EDoorDirection::LEFT:
			SpriteRenderer->ChangeAnimation("GimmickLeftDoorOpening");
			break;
		case EDoorDirection::UP:
			SpriteRenderer->ChangeAnimation("GimmickUpDoorOpening");
			break;
		case EDoorDirection::DOWN:
			SpriteRenderer->ChangeAnimation("GimmickDownDoorOpening");
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void ADoor::Close(float DeltaTime)
{
	ImmuneCollision->SetActive(true);
}

void ADoor::Open(float DeltaTime)
{

}

void ADoor::SetDoorDirection(EDoorDirection Direction)
{
	DoorDirection = Direction;
	FVector2D SpriteScale = FVector2D::ZERO;
	switch (Direction)
	{
	case EDoorDirection::RIGHT:
	case EDoorDirection::LEFT:
		SpriteRenderer->SetSprite("DoorRightLeft2.png", 0);
		SpriteScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(FVector2D::ZERO);
		SpriteRenderer->SetComponentScale(SpriteScale);
		break;
	case EDoorDirection::UP:
	case EDoorDirection::DOWN:
		SpriteRenderer->SetSprite("DoorDownUp2.png", 0);
		SpriteScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(FVector2D::ZERO);
		SpriteRenderer->SetComponentScale(SpriteScale);
		break;
	default:
		break;
	}
}

EDoorDirection ADoor::GetDoorDirection()
{
	return DoorDirection;
}

void ADoor::SetDoorType(EDoorType Type)
{
	DoorType = Type;
}

EDoorType ADoor::GetDoorType()
{
	return DoorType;
}

void ADoor::SetDoorRenderOrder(int Order)
{
	this->SpriteRenderer->SetOrder(Order);
}
