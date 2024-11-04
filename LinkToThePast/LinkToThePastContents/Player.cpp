#include "PreCompile.h"
#include "Player.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>

#include <EnginePlatform/EngineInput.h>
#include "Room.h"
#include "RoomManageMode.h"

APlayer* APlayer::StaticPlayer = nullptr;

void APlayer::RunSoundPlay()
{

}


APlayer::APlayer()
{
	SetActorLocation({ 380, 340 });
	Speed = 1000.f;
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("LinkMoveDown.png");
	SpriteRenderer->SetSpriteScale(3.0f);

	SpriteRenderer->CreateAnimation("Run_Right", "LinkMoveRight.png", 1, 8, 0.1f);
	SpriteRenderer->CreateAnimation("Run_Left", "LinkMoveLeft.png", 1, 8, 0.1f);
	SpriteRenderer->CreateAnimation("Run_Up", "LinkMoveUp.png", 1, 8, 0.1f);
	SpriteRenderer->CreateAnimation("Run_Down", "LinkMoveDown.png", 1, 8, 0.1f);

	SpriteRenderer->CreateAnimation("Idle_Right", "LinkMoveRight.png", 0, 0, 0.1f);
	SpriteRenderer->CreateAnimation("Idle_Left", "LinkMoveLeft.png", 0, 0, 0.1f);
	SpriteRenderer->CreateAnimation("Idle_Up", "LinkMoveUp.png", 0, 0, 0.1f);
	SpriteRenderer->CreateAnimation("Idle_Down", "LinkMoveDown.png", 0, 0, 0.1f);

	SpriteRenderer->CreateAnimation("Attack_Right", "LinkAttackRight.png", 0, 5, 0.04f, false);
	SpriteRenderer->CreateAnimation("Attack_Left", "LinkAttackLeft.png", 0, 5, 0.04f, false);
	SpriteRenderer->CreateAnimation("Attack_Up", "LinkAttackUp.png", 0, 4, 0.04f, false);
	SpriteRenderer->CreateAnimation("Attack_Down", "LinkAttackDown.png", 0, 5, 0.04f, false);

	SpriteRenderer->SetAnimationEvent("Attack_Right", 5, std::bind(&APlayer::SetPlayerStateToIdle, this));
	SpriteRenderer->SetAnimationEvent("Attack_Left", 5, std::bind(&APlayer::SetPlayerStateToIdle, this));
	SpriteRenderer->SetAnimationEvent("Attack_Up", 4, std::bind(&APlayer::SetPlayerStateToIdle, this));
	SpriteRenderer->SetAnimationEvent("Attack_Down", 5, std::bind(&APlayer::SetPlayerStateToIdle, this));

	SpriteRenderer->ChangeAnimation("Idle_Down");

	CurState = EPlayerState::Idle;

	StaticPlayer = this;
	IsCameraControl = true;
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	GetWorld()->SetCameraPivot(Size.Half() * -1);
}

void APlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ARoomManageMode::IsMapMoving == true) return;

	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / DeltaTime));
	UEngineDebug::CoreOutPutString("PlayerPos : " + GetActorLocation().ToString());
	UEngineDebug::CoreOutPutString("PlayerScale : " + GetTransform().Scale.ToString());
	UEngineDebug::CoreOutPutString("PlayerLefTop : " + GetTransform().CenterLeftTop().ToString());
	PrintDebugPlayerState();

	switch (CurState)
	{
	case EPlayerState::None:
		break;
	case EPlayerState::Idle:
		Idle();
		break;
	case EPlayerState::Move:
		Move(DeltaTime);
		break;
	case EPlayerState::Attack:
		Attack();
		break;
	default:
		break;
	}
}

void APlayer::PrintDebugPlayerState()
{
	switch (CurState)
	{
	case EPlayerState::None:
		UEngineDebug::CoreOutPutString("Player Current State : None ");
		break;
	case EPlayerState::Idle:
		UEngineDebug::CoreOutPutString("Player Current State : Idle ");
		break;
	case EPlayerState::Move:
		UEngineDebug::CoreOutPutString("Player Current State : Move ");
		break;
	case EPlayerState::Attack:
		UEngineDebug::CoreOutPutString("Player Current State : Attack ");
		break;
	default:
		break;
	}
}

void APlayer::SetPlayerStateToIdle()
{
	SpriteRenderer->ChangeAnimation("Idle_Down");
	CurState = EPlayerState::Idle;
}

void APlayer::PlayAttackAnimation(FVector2D Dir)
{
	if (Dir == FVector2D::RIGHT)
	{
		SpriteRenderer->ChangeAnimation("Attack_Right", true);
	}
	else if (Dir == FVector2D::LEFT)
	{
		SpriteRenderer->ChangeAnimation("Attack_Left", true);
	}
	else if (Dir == FVector2D::UP)
	{
		SpriteRenderer->ChangeAnimation("Attack_Up", true);
	}
	else if (Dir == FVector2D::DOWN)
	{
		SpriteRenderer->ChangeAnimation("Attack_Down", true);
	}
	else
	{
		SpriteRenderer->ChangeAnimation("Attack_Down", true);
	}
}

void APlayer::Idle()
{
	FollowCamera();

	if (UEngineInput::GetInst().IsPress('A') == true
		|| UEngineInput::GetInst().IsPress('D') == true
		|| UEngineInput::GetInst().IsPress('W') == true
		|| UEngineInput::GetInst().IsPress('S') == true)
	{
		CurState = EPlayerState::Move;
	}

	if (UEngineInput::GetInst().IsPress(VK_LBUTTON) == true &&
		CurState != EPlayerState::Attack)
	{
		PlayAttackAnimation(CurDir);
		CurState = EPlayerState::Attack;
	}

}

void APlayer::Move(float DeltaTime)
{
	FollowCamera();

	if (UEngineInput::GetInst().IsPress('D') == true)
	{
		SpriteRenderer->ChangeAnimation("Run_Right");
		CurDir = FVector2D::RIGHT;
	}
	if (UEngineInput::GetInst().IsPress('A') == true)
	{
		SpriteRenderer->ChangeAnimation("Run_Left");
		CurDir = FVector2D::LEFT;
	}
	if (UEngineInput::GetInst().IsPress('S') == true)
	{
		SpriteRenderer->ChangeAnimation("Run_Down");
		CurDir = FVector2D::DOWN;
	}
	if (true == UEngineInput::GetInst().IsPress('W') == true)
	{
		SpriteRenderer->ChangeAnimation("Run_Up");
		CurDir = FVector2D::UP;
	}

	if (UEngineInput::GetInst().IsPress(VK_LBUTTON) == true &&
		CurState != EPlayerState::Attack)
	{
		PlayAttackAnimation(CurDir);
		CurState = EPlayerState::Attack;
	}

	AddActorLocation(CurDir * DeltaTime * Speed);

	if (false == UEngineInput::GetInst().IsPress('A') &&
		false == UEngineInput::GetInst().IsPress('D') &&
		false == UEngineInput::GetInst().IsPress('W') &&
		false == UEngineInput::GetInst().IsPress('S') &&
		false == UEngineInput::GetInst().IsPress(VK_LBUTTON) &&
		CurState == EPlayerState::Move &&
		CurState != EPlayerState::Attack)
	{

		SpriteRenderer->ChangeAnimation("Idle_Down");
		CurState = EPlayerState::Idle;
		CurDir = FVector2D::ZERO;
	}

	if (UEngineInput::GetInst().IsPress(VK_LBUTTON) == true &&
		CurState != EPlayerState::Attack)
	{
		PlayAttackAnimation(CurDir);
		CurState = EPlayerState::Attack;
	}
}

void APlayer::Attack()
{
	FollowCamera();
}

void APlayer::FollowCamera()
{
	if (CurRoom != nullptr)
	{
		for (int i = 0; i < CurRoom->GetLinkedRoomes().size(); i++)
		{
			UEngineDebug::CoreOutPutString("Link Room : " + CurRoom->GetLinkedRoomes()[i]->GetName());
		}

		FVector2D CameraMovePos = GetTransform().Location + GetWorld()->GetCameraPivot();

		if (CameraMovePos.iX() < CurRoom->LeftTopPos.iX())
		{
			CameraMovePos.X = CurRoom->LeftTopPos.X;
		}
		if (CameraMovePos.iY() < CurRoom->LeftTopPos.iY())
		{
			CameraMovePos.Y = CurRoom->LeftTopPos.Y;
		}
		if (CurRoom->RightBottomPos.iX() < CameraMovePos.iX() + UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().X)
		{
			CameraMovePos.X = CurRoom->RightBottomPos.X - UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().X;
		}
		if (CurRoom->RightBottomPos.iY() < CameraMovePos.iY() + UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Y)
		{
			CameraMovePos.Y = CurRoom->RightBottomPos.Y - UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Y;
		}

		GetWorld()->SetCameraPos(CameraMovePos);
	}
}

void APlayer::LevelChangeStart()
{
	Super::LevelChangeStart();
}

void APlayer::LevelChangeEnd()
{
	Super::LevelChangeEnd();
}