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
	}

	{
		BackgroundRenderer = CreateDefaultSubObject<USpriteRenderer>();
		BackgroundRenderer->SetOrder(0);
		BackgroundRenderer->SetSprite("TitleBackground.png");
		FVector2D BackgroundScale = BackgroundRenderer->SetSpriteScale(1.0f);
		BackgroundRenderer->SetComponentLocation(BackgroundScale.Half());
		BackgroundRenderer->SetCameraEffect(false);

		LogoRenderer = CreateDefaultSubObject<USpriteRenderer>();
		LogoRenderer->SetOrder(1);
		LogoRenderer->SetSprite("NintendoPresentLogo.png");
		LogoRenderer->SetSpriteScale(3.0f);
		LogoRenderer->SetComponentLocation(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half());
		LogoRenderer->SetCameraEffect(false);
		LogoRenderer->SetActive(false);

		for (size_t i = 0; i < 3; i++)
		{

			USpriteRenderer* TriforceRenderer = CreateDefaultSubObject<USpriteRenderer>();
			TriforceRenderer->SetOrder(1);
			TriforceRenderer->SetSprite("TitleTriforce.png", 0);

			if (0 == static_cast<int>(i) || 2 == static_cast<int>(i))
			{
				TriforceRenderer->CreateAnimation("RotateTriforce", "TitleTriforceReverse.png", 0, 170, 0.03f, false);
			}
			else
			{
				TriforceRenderer->CreateAnimation("RotateTriforce", "TitleTriforce.png", 0, 170, 0.03f, false);
			}

			TriforceRenderer->SetAnimationEvent("RotateTriforce", 170, [this]() {
					ChangeState(ETitleState::TITLELOGO);
				});

			TriforceRenderer->SetSpriteScale(1.0f);
			TriforceRenderer->SetComponentLocation(TriforceLocations[i]);
			TriforceRenderer->SetCameraEffect(false);
			TriforceRenderer->SetActive(false);

			Triforces.push_back(TriforceRenderer);
		}

		Triforces[0]->SetAnimationEvent("RotateTriforce", 17, [this]() {
			EffectSoundPlayer = UEngineSound::Play("Title.mp3");
			});

		FadeRenderer = CreateDefaultSubObject<USpriteRenderer>();
		FadeRenderer->SetOrder(1);
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
}

void ATitleManager::StartTitleLogo()
{
}

void ATitleManager::StartSwordLogo()
{
}

void ATitleManager::StartTitle()
{
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
	FVector2D WindowHalfSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half() + FVector2D(0.0f, 30.0f);

	{
		TriforceDistance -= TriforceSpeed * DeltaTime;
		CurTime += DeltaTime;

		for (size_t i = 0; i < Triforces.size(); i++)
		{
			Triforces[i]->SetComponentLocation(FVector2D::LerpClimp(TriforceLocations[i], TriforceFinalLocations[i], CurTime/5.0f));
		}
	}
}

void ATitleManager::TitleLogo(float DeltaTime)
{
}

void ATitleManager::SwordLogo(float DeltaTime)
{
}

void ATitleManager::Title(float DeltaTime)
{
}

void ATitleManager::ChangeState(ETitleState State)
{
	if (State == TitleState) return;

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

