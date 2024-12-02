#include "PreCompile.h"
#include "Grass.h"

#include "ContentsEnum.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.h"
#include "DropHeartStay.h"

#include <EngineBase/EngineDebug.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision2D.h>
#include <EngineCore/EngineCoreDebug.h>

AGrass::AGrass()
{
	// 스프라이트 컴포넌트 생성
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Grass.png");

		SpriteRenderer->CreateAnimation("Idle", "Grass.png", 0, 0, 0.05f, false);
		SpriteRenderer->CreateAnimation("Break", "GrassBreak.png", 0, 7, 0.05f, false);

		SpriteRenderer->SetAnimationEvent("Break", 7, std::bind(&AGrass::EndBreak, this));

		SpriteRenderer->ChangeAnimation("Idle");

		SpriteRenderer->SetSpriteScale(3.0f);

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
		ImmuneCollision->SetComponentScale({ 40, 40 });
		ImmuneCollision->SetCollisionGroup(ECollisionGroup::NOTMOVEABLE);
		ImmuneCollision->SetActive(false);
	}

	//DebugOn();
}

AGrass::~AGrass()
{
}

void AGrass::BeginPlay()
{
	AEventActor::BeginPlay();

	IsEquipable = true;
}

void AGrass::Tick(float DeltaTime)
{
	AEventActor::Tick(DeltaTime);

	switch (CurGrassState)
	{
	case EGrassState::NONE:
		break;
	case EGrassState::FOLLOW:
		Follow(DeltaTime);
		break;
	case EGrassState::THROW:
		Throw(DeltaTime);
		break;
	default:
		break;
	}
}

int AGrass::Interact(ABaseCharacter* Character)
{
	if (true == bEvent)
	{
		SoundPlayer = UEngineSound::Play("secret.wav");
	}
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
		MSGASSERT("항아리의 소유주 플레이어가 nullptr입니다.");
		return 0;
	}

	if (Owner->GetCurDirection() == FVector2D::RIGHT)
	{
		TimeEventer.PushEvent(0.3f, [this]()
			{
				SetActorLocation(Owner->GetActorLocation() + FVector2D(20.0f, -20.0f));
				SpriteRenderer->SetOrder(Owner->GetSpriteOrder() + 1);
			}
		, false, false);

		TimeEventer.PushEvent(0.6f, [this]()
			{
				SetActorLocation(Owner->GetActorLocation() + FVector2D(0.0f, -40.0f));
				SpriteRenderer->SetOrder(Owner->GetSpriteOrder() + 1);
				ChangeState(EGrassState::FOLLOW);
			}
		, false, false);
	}
	else if (Owner->GetCurDirection() == FVector2D::LEFT)
	{
		TimeEventer.PushEvent(0.3f, [this]()
			{
				SetActorLocation(Owner->GetActorLocation() + FVector2D(-20.0f, -20.0f));
				SpriteRenderer->SetOrder(Owner->GetSpriteOrder() + 1);
			}
		, false, false);

		TimeEventer.PushEvent(0.6f, [this]()
			{
				SetActorLocation(Owner->GetActorLocation() + FVector2D(0.0f, -40.0f));
				SpriteRenderer->SetOrder(Owner->GetSpriteOrder() + 1);
				ChangeState(EGrassState::FOLLOW);
			}
		, false, false);
	}
	else if (Owner->GetCurDirection() == FVector2D::UP)
	{
		TimeEventer.PushEvent(0.3f, [this]()
			{
				if (nullptr != Owner)
				{
					SetActorLocation(Owner->GetActorLocation() + FVector2D(0.0f, -20.0f));
					SpriteRenderer->SetOrder(Owner->GetSpriteOrder() + 1);
				}
			}
		, false, false);

		TimeEventer.PushEvent(0.6f, [this]()
			{
				SetActorLocation(GetActorLocation() + FVector2D(0.0f, -12.0f));
				SpriteRenderer->SetOrder(Owner->GetSpriteOrder() + 1);
				ChangeState(EGrassState::FOLLOW);
			}
		, false, false);
	}
	else if (Owner->GetCurDirection() == FVector2D::DOWN)
	{
		TimeEventer.PushEvent(0.3f, [this]()
			{
				SetActorLocation(Owner->GetActorLocation() + FVector2D(0.0f, -20.0f));
				SpriteRenderer->SetOrder(Owner->GetSpriteOrder() + 1);
			}
		, false, false);

		TimeEventer.PushEvent(0.6f, [this]()
			{
				SetActorLocation(GetActorLocation() + FVector2D(0.0f, -15.0f));
				SpriteRenderer->SetOrder(Owner->GetSpriteOrder() + 1);
				ChangeState(EGrassState::FOLLOW);
			}
		, false, false);
	}

	return 1;
}

void AGrass::Throw()
{
	CurDirection = Owner->GetCurDirection();
	ChangeState(EGrassState::THROW);
}

void AGrass::DestoryEventActor()
{
	if (false == IsDestorying)
	{
		IsDestorying = true;
		SoundPlayer = UEngineSound::Play("grass destroyed.wav");
		SpriteRenderer->ChangeAnimation("Break");
	}
}

void AGrass::Throw(float DeltaTime)
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

void AGrass::EndBreak()
{
	Destroy();
}

void AGrass::ChangeState(EGrassState GrassState)
{
	switch (GrassState)
	{
	case EGrassState::NONE:
		break;
	case EGrassState::FOLLOW:
		StartFollow();
		break;
	case EGrassState::THROW:
		StartThrow();
		break;
	default:
		break;
	}

	CurGrassState = GrassState;
}

void AGrass::StartFollow()
{
	IsControl = true;
}

void AGrass::StartThrow()
{
	Owner = nullptr;
}

void AGrass::Follow(float DeltaTime)
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