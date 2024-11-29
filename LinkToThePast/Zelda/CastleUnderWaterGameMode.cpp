#include "PreCompile.h"
#include "CastleUnderWaterGameMode.h"
#include "ContentsEnum.h"
#include "Room.h"
#include "HouseBed.h"
#include "UIBox.h"
#include "Fade.h"
#include "PlayerCharacter.h"
#include "LinkFather.h"
#include "Pot.h"
#include "Chest.h"
#include "SoundManager.h"
#include "LevelMove.h"

#include <EngineBase/EngineMath.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision2D.h>
#include <EngineCore/EngineAPICore.h>

ACastleUnderWaterGameMode::ACastleUnderWaterGameMode()
{
	{
		LinkCheckCollision = CreateDefaultSubObject<UCollision2D>();
		LinkCheckCollision->SetComponentLocation({ 596, 224 });
		LinkCheckCollision->SetComponentScale({ 50, 50 });
		LinkCheckCollision->SetCollisionGroup(ECollisionGroup::EventTarget);
		LinkCheckCollision->SetActive(true);
	}

	DebugOn();
}

ACastleUnderWaterGameMode::~ACastleUnderWaterGameMode()
{
}

void ACastleUnderWaterGameMode::BeginPlay()
{
	AZeldaGameMode::BeginPlay();

	Player = GetWorld()->GetPawn<APlayerCharacter>();

	BeginPlayRoomActor();
	BeginPlayEnvActor();
	BeginPlayEnemyActor();
	BeginPlayUI();

	TimeEventer.PushEvent(0.2f, [this]()
		{
			ChangeState(ECastleUnderWaterState::LINK_FALL);
		}
	);
}


void ACastleUnderWaterGameMode::BeginPlayRoomActor()
{
	Roomes.reserve(1);
	RoomDataes.reserve(1);

	RoomDataes.push_back({ { 0, 0 } ,{ 1434, 700 } });

	CreateRoomActor("CastleUnderWater", 0);

	//this->Roomes[0]->CreateEnvSprite("CastleUnderWater1Door1.png", FVector2D(282, 648), FVector2D(214, 24), ERenderOrder::FIRST_FLOOR_OBJ);
}

void ACastleUnderWaterGameMode::BeginPlayEnvActor()
{
	{
		LinkFather = GetWorld()->SpawnActor<ALinkFather>();
		LinkFather->SetActorLocation({ 596, 224 });
		LinkFather->ChangeState(ELinkFatherState::DEATH_WEAPON);
		LinkFather->SetActive(true);
	}
}

void ACastleUnderWaterGameMode::Tick(float DeltaTime)
{
	AZeldaGameMode::Tick(DeltaTime);

	switch (CurState)
	{
	case ECastleUnderWaterState::LINK_FALL:
		FallLink(DeltaTime);
		break;
	case ECastleUnderWaterState::ITEM_GET:
		GetWeapon(DeltaTime);
		break;
	case ECastleUnderWaterState::GAMEPLAY:
		GamePlay(DeltaTime);
		break;
	default:
		break;
	}
}

void ACastleUnderWaterGameMode::StartFallLink()
{
	Player->ChangeState(EPlayerState::TurnFall);
	Player->SetActorLocation(LinkStartLocation);
	CurTime = 0.0f;
}

void ACastleUnderWaterGameMode::FallLink(float DeltaTime)
{
	CurTime += DeltaTime;
	Player->SetActorLocation(FVector2D::LerpClimp(LinkStartLocation, LinkDestLocation, CurTime / 1.0f));

	if (UEngineMath::Abs(Player->GetActorLocation().Y - LinkDestLocation.Y) < 0.1f)
	{
		Player->SetActorLocation(LinkDestLocation);
		ChangeState(ECastleUnderWaterState::GAMEPLAY);
	}
}

void ACastleUnderWaterGameMode::StartGetWeapon()
{
	LinkCheckCollision->SetActive(false);

	UIBox = GetWorld()->SpawnActor<AUIBox>();
	UIBox->SetActorLocation(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half() + FVector2D(10.0f, 200.0f));

	std::vector<std::string> StrValues;
	StrValues.push_back("Unnh... Link, I did not want");
	StrValues.push_back("you involved in this... I told");
	StrValues.push_back("you not to leave the house...");
	StrValues.push_back("Take my sword and shield.");

	UIBox->CreateUIText(StrValues, 1.0f);

	TimeEventer.PushEvent(5.0f, [this]()
		{
			Player->ChangeState(EPlayerState::SwordGet);
			LinkFather->ChangeState(ELinkFatherState::DEATH_NONWEAPON);
			UIBox->ResetText();
		}
	);

	TimeEventer.PushEvent(8.0f, [this]()
		{
			ChangeState(ECastleUnderWaterState::GAMEPLAY);
		}
	);

	//USoundManager::GetInstance().PlayBGM("LTTP_Rain_InL.wav");
}

void ACastleUnderWaterGameMode::GetWeapon(float DeltaTime)
{
}


void ACastleUnderWaterGameMode::StartGamePlay()
{
	Player->SetCurDirection(FVector2D::LEFT);
	Player->ChangeState(EPlayerState::Idle);
}

void ACastleUnderWaterGameMode::GamePlay(float DeltaTime)
{
	APlayerCharacter* Actor = dynamic_cast<APlayerCharacter*>(LinkCheckCollision->CollisionOnce(ECollisionGroup::PlayerBody));

	if (nullptr != Actor)
	{
		ChangeState(ECastleUnderWaterState::ITEM_GET);
	}
}

void ACastleUnderWaterGameMode::ChangeState(ECastleUnderWaterState State)
{
	if (State == CurState) return;

	switch (State)
	{
	case ECastleUnderWaterState::LINK_FALL:
		StartFallLink();
		break;
	case ECastleUnderWaterState::ITEM_GET:
		StartGetWeapon();
		break;
	case ECastleUnderWaterState::GAMEPLAY:
		StartGamePlay();
		break;
	default:
		break;
	}

	CurState = State;
}
