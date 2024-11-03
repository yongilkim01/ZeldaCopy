#include "PreCompile.h"
#include "Player.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>

#include <EnginePlatform/EngineInput.h>
#include "Room.h"

APlayer* APlayer::StaticPlayer = nullptr;

void APlayer::RunSoundPlay()
{

}

APlayer::APlayer()
{
	// UEngineAPICore::GetCore()->CreateLevel("Title");
	//SetActorLocation({ 1600, 2200 });
	//SetActorLocation({ 390, 427 });
	SetActorLocation({ 280, 200 });
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

	SpriteRenderer->ChangeAnimation("Idle_Down");

	StaticPlayer = this;
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

	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / DeltaTime));
	UEngineDebug::CoreOutPutString("PlayerPos : " + GetActorLocation().ToString());
	UEngineDebug::CoreOutPutString("PlayerScale : " + GetTransform().Scale.ToString());
	UEngineDebug::CoreOutPutString("PlayerLefTop : " + GetTransform().CenterLeftTop().ToString());

	// 카메라 위치 이동 코드
	if (CurRoom != nullptr)
	{
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

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineDebug::SwitchIsDebug();
		UEngineAPICore::GetCore()->OpenLevel("Title");
	}

	FVector2D CurDir = FVector2D::ZERO;

	// TODO: 콜리전 체크
	if (false)
	{

	}
	else
	{
		if (true == UEngineInput::GetInst().IsPress('D'))
		{
			SpriteRenderer->ChangeAnimation("Run_Right");
			CurDir = FVector2D::RIGHT;
		}
		if (true == UEngineInput::GetInst().IsPress('A'))
		{
			SpriteRenderer->ChangeAnimation("Run_Left");
			CurDir = FVector2D::LEFT;
		}
		if (true == UEngineInput::GetInst().IsPress('S'))
		{
			SpriteRenderer->ChangeAnimation("Run_Down");
			CurDir = FVector2D::DOWN;
		}
		if (true == UEngineInput::GetInst().IsPress('W'))
		{
			SpriteRenderer->ChangeAnimation("Run_Up");
			CurDir = FVector2D::UP;
		}
		if (false == UEngineInput::GetInst().IsPress('A') &&
			false == UEngineInput::GetInst().IsPress('D') &&
			false == UEngineInput::GetInst().IsPress('W') &&
			false == UEngineInput::GetInst().IsPress('S'))
		{
			SpriteRenderer->ChangeAnimation("Idle_Down");
		}
	}
	AddActorLocation(CurDir * DeltaTime * Speed);

}

void APlayer::LevelChangeStart()
{
	Super::LevelChangeStart();
}
void APlayer::LevelChangeEnd()
{
	Super::LevelChangeEnd();
}