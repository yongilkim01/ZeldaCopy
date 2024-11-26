#include "PreCompile.h"
#include "TitleManager.h"
#include "ContentsEnum.h"

#include <EngineBase/EngineMath.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>

ATitleManager::ATitleManager()
{
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	FVector2D WindowHalfSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half() + FVector2D(0.0f, 30.0f);

	Triforces.reserve(3);
	TriforceLocations.reserve(3);
	TriforceFinalLocations.reserve(3);

	{
		TriforceLocations.push_back(UEngineMath::RotateToDegree(270.0f, WindowHalfSize, TriforceDistance));
		TriforceLocations.push_back(UEngineMath::RotateToDegree(30.0f, WindowHalfSize, TriforceDistance));
		TriforceLocations.push_back(UEngineMath::RotateToDegree(150.0f, WindowHalfSize, TriforceDistance));

		TriforceFinalLocations.push_back(FVector2D(380, 242));
		TriforceFinalLocations.push_back(FVector2D(442, 362));
		TriforceFinalLocations.push_back(FVector2D(319, 362));

		EnvInitLocation = WindowHalfSize + FVector2D(0.0f, -53.0f);
		FadeGreenInitLocation = WindowHalfSize;
	}

	{
		BackgroundRenderer = CreateDefaultSubObject<USpriteRenderer>();
		BackgroundRenderer->SetOrder(0);
		BackgroundRenderer->SetSprite("TitleBackground.png");
		FVector2D BackgroundScale = BackgroundRenderer->SetSpriteScale(1.0f);
		BackgroundRenderer->SetComponentLocation(BackgroundScale.Half());
		BackgroundRenderer->SetCameraEffect(false);

		LogoRenderer = CreateDefaultSubObject<USpriteRenderer>();
		LogoRenderer->SetOrder(3);
		LogoRenderer->SetSprite("NintendoPresentLogo.png");
		LogoRenderer->SetSpriteScale(3.0f);
		LogoRenderer->SetComponentLocation(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half());
		LogoRenderer->SetCameraEffect(false);
		LogoRenderer->SetActive(false);

		for (size_t i = 0; i < 3; i++)
		{

			USpriteRenderer* TriforceRenderer = CreateDefaultSubObject<USpriteRenderer>();
			TriforceRenderer->SetOrder(4);
			TriforceRenderer->SetSprite("TitleTriforce.png", 0);

			if (0 == static_cast<int>(i) || 2 == static_cast<int>(i))
			{
				TriforceRenderer->CreateAnimation("RotateTriforce", "TitleTriforceReverse.png", 0, 170, 0.03f, false);
				TriforceRenderer->CreateAnimation("RotateDone", "TitleTriforceReverse.png", 170, 170, 0.03f);
			}
			else
			{
				TriforceRenderer->CreateAnimation("RotateTriforce", "TitleTriforce.png", 0, 170, 0.03f, false);
				TriforceRenderer->CreateAnimation("RotateDone", "TitleTriforce.png", 170, 170, 0.03f);
			};

			TriforceRenderer->SetSpriteScale(1.0f);
			TriforceRenderer->SetComponentLocation(TriforceLocations[i]);
			TriforceRenderer->SetCameraEffect(false);
			TriforceRenderer->SetActive(false);

			Triforces.push_back(TriforceRenderer);
		}

		Triforces[0]->SetAnimationEvent("RotateTriforce", 17, [this]() {
			EffectSoundPlayer = UEngineSound::Play("Title.mp3");
			});

		TitleRenderer = CreateDefaultSubObject<USpriteRenderer>();
		TitleRenderer->SetOrder(3);
		TitleRenderer->SetSprite("TitleLogo.png");
		TitleRenderer->SetSpriteScale(1.0f);
		TitleRenderer->SetComponentLocation(FVector2D(407, 323));
		TitleRenderer->SetCameraEffect(false);
		TitleRenderer->SetActive(true);
		TitleRenderer->SetAlphafloat(TitleAlpha);

		TitleZRenderer = CreateDefaultSubObject<USpriteRenderer>();
		TitleZRenderer->SetOrder(7);
		TitleZRenderer->SetSprite("TitleZmiddle.png");
		TitleZRenderer->SetSpriteScale(1.0f);
		TitleZRenderer->SetComponentLocation(TitleRenderer->GetComponentLocation() - TitleZLocation);
		TitleZRenderer->SetCameraEffect(false);
		TitleZRenderer->SetActive(true);
		TitleZRenderer->SetAlphafloat(TitleAlpha);

		SwordRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SwordRenderer->SetOrder(6);
		SwordRenderer->SetSprite("TitleSword.png");
		SwordRenderer->SetSpriteScale(1.0f);
		SwordRenderer->SetComponentLocation(SwordInitLocation);
		SwordRenderer->SetCameraEffect(false);
		SwordRenderer->SetActive(true);
		SwordRenderer->SetAlphafloat(1.0f);

		EnvRenderer = CreateDefaultSubObject<USpriteRenderer>();
		EnvRenderer->SetOrder(1);
		EnvRenderer->SetSprite("TitleEnv.png");
		EnvRenderer->SetSpriteScale(1.0f);
		EnvRenderer->SetComponentLocation(EnvInitLocation);
		EnvRenderer->SetCameraEffect(false);
		EnvRenderer->SetActive(true);
		EnvRenderer->SetAlphafloat(0.0f);

		FadeGreenRenderer = CreateDefaultSubObject<USpriteRenderer>();
		FadeGreenRenderer->SetOrder(10);
		FadeGreenRenderer->SetSprite("FadeGreen.png");
		FVector2D FadeGreenScale = FadeGreenRenderer->SetSpriteScale(1.0f);
		FadeGreenRenderer->SetComponentLocation(FadeGreenScale.Half());
		FadeGreenRenderer->SetCameraEffect(false);
		FadeGreenRenderer->SetAlphafloat(0.0f);

		FadeWhiteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		FadeWhiteRenderer->SetOrder(2);
		FadeWhiteRenderer->SetSprite("FadeWhite.png");
		FadeWhiteRenderer->SetSpriteScale(1.0f);
		FadeWhiteRenderer->SetComponentLocation(EnvInitLocation);
		FadeWhiteRenderer->SetCameraEffect(false);
		FadeWhiteRenderer->SetActive(true);
		FadeWhiteRenderer->SetAlphafloat(FadeWhiteAlpha);

		FadeRenderer = CreateDefaultSubObject<USpriteRenderer>();
		FadeRenderer->SetOrder(10);
		FadeRenderer->SetSprite("Fade.bmp");
		FVector2D FadeScale = FadeRenderer->SetSpriteScale(1.0f);
		FadeRenderer->SetComponentLocation(FadeScale.Half());
		FadeRenderer->SetCameraEffect(false);
		FadeRenderer->SetAlphafloat(0.0f);
	}
}

ATitleManager::~ATitleManager()
{
}

void ATitleManager::BeginPlay()
{
	Super::BeginPlay();

	TimeEventer.PushEvent(0.5f, [this]()
		{
			ChangeState(ETitleState::LOGO);
		}
	, false, false);
}

void ATitleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (TitleState)
	{
	case ETitleState::LOGO:
		Logo(DeltaTime);
		break;
	case ETitleState::TRIFORCE:
		Triforce(DeltaTime);
		break;
	case ETitleState::TITLELOGO:
		TitleLogo(DeltaTime);
		break;
	case ETitleState::SWORDLOGO:
		SwordLogo(DeltaTime);
		break;
	case ETitleState::TITLE:
		Title(DeltaTime);
		break;
	default:
		break;
	}
}

void ATitleManager::StartLogo()
{
	EffectSoundPlayer = UEngineSound::Play("rupee.wav");
	LogoRenderer->SetActive(true);
}

void ATitleManager::StartTriforce()
{
	for (size_t i = 0; i < Triforces.size(); i++)
	{
		Triforces[i]->SetActive(true);
		Triforces[i]->ChangeAnimation("RotateTriforce");
	}

	LogoRenderer->SetSprite("NintentdoAgeLogo.png");
	LogoRenderer->SetSpriteScale(3.0f);
	LogoRenderer->SetComponentLocation(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half() + FVector2D(0.0f, 250.0f));
	LogoRenderer->SetCameraEffect(false);
	LogoRenderer->SetActive(true);
	LogoRenderer->SetAlphafloat(1.0f);
}

void ATitleManager::StartTitleLogo()
{
}

void ATitleManager::StartSwordLogo()
{
	EffectSoundPlayer = UEngineSound::Play("sword shine 1.wav");
}

void ATitleManager::StartTitle()
{
	//if (ETitleState::SWORDLOGO != PrevState)
	//{
	//	EffectSoundPlayer = UEngineSound::Play("Title.mp3");
	//}
	//EffectSoundPlayer = UEngineSound::Play("Title.mp3");
	LogoRenderer->SetSprite("NintentdoAgeLogo.png");
	LogoRenderer->SetSpriteScale(3.0f);
	LogoRenderer->SetComponentLocation(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half() + FVector2D(0.0f, 250.0f));
	LogoRenderer->SetCameraEffect(false);
	LogoRenderer->SetActive(true);
	LogoRenderer->SetAlphafloat(1.0f);

	Triforces[0]->SetComponentLocation(TriforceFinalLocations[0]);
	Triforces[1]->SetComponentLocation(TriforceFinalLocations[1]);
	Triforces[2]->SetComponentLocation(TriforceFinalLocations[2]);

	Triforces[0]->ChangeAnimation("RotateDone", true);
	Triforces[1]->ChangeAnimation("RotateDone", true);
	Triforces[2]->ChangeAnimation("RotateDone", true);

	TitleRenderer->SetAlphafloat(1.0f);
	TitleRenderer->SetOrder(5);
	TitleZRenderer->SetAlphafloat(1.0f);

	SwordRenderer->SetComponentLocation(SwordFinalLocation);

	EnvRenderer->SetAlphafloat(1.0f);

}


void ATitleManager::Logo(float DeltaTime)
{
	LogoTime += DeltaTime;

	if (LogoTime >= 1.0f)
	{
		FadeValue += 0.01f;
		FadeRenderer->SetAlphafloat(FadeValue);

		if (FadeValue >= 1.0f)
		{
			LogoRenderer->SetAlphafloat(0.0f);
			FadeRenderer->SetAlphafloat(0.0f);
			ChangeState(ETitleState::TRIFORCE);
		}
	}
}

void ATitleManager::Triforce(float DeltaTime)
{
	CurTime += DeltaTime;

	for (size_t i = 0; i < Triforces.size(); i++)
	{
		Triforces[i]->SetComponentLocation(FVector2D::LerpClimp(TriforceLocations[i], TriforceFinalLocations[i], CurTime / 5.0f));
	}

	if (CurTime >= 7.0f)
	{
		ChangeState(ETitleState::TITLELOGO);
		CurTime = 0.0f;
	}

}

void ATitleManager::TitleLogo(float DeltaTime)
{
	CurTime += DeltaTime;

	if (TitleAlpha < 1.0f)
	{
		TitleAlpha += 0.005f;
		TitleRenderer->SetAlphafloat(TitleAlpha);
		TitleZRenderer->SetAlphafloat(TitleAlpha);
	}
	else
	{
		TitleRenderer->SetOrder(5);
	}

	if (CurTime >= 1.5f)
	{
		ChangeState(ETitleState::SWORDLOGO);
		CurTime = 0.0f;
	}
}
void ATitleManager::SwordLogo(float DeltaTime)
{
	CurTime += DeltaTime;

	SwordRenderer->SetComponentLocation(FVector2D::LerpClimp(SwordInitLocation, SwordFinalLocation, CurTime / 0.1f));

	if (0.1f <= CurTime && CurTime < 0.3f)
	{
		FadeGreenRenderer->SetAlphafloat(UEngineMath::Sin(CurTime * 500.0f));
		FadeWhiteAlpha += 0.01f;
		FadeWhiteRenderer->SetAlphafloat(FadeWhiteAlpha);
		EnvRenderer->SetAlphafloat(1.0f);
	}
	else if (0.3f <= CurTime && FadeWhiteAlpha > 0.0f)
	{
		FadeGreenRenderer->SetAlphafloat(0.0f);
		FadeWhiteAlpha -= 0.006f;
		FadeWhiteRenderer->SetAlphafloat(FadeWhiteAlpha);

		if (FadeWhiteAlpha <= 0.0f)
		{
			PrevState = TitleState;
			ChangeState(ETitleState::TITLE);
		}
	}
}

void ATitleManager::Title(float DeltaTime)
{
}

void ATitleManager::ChangeState(ETitleState State)
{
	if (State == TitleState) return;

	PrevState = TitleState;

	switch (State)
	{
	case ETitleState::LOGO:
		StartLogo();
		break;
	case ETitleState::TRIFORCE:
		StartTriforce();
		break;
	case ETitleState::TITLELOGO:
		StartTitleLogo();
		break;
	case ETitleState::SWORDLOGO:
		StartSwordLogo();
		break;
	case ETitleState::TITLE:
		StartTitle();
		break;
	default:
		break;
	}

	TitleState = State;
}

