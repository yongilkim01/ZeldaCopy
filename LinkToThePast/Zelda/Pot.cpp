#include "PreCompile.h"
#include "Pot.h"

#include "ContentsEnum.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.h"
#include "DropHeartStay.h"

#include <EngineBase/EngineDebug.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision2D.h>
#include <EngineCore/EngineCoreDebug.h>

APot::APot()
{
	// ��������Ʈ ������Ʈ ����
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Pot.png");

		SpriteRenderer->CreateAnimation("Idle", "Pot.png", 0, 0, 0.05f, false);
		SpriteRenderer->CreateAnimation("Break", "PotBreak.png", 0, 7, 0.05f, false);

		SpriteRenderer->SetAnimationEvent("Break", 7, std::bind(&APot::EndBreak, this));

		SpriteRenderer->ChangeAnimation("Idle");
	
		SpriteRenderer->SetSpriteScale(1.0f);

	}
	{
		// �浹 ������Ʈ ����
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

APot::~APot()
{
}

void APot::BeginPlay()
{
	AEventActor::BeginPlay();

	IsEquipable = true;
}

void APot::Tick(float DeltaTime)
{
	AEventActor::Tick(DeltaTime);

	switch (CurPotState)
	{
	case EPotState::NONE:
		break;
	case EPotState::FOLLOW:
		Follow(DeltaTime);
		break;
	case EPotState::THROW:
		Throw(DeltaTime);
		break;
	default:
		break;
	}
}

int APot::Interact(ABaseCharacter* Character)
{
	ImmuneCollision->SetActive(false);
	ADropItem* DropItem = nullptr;
	switch (DropItemType)
	{
	case EDropItemType::KEY:
		break;
	case EDropItemType::LANTERN:
		break;
	case EDropItemType::HEART:
		DropItem = GetWorld()->SpawnActor<ADropHeartStayItem>();
		DropItem->SetEventActorRenderOrder(SpriteRenderer->GetOrder() + 1);
		DropItem->SetActorLocation(GetActorLocation());
		break;
	case EDropItemType::BOW:
		break;
	default:
		break;
	}

	SpriteRenderer->SetOrder(Character->GetSpriteOrder() + 1);
	Owner = dynamic_cast<APlayerCharacter*>(Character);


	if (nullptr == Owner)
	{
		MSGASSERT("�׾Ƹ��� ������ �÷��̾ nullptr�Դϴ�.");
		return 0;
	}

	if (Owner->GetCurDirection() == FVector2D::RIGHT)
	{
		TimeEventer.PushEvent(0.1f, [this]()
			{
				SetActorLocation(Owner->GetActorLocation() + FVector2D(20.0f, -20.0f));
				SpriteRenderer->SetOrder(Owner->GetSpriteOrder() + 1);
			}
		, false, false);

		TimeEventer.PushEvent(0.2f, [this]()
			{
				SetActorLocation(Owner->GetActorLocation() + FVector2D(0.0f, -40.0f));
				SpriteRenderer->SetOrder(Owner->GetSpriteOrder() + 1);
				ChangeState(EPotState::FOLLOW);
			}
		, false, false);
	}
	else if (Owner->GetCurDirection() == FVector2D::LEFT)
	{
		TimeEventer.PushEvent(0.1f, [this]()
			{
				SetActorLocation(Owner->GetActorLocation() + FVector2D(-20.0f, -20.0f));
				SpriteRenderer->SetOrder(Owner->GetSpriteOrder() + 1);
			}
		, false, false);

		TimeEventer.PushEvent(0.2f, [this]()
			{
				SetActorLocation(Owner->GetActorLocation() + FVector2D(0.0f, -40.0f));
				SpriteRenderer->SetOrder(Owner->GetSpriteOrder() + 1);
				ChangeState(EPotState::FOLLOW);
			}
		, false, false);
	}
	else if (Owner->GetCurDirection() == FVector2D::UP)
	{
		TimeEventer.PushEvent(0.1f, [this]()
			{
				if (nullptr != Owner)
				{
					SetActorLocation(Owner->GetActorLocation() + FVector2D(0.0f, -20.0f));
					SpriteRenderer->SetOrder(Owner->GetSpriteOrder() + 1);
				}
			}
		, false, false);

		TimeEventer.PushEvent(0.2f, [this]()
			{
				SetActorLocation(GetActorLocation() + FVector2D(0.0f, -12.0f));
				SpriteRenderer->SetOrder(Owner->GetSpriteOrder() + 1);
				ChangeState(EPotState::FOLLOW);
			}
		, false, false);
	}
	else if (Owner->GetCurDirection() == FVector2D::DOWN)
	{
		TimeEventer.PushEvent(0.1f, [this]()
			{
				SetActorLocation(Owner->GetActorLocation() + FVector2D(0.0f, -20.0f));
				SpriteRenderer->SetOrder(Owner->GetSpriteOrder() + 1);
			}
		, false, false);

		TimeEventer.PushEvent(0.2f, [this]()
			{
				SetActorLocation(GetActorLocation() + FVector2D(0.0f, -15.0f));
				SpriteRenderer->SetOrder(Owner->GetSpriteOrder() + 1);
				ChangeState(EPotState::FOLLOW);
			}
		, false, false);
	}

	return 1;
}

void APot::Throw()
{
	CurDirection = Owner->GetCurDirection();
	ChangeState(EPotState::THROW);
}

void APot::DestoryEventActor()
{
	SpriteRenderer->ChangeAnimation("Break");
}

void APot::Throw(float DeltaTime)
{
	this->AddEventActorLocation(CurDirection * DeltaTime * ThrowSpeed);

	ABaseCharacter* Result = dynamic_cast<ABaseCharacter*>(Collision->CollisionOnce(ECollisionGroup::EnemyBody));
	if (nullptr != Result)
	{
		Result->TakeDamage(10, this);
		this->ThrowSpeed = 0.0f;
		DestoryEventActor();
	}
}

void APot::EndBreak()
{
	Destroy();
}

void APot::ChangeState(EPotState PotState)
{
	switch (PotState)
	{
	case EPotState::NONE:
		break;
	case EPotState::FOLLOW:
		StartFollow();
		break;
	case EPotState::THROW:
		StartThrow();
		break;
	default:
		break;
	}

	CurPotState = PotState;
}

void APot::StartFollow()
{
	IsControl = true;
}

void APot::StartThrow()
{
	Owner = nullptr;
}

void APot::Follow(float DeltaTime)
{
	if (Owner->GetCurDirection() == FVector2D::RIGHT)
	{
		SetActorLocation(Owner->GetActorLocation() + FVector2D(0.0f, -40.0f));
	}
	else if (Owner->GetCurDirection() == FVector2D::LEFT)
	{
		SetActorLocation(Owner->GetActorLocation() + FVector2D(0.0f, -40.0f));
	}
	else if (Owner->GetCurDirection() == FVector2D::UP)
	{
		SetActorLocation(Owner->GetActorLocation() + FVector2D(0.0f, -32.0f));
	}
	else if (Owner->GetCurDirection() == FVector2D::DOWN)
	{
		SetActorLocation(Owner->GetActorLocation() + FVector2D(0.0f, -35.0f));
	}

	SpriteRenderer->SetOrder(Owner->GetSpriteOrder() + 1);
}