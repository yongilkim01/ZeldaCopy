#include "PreCompile.h"
#include "LinkFather.h"
#include "ContentsEnum.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineMath.h>

ALinkFather::ALinkFather()
{
	// 스프라이트 렌더러 컴포넌트 초기화
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("FatherSit.png", 0);
		SpriteRenderer->SetSpriteScale(3.0f);
		SpriteRenderer->SetOrder(ERenderOrder::FIRST_FLOOR_OBJ);

		SpriteRenderer->CreateAnimation("SitDown", "FatherSit.png", 0, 0, 0.01f, true);
		SpriteRenderer->CreateAnimation("SitLeft", "FatherSit.png", 1, 1, 0.01f, true);

		SpriteRenderer->CreateAnimation("MoveRight", "FatherMove.png", 0, 1, 0.5f, true);
		SpriteRenderer->CreateAnimation("MoveLeft", "FatherMove.png", 2, 3, 0.5f, true);
		SpriteRenderer->CreateAnimation("MoveDown", "FatherMove.png", 4, 5, 0.5f, true);
		
		SpriteRenderer->CreateAnimation("DeathWeapon", "FatherDeath.png", 0, 0, 0.01f, true);
		SpriteRenderer->CreateAnimation("DeathNoneWeapon", "FatherDeath.png", 1, 1, 0.01f, true);

		SpriteRenderer->ChangeAnimation("SitDown");
	}
}

ALinkFather::~ALinkFather()
{
}

void ALinkFather::BeginPlay()
{
	Super::BeginPlay();
	ChangeState(ELinkFatherState::SIT_DOWN);
}

void ALinkFather::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	switch (CurState)
	{
	case ELinkFatherState::SIT_DOWN:
		SitDown(DeltaTime);
		break;
	case ELinkFatherState::SIT_LEFT:
		SitLeft(DeltaTime);
		break;
	case ELinkFatherState::MOVE_LEFT:
		MoveLeft(DeltaTime);
		break;
	case ELinkFatherState::MOVE_DOWN:
		MoveDown(DeltaTime);
		break;
	default:
		break;
	}
}

void ALinkFather::StartSitDown()
{
	SpriteRenderer->ChangeAnimation("SitDown");
}

void ALinkFather::SitDown(float DeltaTime)
{
}

void ALinkFather::StartSitLeft()
{
	SpriteRenderer->ChangeAnimation("SitLeft");
}

void ALinkFather::SitLeft(float DeltaTime)
{
}

void ALinkFather::StartMoveLeft()
{
	SpriteRenderer->ChangeAnimation("MoveLeft");
	CurTime = 0.0f;
	SetStartLocation(GetActorLocation());
}

void ALinkFather::MoveLeft(float DeltaTime)
{
	CurTime += DeltaTime;

	SetActorLocation(FVector2D::LerpClimp(StartLocation, DestLocation, CurTime / 2.0f));
}

void ALinkFather::StartMoveDown()
{
	SpriteRenderer->ChangeAnimation("MoveDown");
	CurTime = 0.0f;
	SetStartLocation(GetActorLocation());
}

void ALinkFather::MoveDown(float DeltaTime)
{
	CurTime += DeltaTime;

	SetActorLocation(FVector2D::LerpClimp(StartLocation, DestLocation, CurTime / 3.0f));
}

void ALinkFather::ChangeState(ELinkFatherState State)
{
	if (State == CurState) return;
	
	switch (State)
	{
	case ELinkFatherState::SIT_DOWN:
		StartSitDown();
		break;
	case ELinkFatherState::SIT_LEFT:
		StartSitLeft();
		break;
	case ELinkFatherState::MOVE_LEFT:
		StartMoveLeft();
		break;
	case ELinkFatherState::MOVE_DOWN:
		StartMoveDown();
		break;
	default:
		break;
	}

	CurState = State;
}
