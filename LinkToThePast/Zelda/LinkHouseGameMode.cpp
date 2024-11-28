#include "PreCompile.h"
#include "LinkHouseGameMode.h"
#include "ContentsEnum.h"
#include "Room.h"
#include "HouseBed.h"
#include "UIBox.h"
#include "Fade.h"
#include "PlayerCharacter.h"
#include "LinkFather.h"

#include <EnginePlatform/EngineInput.h>
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
		FadeBlueRenderer->SetAlphafloat(FadeAlpha);
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

	this->Roomes[0]->CreateEnvSprite("LinkHouse1Door1.png", FVector2D(282, 648), FVector2D(214, 24), ERenderOrder::FIRST_FLOOR_OBJ);
}

void ALinkHouseGameMode::BeginPlayEnvActor()
{
	HouseBed = GetWorld()->SpawnActor<AHouseBed>();
	HouseBed->SetActorLocation({ 216, 276 });

	LinkFather = GetWorld()->SpawnActor<ALinkFather>();
	LinkFather->SetActorLocation({ 528, 303 });
	LinkFather->SetActive(true);
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
	case ELinkHouseState::NPC_TALK:
		NPCTalk(DeltaTime);
		break;
	case ELinkHouseState::SKIP:
		Skip(DeltaTime);
		break;
	case ELinkHouseState::FADE_OUT:
		FadeOut(DeltaTime);
		break;
	case ELinkHouseState::NPC_MOVE_LEFT:
		NPCMoveLeft(DeltaTime);
		break;
	case ELinkHouseState::NPC_MOVE_DOWN:
		NPCMoveDown(DeltaTime);
		break;
	case ELinkHouseState::GAMEPLAY:
		GamePlay(DeltaTime);
		break;
	default:
		break;
	}
}

void ALinkHouseGameMode::StartHelpMsg()
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
}

void ALinkHouseGameMode::HelpMsg(float DeltaTime)
{
	if (EUIBoxState::END == UIBox->GetUIBoxState())
	{
		ChangeState(ELinkHouseState::FADE_OUT);
	}

	if (true == UEngineInput::GetInst().IsDown(VK_SPACE) ||
		true == UEngineInput::GetInst().IsDown(VK_RETURN))
	{
		ChangeState(ELinkHouseState::SKIP);
	}
}

void ALinkHouseGameMode::StartFadeOut()
{
	UIBox->ResetText();
}

void ALinkHouseGameMode::FadeOut(float DeltaTime)
{
	FadeAlpha -= 0.001f;
	FadeBlueRenderer->SetAlphafloat(FadeAlpha);

	if (FadeAlpha < 0.0f)
	{
		ChangeState(ELinkHouseState::NPC_TALK);
	}
}

void ALinkHouseGameMode::StartSkip()
{
	UIBox->ChangeState(EUIBoxState::SKIP);

	TimeEventer.PushEvent(1.0f, [this]()
		{
			ChangeState(ELinkHouseState::FADE_OUT);
		});
}

void ALinkHouseGameMode::Skip(float DeltaTime)
{
	if (true == UEngineInput::GetInst().IsDown(VK_SPACE) ||
		true == UEngineInput::GetInst().IsDown(VK_RETURN))
	{
		ChangeState(ELinkHouseState::SKIP);
	}
}

void ALinkHouseGameMode::StartNPCTalk()
{
	UIBox->ResetText();
	UIBox->SetActorLocation(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half() + FVector2D(10.0f, 200.0f));

	std::vector<std::string> StrValues;

	StrValues.push_back("Link, I am going out for a");
	StrValues.push_back("while. I will be back by morning.");
	StrValues.push_back("Do not leave the house.");

	UIBox->SetIsShowFrame(true);
	UIBox->CreateUIText(StrValues, 1.0f);

	LinkFather->ChangeState(ELinkFatherState::SIT_LEFT);
	Player->ChangeState(EPlayerState::WakeUp);

	TimeEventer.PushEvent(3.0f, [this]() 
		{
			ChangeState(ELinkHouseState::NPC_MOVE_LEFT);
		});
}

void ALinkHouseGameMode::NPCTalk(float DeltaTime)
{
}

void ALinkHouseGameMode::StartNPCMoveLeft()
{
	LinkFather->SetDestLocaion(LinkFather->GetActorLocation() - FVector2D(144.0f, 0.0f));
	LinkFather->ChangeState(ELinkFatherState::MOVE_LEFT);
}

void ALinkHouseGameMode::NPCMoveLeft(float DeltaTime)
{
	if (UEngineMath::Abs(LinkFather->GetActorLocation().X - LinkFather->GetDestLocation().X) < 0.1f)
	{
		LinkFather->SetActorLocation(LinkFather->GetDestLocation());
		LinkFather->SetDestLocaion(FVector2D::ZERO);
		ChangeState(ELinkHouseState::NPC_MOVE_DOWN);
	}
}

void ALinkHouseGameMode::StartNPCMoveDown()
{
	LinkFather->SetDestLocaion(LinkFather->GetActorLocation() + FVector2D(0.0f, 369.0f));
	LinkFather->ChangeState(ELinkFatherState::MOVE_DOWN);
}

void ALinkHouseGameMode::NPCMoveDown(float DeltaTime)
{
	if (UEngineMath::Abs(LinkFather->GetActorLocation().Y - LinkFather->GetDestLocation().Y) < 0.1f)
	{
		LinkFather->Destroy();
		ChangeState(ELinkHouseState::GAMEPLAY);
	}
}

void ALinkHouseGameMode::StartGamePlay()
{
	Player->ChangeState(EPlayerState::Idle);
	Player->SetActorLocation(Player->GetActorLocation() + FVector2D(70.0f, 0.0f));
	UIBox->ResetText();
}

void ALinkHouseGameMode::GamePlay(float DeltaTime)
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
	case ELinkHouseState::NPC_TALK:
		StartNPCTalk();
		break;
	case ELinkHouseState::SKIP:
		StartSkip();
		break;
	case ELinkHouseState::FADE_OUT:
		StartFadeOut();
		break;
	case ELinkHouseState::NPC_MOVE_LEFT:
		StartNPCMoveLeft();
		break;
	case ELinkHouseState::NPC_MOVE_DOWN:
		StartNPCMoveDown();
		break;
	case ELinkHouseState::GAMEPLAY:
		StartGamePlay();
		break;
	default:
		break;
	}

	CurState = State;
}
