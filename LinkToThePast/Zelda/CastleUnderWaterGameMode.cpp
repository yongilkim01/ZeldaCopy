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
#include <EngineCore/EngineAPICore.h>

ACastleUnderWaterGameMode::ACastleUnderWaterGameMode()
{

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

	TimeEventer.PushEvent(1.0f, [this]()
		{
			ChangeState(ECastleUnderWaterState::LINK_FALL);
		}
	);
}


void ACastleUnderWaterGameMode::BeginPlayRoomActor()
{
	Roomes.reserve(1);
	RoomDataes.reserve(1);

	RoomDataes.push_back({ { 0, 0 } ,{ 1434, 621 } });

	CreateRoomActor("CastleUnderWater", 0);

	//this->Roomes[0]->CreateEnvSprite("CastleUnderWater1Door1.png", FVector2D(282, 648), FVector2D(214, 24), ERenderOrder::FIRST_FLOOR_OBJ);
}

void ACastleUnderWaterGameMode::BeginPlayEnvActor()
{
	{
		LinkFather = GetWorld()->SpawnActor<ALinkFather>();
		LinkFather->SetActorLocation({ 596, 224 });
		LinkFather->SetActive(true);
	}
}

void ACastleUnderWaterGameMode::Tick(float DeltaTime)
{
	AZeldaGameMode::Tick(DeltaTime);

	//StartFsm.Update(DeltaTime);

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
	Player->SetActorLocation(FVector2D::LerpClimp(LinkStartLocation, LinkDestLocation, CurTime / 2.0f));

	if (UEngineMath::Abs(Player->GetActorLocation().Y - LinkDestLocation.Y) < 0.1f)
	{
		Player->SetActorLocation(LinkDestLocation);
		Player->SetCurDirection(FVector2D::LEFT);
		Player->ChangeState(EPlayerState::Idle);
		ChangeState(ECastleUnderWaterState::GAMEPLAY);
	}
}

void ACastleUnderWaterGameMode::StartGetWeapon()
{
	UIBox = GetWorld()->SpawnActor<AUIBox>();
	UIBox->SetActorLocation(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half() + FVector2D(10.0f, 200.0f));
	UIBox->SetIsShowFrame(false);

	std::vector<std::string> StrValues;
	StrValues.push_back("Help me...");
	StrValues.push_back("          ");
	StrValues.push_back("Please help me...");
	StrValues.push_back("I am a prisoner in the dungeon");
	StrValues.push_back("of the castle.");
	StrValues.push_back("My name is Zelda.");
	StrValues.push_back("The wizard, Agahnim, has done...");
	StrValues.push_back("something to the other missing");
	StrValues.push_back("girls. Now only I remain....");
	StrValues.push_back("Agahnim has seized control of");
	StrValues.push_back("the castle and is now trying to");
	StrValues.push_back("oepn the seven wise men is");
	StrValues.push_back("seal. ... ...");
	StrValues.push_back("I am in the dungeon of the");
	StrValues.push_back("castle.");
	StrValues.push_back("Please help me...");

	UIBox->CreateUIText(StrValues, 1.0f);

	USoundManager::GetInstance().PlayBGM("LTTP_Rain_InL.wav");
}

void ACastleUnderWaterGameMode::GetWeapon(float DeltaTime)
{
}


void ACastleUnderWaterGameMode::StartGamePlay()
{

}

void ACastleUnderWaterGameMode::GamePlay(float DeltaTime)
{
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
