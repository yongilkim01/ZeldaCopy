#include "PreCompile.h"
#include "LinkHouseGameMode.h"
#include "ContentsEnum.h"
#include "Room.h"
#include "HouseBed.h"
#include "UIBox.h"
#include "Fade.h"
#include "PlayerCharacter.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>

ALinkHouseGameMode::ALinkHouseGameMode()
{
	{
		FadeBlueRenderer = CreateDefaultSubObject<USpriteRenderer>();
		FadeBlueRenderer->SetSprite("FadeBlue.bmp");
		FVector2D Location = FadeBlueRenderer->SetSpriteScale(1.0f);
		FadeBlueRenderer->SetComponentLocation(Location.Half());
		FadeBlueRenderer->SetOrder(ERenderOrder::FADE_FIRST);
		FadeBlueRenderer->SetAlphafloat(0.85f);
		FadeBlueRenderer->SetActive(true);
	}
}

ALinkHouseGameMode::~ALinkHouseGameMode()
{
}

void ALinkHouseGameMode::BeginPlay()
{
	AZeldaGameMode::BeginPlay();

	Player = GetWorld()->GetPawn<APlayerCharacter>();

	BeginPlayRoomActor();
	BeginPlayEnvActor();
	BeginPlayEnemyActor();
	BeginPlayUI();

	Fade = GetWorld()->SpawnActor<AFade>();
	Fade->SetFadeSize(EFadeSize::BIG);
	Fade->SetActorLocation(HouseBed->GetActorLocation());
	Fade->FadeOut();


	TimeEventer.PushEvent(1.0f, [this]()
		{
			ChangeState(ELinkHouseState::HELPMSG);
		}
	);

	//StartFsm.CreateState(0, [this](float _DeltaTime)
	//	{
	//		static float CurTime = 0.0f;

	//		CurTime += _DeltaTime;

	//		if (3.0f <= CurTime)
	//		{
	//			StartFsm.ChangeState(1);
	//			return;
	//		}

	//		// 글자 출력해라.
	//		// 화면 밝아져라

	//	});

	//StartFsm.CreateState(1, [this](float _DeltaTime)
	//	{
	//		static float CurTime = 0.0f;

	//		CurTime += _DeltaTime;

	//		// 아빠가 왼쪽으로 가면
	//		if (3.0f <= CurTime)
	//		{
	//			StartFsm.ChangeState(2);
	//			return;
	//		}
	//		// 아빠 왼쪽으로 움직여라.
	//	});

	//StartFsm.CreateState(2, [this](float _DeltaTime)
	//	{
	//		static float CurTime = 0.0f;

	//		CurTime += _DeltaTime;
	//		if (3.0f <= CurTime)
	//		{
	//			StartFsm.ChangeState(3);
	//			return;
	//		}
	//		// 아빠 오른쪽으로 움직여라.
	//	});

	//StartFsm.CreateState(2, [this](float _DeltaTime)
	//	{
	//		static float CurTime = 0.0f;

	//		CurTime += _DeltaTime;
	//		if (3.0f <= CurTime)
	//		{
	//			// MainPlayer->SetActive(true);
	//			StartFsm.Stop();
	//			return;
	//		}
	//		// 아빠 오른쪽으로 움직여라.


	//	});


}


void ALinkHouseGameMode::BeginPlayRoomActor()
{
	Roomes.reserve(1);
	RoomDataes.reserve(1);

	RoomDataes.push_back({ { 0, 0 } ,{ 768, 672 } });

	CreateRoomActor("LinkHouse", 0);
}

void ALinkHouseGameMode::BeginPlayEnvActor()
{
	HouseBed = GetWorld()->SpawnActor<AHouseBed>();
	HouseBed->SetActorLocation({ 216, 276 });
}

void ALinkHouseGameMode::BeginPlayEnemyActor()
{
}

void ALinkHouseGameMode::Tick(float DeltaTime)
{
	AZeldaGameMode::Tick(DeltaTime);

	//StartFsm.Update(DeltaTime);

	switch (CurState)
	{
	case ELinkHouseState::HELPMSG:
		HelpMsg(DeltaTime);
		break;
	default:
		break;
	}
}

void ALinkHouseGameMode::StartHelpMsg()
{
	UIBox = GetWorld()->SpawnActor<AUIBox>();
	UIBox->SetActorLocation(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half() + FVector2D(0.0f, 100.0f));
	UIBox->SetIsShowFrame(false);

	std::vector<std::string> StrValues;
	StrValues.push_back("Help me...");
	StrValues.push_back("          ");
	StrValues.push_back("Please help me...");
	StrValues.push_back("I am a prisoner in the dungeon");
	StrValues.push_back("of the castle.");
	StrValues.push_back("My name is Zelda.");

	UIBox->CreateUIText(StrValues, 1.0f);
}

void ALinkHouseGameMode::HelpMsg(float DeltaTime)
{

}

void ALinkHouseGameMode::ChangeState(ELinkHouseState State)
{
	if (State == CurState) return;

	switch (State)
	{
	case ELinkHouseState::HELPMSG:
		StartHelpMsg();
		break;
	default:
		break;
	}

	CurState = State;
}
