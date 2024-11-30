#include "PreCompile.h"
#include "Arrow.h"
#include "ContentsEnum.h"
#include "BaseCharacter.h"
#include "Room.h"
#include "PlayerCharacter.h"

#include <EngineBase/EngineMath.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision2D.h>

AArrow::AArrow()
{
	// 스프라이트 컴포넌트 생성
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Arrow.png", 0);
		FVector2D SpriteScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(FVector2D::ZERO);
		SpriteRenderer->SetComponentScale(SpriteScale);

	}
	// 충돌 컴포넌트 생성
	{
		Collision = CreateDefaultSubObject<UCollision2D>();
		Collision->SetComponentLocation({ 0, 0 });
		Collision->SetComponentScale({ 45, 15 });
		Collision->SetCollisionGroup(ECollisionGroup::PlayerAttack);
		Collision->SetActive(true);
	}
	DebugOn();
}

AArrow::~AArrow()
{
}

void AArrow::BeginPlay()
{
	Super::BeginPlay();
	ChangeState(EArrowState::THROW);

	PlayerCharacter = dynamic_cast<APlayerCharacter*>(GetWorld()->GetPawn());

}

void AArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (CurState)
	{
	case EArrowState::THROW:
		Throw(DeltaTime);
		break;
	case EArrowState::HIT:
		Hit(DeltaTime);
		break;
	case EArrowState::STUCK:
		Stuck(DeltaTime);
		break;
	default:
		break;
	}
}

void AArrow::StartThrow()
{
	SoundPlayer = UEngineSound::Play("arrow 1.wav");

	if (FVector2D::RIGHT == CurDirection)
	{
		SpriteRenderer->SetSprite("Arrow.png", 0);
		Collision->SetComponentScale({ 45, 15 });
	}
	else if (FVector2D::LEFT == CurDirection)
	{
		SpriteRenderer->SetSprite("Arrow.png", 3);
		Collision->SetComponentScale({ 45, 15 });
	}
	else if (FVector2D::UP == CurDirection)
	{
		SpriteRenderer->SetSprite("Arrow.png", 6);
		Collision->SetComponentScale({ 15, 45 });
	}
	else if (FVector2D::DOWN == CurDirection)
	{
		SpriteRenderer->SetSprite("Arrow.png", 9);
		Collision->SetComponentScale({ 15, 45 });
	}
}

void AArrow::StartHit()
{
	if (FVector2D::RIGHT == CurDirection)
	{
		SpriteRenderer->SetSprite("Arrow.png", 1);
	}
	else if (FVector2D::LEFT == CurDirection)
	{
		SpriteRenderer->SetSprite("Arrow.png", 4);
	}
	else if (FVector2D::UP == CurDirection)
	{
		SpriteRenderer->SetSprite("Arrow.png", 7);
	}
	else if (FVector2D::DOWN == CurDirection)
	{
		SpriteRenderer->SetSprite("Arrow.png", 10);
	}
}

void AArrow::StartStuck()
{
	if (FVector2D::RIGHT == CurDirection)
	{
		SpriteRenderer->SetSprite("Arrow.png", 2);
	}
	else if (FVector2D::LEFT == CurDirection)
	{
		SpriteRenderer->SetSprite("Arrow.png", 5);
	}
	else if (FVector2D::UP == CurDirection)
	{
		SpriteRenderer->SetSprite("Arrow.png", 8);
	}
	else if (FVector2D::DOWN == CurDirection)
	{
		SpriteRenderer->SetSprite("Arrow.png", 11);
	}
}

void AArrow::StartDestroy()
{
	Destroy();
}

void AArrow::Throw(float DeltaTime)
{
	if (nullptr == CollisionImage) return;

	AddActorLocation(CurDirection * Speed * DeltaTime);

	FVector2D CheckLocation = GetActorLocation();
	CheckLocation -= GetCurRoom()->GetActorLocation();

	FVector2D CheckSize = FVector2D::ZERO;

	if (FVector2D::RIGHT == CurDirection)
	{
		CheckSize = { 22.0f, 0.0f };
	}
	else if (FVector2D::LEFT == CurDirection)
	{
		CheckSize = { -22.0f, 0.0f };
	}
	else if (FVector2D::UP == CurDirection)
	{
		CheckSize = { 0.0f, -22.0f };
	}
	else if (FVector2D::DOWN == CurDirection)
	{
		CheckSize = { 0.0f, 22.0f };
	}

	UColor CheckColor = CollisionImage->GetColor(CheckLocation, UColor::PINK);

	if (UColor::PINK == CheckColor)
	{
		ChangeState(EArrowState::HIT);
	}

	ABaseCharacter* Character = dynamic_cast<ABaseCharacter*>(Collision->CollisionOnce(ECollisionGroup::EnemyBody));
	
	if (nullptr != Character &&
		0 < Character->GetCurrentHP())
	{
		HitCharacter = Character;
		PrevHitLocation = HitCharacter->GetActorLocation();
		Collision->SetActive(false);
		HitCharacter->TakeDamage(10, PlayerCharacter);
		ChangeState(EArrowState::HIT);
	}
}

void AArrow::Hit(float DeltaTime)
{
	HitCurrentTime += DeltaTime;

	if (nullptr == HitCharacter)
	{
		Destroy();
		return;
	}

	if (HitCheckTime < HitCurrentTime)
	{
		ChangeState(EArrowState::STUCK);
		return;
	}

	if (0 >= HitCharacter->GetCurrentHP())
	{
		ChangeState(EArrowState::DESTROY);
		return;
	}

	if (nullptr != HitCharacter)
	{
		int EnemyHP = HitCharacter->GetCurrentHP();
		if (0 >= HitCharacter->GetCurrentHP())
		{
			ChangeState(EArrowState::DESTROY);
			return;
		}
		FVector2D ChangeLocation = HitCharacter->GetHitLocation() - PrevHitLocation;
		AddActorLocation(ChangeLocation);
		PrevHitLocation = HitCharacter->GetHitLocation();
	}
}

void AArrow::Stuck(float DeltaTime)
{
	LifeCurrentTime += DeltaTime;

	if (LifeCheckTime < LifeCurrentTime)
	{
		Destroy();
	}

	if (nullptr == HitCharacter ||
		0 >= HitCharacter->GetCurrentHP())
	{
		ChangeState(EArrowState::DESTROY);
		return;
	}

	if (nullptr != HitCharacter)
	{
		int EnemyHP = HitCharacter->GetCurrentHP();
		if (0 >= HitCharacter->GetCurrentHP())
		{
			ChangeState(EArrowState::DESTROY);
			return;
		}

		FVector2D CheckLocation = HitCharacter->GetHitLocation();
		FVector2D ChangeLocation = HitCharacter->GetHitLocation() - PrevHitLocation;
		AddActorLocation(ChangeLocation);
		PrevHitLocation = HitCharacter->GetHitLocation();
	}
}

void AArrow::ChangeState(EArrowState State)
{
	if (CurState == State) return;

	switch (State)
	{
	case EArrowState::THROW:
		StartThrow();
		break;
	case EArrowState::HIT:
		StartHit();
		break;
	case EArrowState::STUCK:
		StartStuck();
		break;
	case EArrowState::DESTROY:
		StartDestroy();
		break;
	default:
		break;
	}

	CurState = State;
}

void AArrow::SetOrder(int Order)
{
	SpriteRenderer->SetOrder(Order);
}
