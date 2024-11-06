#include "PreCompile.h"
#include "Player.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>

#include <EnginePlatform/EngineInput.h>
#include "Room.h"
#include "RoomMove.h"
#include "RoomManageMode.h"

void APlayer::RunSoundPlay()
{

}


APlayer::APlayer()
{
	SetActorLocation({ 380, 340 });
	Speed = 250.0f;
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("LinkMoveDown.png");
	SpriteRenderer->SetSpriteScale(3.0f);

	SpriteRenderer->CreateAnimation("Run_Right", "LinkMoveRight.png", 1, 8, 0.04f);
	SpriteRenderer->CreateAnimation("Run_Left", "LinkMoveLeft.png", 1, 8, 0.04f);
	SpriteRenderer->CreateAnimation("Run_Up", "LinkMoveUp.png", 1, 8, 0.04f);
	SpriteRenderer->CreateAnimation("Run_Down", "LinkMoveDown.png", 1, 8, 0.04f);

	SpriteRenderer->CreateAnimation("Idle_Right", "LinkMoveRight.png", 0, 0, 0.1f);
	SpriteRenderer->CreateAnimation("Idle_Left", "LinkMoveLeft.png", 0, 0, 0.1f);
	SpriteRenderer->CreateAnimation("Idle_Up", "LinkMoveUp.png", 0, 0, 0.1f);
	SpriteRenderer->CreateAnimation("Idle_Down", "LinkMoveDown.png", 0, 0, 0.1f);

	SpriteRenderer->CreateAnimation("Attack_Right", "LinkAttackRight.png", 0, 5, 0.04f, false);
	SpriteRenderer->CreateAnimation("Attack_Left", "LinkAttackLeft.png", 0, 5, 0.04f, false);
	SpriteRenderer->CreateAnimation("Attack_Up", "LinkAttackUp.png", 0, 4, 0.04f, false);
	SpriteRenderer->CreateAnimation("Attack_Down", "LinkAttackDown.png", 0, 5, 0.04f, false);

	SpriteRenderer->SetAnimationEvent("Attack_Right", 5, std::bind(&APlayer::IdleStart, this));
	SpriteRenderer->SetAnimationEvent("Attack_Left", 5, std::bind(&APlayer::IdleStart, this));
	SpriteRenderer->SetAnimationEvent("Attack_Up", 4, std::bind(&APlayer::IdleStart, this));
	SpriteRenderer->SetAnimationEvent("Attack_Down", 5, std::bind(&APlayer::IdleStart, this));


	CurDir = FVector2D::DOWN;

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
	SetCollisionImage("Dungeon1Collision.png");

	ChangeState(EPlayerState::Idle);
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
	case EPlayerState::Idle:
		Idle(DeltaTime);
		break;
	case EPlayerState::Move:
		Move(DeltaTime);
		break;
	case EPlayerState::Attack:
		Attack(DeltaTime);
		break;
	default:
		break;
	}
}

void APlayer::SetCollisionImage(std::string_view CollisionImageName)
{
	CollisionImage = UImageManager::GetInst().FindImage(CollisionImageName);
}

void APlayer::PrintDebugPlayerState()
{
	switch (CurState)
	{
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

void APlayer::ChangeState(EPlayerState ChangeState)
{
	switch (ChangeState)
	{
	case EPlayerState::Idle:
		IdleStart();
		break;
	case EPlayerState::Move:
		MoveStart();
		break;
	case EPlayerState::Attack:
		AttackStart();
		break;
	default:
		break;
	}

	CurState = ChangeState;
}

void APlayer::IdleStart()
{
	if (CurDir == FVector2D::RIGHT)
	{
		SpriteRenderer->ChangeAnimation("Idle_Right");
	}
	else if (CurDir == FVector2D::LEFT)
	{
		SpriteRenderer->ChangeAnimation("Idle_Left");
	}
	else if (CurDir == FVector2D::UP)
	{
		SpriteRenderer->ChangeAnimation("Idle_Up");
	}
	else if (CurDir == FVector2D::DOWN)
	{
		SpriteRenderer->ChangeAnimation("Idle_Down");
	}
	else
	{
		MSGASSERT("플레이어의 방향이 초기화 되지 않았습니다!");
		return;
	}

	CurState = EPlayerState::Idle;
}

void APlayer::MoveStart()
{
	if (CurDir == FVector2D::RIGHT)
	{
		SpriteRenderer->ChangeAnimation("Run_Right");
	}
	else if (CurDir == FVector2D::LEFT)
	{
		SpriteRenderer->ChangeAnimation("Run_Left");
	}
	else if (CurDir == FVector2D::UP)
	{
		SpriteRenderer->ChangeAnimation("Run_Up");
	}
	else if (CurDir == FVector2D::DOWN)
	{
		SpriteRenderer->ChangeAnimation("Run_Down");
	}
	else
	{
		MSGASSERT("플레이어의 방향이 초기화 되지 않았습니다!");
		return;
	}

	CurState = EPlayerState::Move;
}

void APlayer::AttackStart()
{
	if (CurDir == FVector2D::RIGHT)
	{
		SpriteRenderer->ChangeAnimation("Attack_Right", true);
	}
	else if (CurDir == FVector2D::LEFT)
	{
		SpriteRenderer->ChangeAnimation("Attack_Left", true);
	}
	else if (CurDir == FVector2D::UP)
	{
		SpriteRenderer->ChangeAnimation("Attack_Up", true);
	}
	else if (CurDir == FVector2D::DOWN)
	{
		SpriteRenderer->ChangeAnimation("Attack_Down", true);
	}
	else
	{
		MSGASSERT("플레이어의 방향이 초기화 되지 않았습니다!");
		return;
	}

	CurState = EPlayerState::Attack;
}

void APlayer::Idle(float DeltaTime)
{
	FollowCamera();

	if (UEngineInput::GetInst().IsPress('A') == true)
	{
		CurDir = FVector2D::LEFT;
		ChangeState(EPlayerState::Move);
		return;
	}
	else if (UEngineInput::GetInst().IsPress('D') == true)
	{
		CurDir = FVector2D::RIGHT;
		ChangeState(EPlayerState::Move);
		return;
	}
	else if (UEngineInput::GetInst().IsPress('W') == true)
	{
		CurDir = FVector2D::UP;
		ChangeState(EPlayerState::Move);
		return;
	}
	else if (UEngineInput::GetInst().IsPress('S') == true)
	{
		CurDir = FVector2D::DOWN;
		ChangeState(EPlayerState::Move);
		return;
	}


	if (UEngineInput::GetInst().IsPress(VK_LBUTTON) == true &&
		CurState != EPlayerState::Attack)
	{
		AttackStart();
		CurState = EPlayerState::Attack;
	}
}

void APlayer::Move(float DeltaTime)
{
	FollowCamera();

	if (UEngineInput::GetInst().IsPress('D') == true
		&& MoveDir != FVector2D::RIGHT)
	{
		CurDir = FVector2D::RIGHT;
		MoveDir += FVector2D::RIGHT;
		//SpriteRenderer->ChangeAnimation("Run_Right");
	}
	if (UEngineInput::GetInst().IsPress('A') == true
		&& MoveDir != FVector2D::LEFT)
	{
		CurDir = FVector2D::LEFT;
		MoveDir += FVector2D::LEFT;
		//SpriteRenderer->ChangeAnimation("Run_Left");
	}

	if (UEngineInput::GetInst().IsPress('S') == true
		&& MoveDir != FVector2D::DOWN)
	{
		CurDir = FVector2D::DOWN;
		MoveDir += FVector2D::DOWN;
		//SpriteRenderer->ChangeAnimation("Run_Down");
	}
	if (UEngineInput::GetInst().IsPress('W') == true
		&& MoveDir != FVector2D::UP)
	{
		CurDir = FVector2D::UP;
		MoveDir += FVector2D::UP;
		//SpriteRenderer->ChangeAnimation("Run_Up");
	}


	MoveDir.Normal();

	if (CollisionImage != nullptr)
	{
		// 픽셀충돌에서 제일 중요한건 애초에 박히지 않는것이다.
		FVector2D NextPos = GetActorLocation() + MoveDir * DeltaTime * Speed;
		UColor Color = CollisionImage->GetColor(NextPos, UColor::PINK);
		if (Color == UColor::WHITE)
		{
			AddActorLocation(MoveDir * DeltaTime * Speed);
		} 
		else if (Color == UColor::ORANGE)
		{
			AddActorLocation(MoveDir * DeltaTime * (Speed * 0.5f));
		}
	}
	//AddActorLocation(MoveDir * DeltaTime * Speed);

	MoveDir = FVector2D::ZERO;

	if (false == UEngineInput::GetInst().IsPress('A') &&
		false == UEngineInput::GetInst().IsPress('D') &&
		false == UEngineInput::GetInst().IsPress('W') &&
		false == UEngineInput::GetInst().IsPress('S'))
	{

		ChangeState(EPlayerState::Idle);
	}

	if (UEngineInput::GetInst().IsPress(VK_LBUTTON) == true &&
		CurState != EPlayerState::Attack)
	{
		AttackStart();
		CurState = EPlayerState::Attack;
	}
}

void APlayer::Attack(float DeltaTime)
{
	FollowCamera();
}


void APlayer::FollowCamera()
{
	if (CurRoom != nullptr)
	{
		for (int i = 0; i < CurRoom->GetRoomMovesSize(); i++)
		{
			URoomMove* RoomMove = CurRoom->FindRoomMove(i);
			ARoom* TestRoom1 = RoomMove->GetCurRoom();
			ARoom* TestRoom2 = RoomMove->GetMoveRoom();
			if (RoomMove->GetMoveRoom() == nullptr || RoomMove->GetCurRoom() == nullptr) continue;
			UEngineDebug::CoreOutPutString("Link Room : " + RoomMove->GetMoveRoom()->GetName());
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