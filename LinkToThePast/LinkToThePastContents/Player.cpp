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
	//SpriteRenderer->SetComponentScale({ 300, 300 });

	// SpriteRenderer->CreateAnimation("bomb", 0, 2, 0.1f);

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

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
	UEngineDebug::CoreOutPutString("PlayerPos : " + GetActorLocation().ToString());
	UEngineDebug::CoreOutPutString("PlayerScale : " + GetTransform().Scale.ToString());
	UEngineDebug::CoreOutPutString("PlayerLefTop : " + GetTransform().CenterLeftTop().ToString());

	if (CurRoom != nullptr)
	{
		UEngineDebug::CoreOutPutString(" ");
		UEngineDebug::CoreOutPutString("Room Posiiton : " + CurRoom->GetActorLocation().ToString());
		UEngineDebug::CoreOutPutString("Room LeftTop : " + CurRoom->LeftTopPos.ToString());
		UEngineDebug::CoreOutPutString("Room RightBottom : " + CurRoom->RightBottomPos.ToString());
		UEngineDebug::CoreOutPutString("Room Name : " + CurRoom->GetName());

		int LightTopPosX = GetActorLocation().iX() + GetWorld()->GetCameraPivot().iX();
		int LightTopPosY = GetActorLocation().iY() + GetWorld()->GetCameraPivot().iY();
		int RightBottomPosX = GetActorLocation().iX() - GetWorld()->GetCameraPivot().iX();
		int RightBottomPosY = GetActorLocation().iY() - GetWorld()->GetCameraPivot().iY();

		float MovePositionX = GetTransform().Location.X + GetWorld()->GetCameraPivot().X;
		float MovePositionY = GetTransform().Location.Y + GetWorld()->GetCameraPivot().Y;

		UEngineDebug::CoreOutPutString(" ");

		UEngineDebug::CoreOutPutString("Current Window X Posiiton : " + std::to_string(LightTopPosX));
		UEngineDebug::CoreOutPutString("CameraPos : " + GetWorld()->GetCameraPos().ToString());

		if (CurRoom->LeftTopPos.iX() > LightTopPosX)
		{
			MovePositionX = CurRoom->LeftTopPos.X;
		}
		else if (CurRoom->RightBottomPos.iX() < RightBottomPosX)
		{
			MovePositionX = CurRoom->RightBottomPos.X - UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().X;
		}

		if (CurRoom->LeftTopPos.iY() > LightTopPosY)
		{
			MovePositionY = CurRoom->LeftTopPos.Y;
		}
		else if (CurRoom->RightBottomPos.iY() < RightBottomPosY)
		{
			MovePositionY = CurRoom->RightBottomPos.Y - UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Y;
		}


		//if (CurRoom->RoomSize.iX() <= UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().iX()) MovePositionY = LightTopPosY;
		//if (CurRoom->RoomSize.iY() <= UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().iY()) MovePositionY = RightBottomPosY;

		GetWorld()->SetCameraPos({ MovePositionX , MovePositionY });

	}

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineDebug::SwitchIsDebug();
		UEngineAPICore::GetCore()->OpenLevel("Title");
		// UEngineDebug::SwitchIsDebug();
	}

	if (true == UEngineInput::GetInst().IsPress('D'))
	{
		SpriteRenderer->ChangeAnimation("Run_Right");
		AddActorLocation(FVector2D::RIGHT * _DeltaTime * Speed);
	}
	if (true == UEngineInput::GetInst().IsPress('A'))
	{
		SpriteRenderer->ChangeAnimation("Run_Left");
		AddActorLocation(FVector2D::LEFT * _DeltaTime * Speed);
	}
	if (true == UEngineInput::GetInst().IsPress('S'))
	{
		SpriteRenderer->ChangeAnimation("Run_Down");
		AddActorLocation(FVector2D::DOWN * _DeltaTime * Speed);
	}
	if (true == UEngineInput::GetInst().IsPress('W'))
	{
		SpriteRenderer->ChangeAnimation("Run_Up");
		AddActorLocation(FVector2D::UP * _DeltaTime * Speed);
	}

	if (false == UEngineInput::GetInst().IsPress('A') &&
		false == UEngineInput::GetInst().IsPress('D') &&
		false == UEngineInput::GetInst().IsPress('W') &&
		false == UEngineInput::GetInst().IsPress('S'))
	{
		SpriteRenderer->ChangeAnimation("Idle_Down");
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