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
		//UEngineDebug::CoreOutPutString(" ");
		//UEngineDebug::CoreOutPutString("Room Posiiton : " + CurRoom->GetActorLocation().ToString());
		//UEngineDebug::CoreOutPutString("Room LeftTop : " + CurRoom->LeftTopPos.ToString());
		//UEngineDebug::CoreOutPutString("Room RightBottom : " + CurRoom->RightBottomPos.ToString());
		//UEngineDebug::CoreOutPutString("Room Name : " + CurRoom->GetName());
		//UEngineDebug::CoreOutPutString("Room Size : " + CurRoom->RoomSize.ToString());

		//int LightTopPosX = GetActorLocation().iX() + GetWorld()->GetCameraPivot().iX();
		//int LightTopPosY = GetActorLocation().iY() + GetWorld()->GetCameraPivot().iY();
		//int RightBottomPosX = GetActorLocation().iX() - GetWorld()->GetCameraPivot().iX();
		//int RightBottomPosY = GetActorLocation().iY() - GetWorld()->GetCameraPivot().iY();

		//float MovePositionX = GetTransform().Location.X + GetWorld()->GetCameraPivot().X;
		//float MovePositionY = GetTransform().Location.Y + GetWorld()->GetCameraPivot().Y;
		//float PrevPositionY = MovePositionY;

		//UEngineDebug::CoreOutPutString(" ");

		//UEngineDebug::CoreOutPutString("Current Window X Posiiton : " + std::to_string(LightTopPosX));
		//UEngineDebug::CoreOutPutString("CameraPos : " + GetWorld()->GetCameraPos().ToString());

		//if (CurRoom->LeftTopPos.iX() > LightTopPosX)
		//{
		//	MovePositionX = CurRoom->LeftTopPos.X;
		//}
		//if (CurRoom->RightBottomPos.iX() < RightBottomPosX)
		//{
		//	MovePositionX = CurRoom->RightBottomPos.X - UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().X;
		//}

		//UEngineDebug::CoreOutPutString(" ");
		//UEngineDebug::CoreOutPutString(" ");
		//UEngineDebug::CoreOutPutString("CurRoom LeftTop : " + CurRoom->LeftTopPos.ToString());
		//UEngineDebug::CoreOutPutString("CurRoom RightBottom : " + CurRoom->RightBottomPos.ToString());
		//UEngineDebug::CoreOutPutString("Window Size : " + UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().ToString());
		//int Num1 = CurRoom->RightBottomPos.Y;
		//int Num2 = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Y;

		//bool Case1 = false;
		//bool Case2 = false;

		//if (CurRoom->LeftTopPos.iY() > LightTopPosY)
		//{
		//	MovePositionY = CurRoom->LeftTopPos.Y;
		//	Case1 = true;
		//}
		//if (CurRoom->RightBottomPos.iY() < RightBottomPosY)
		//{
		//	MovePositionY = CurRoom->RightBottomPos.Y - UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Y;
		//	UEngineDebug::CoreOutPutString("Move Position : " + std::to_string(MovePositionY));
		//	Case2 = true;
		//}

		//if (static_cast<int>(MovePositionY) == 1428)
		//{
		//	int a = 0;
		//}

		//GetWorld()->SetCameraPos({ MovePositionX , MovePositionY });

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