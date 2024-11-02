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
	SetActorLocation({ 1600, 2200 });
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

	if (CurRoom == nullptr)
	{
		//SetCamera
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