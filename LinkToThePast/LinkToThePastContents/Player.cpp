#include "PreCompile.h"
#include "Player.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>

#include <EnginePlatform/EngineInput.h>
#include "Bullet.h"

void APlayer::RunSoundPlay()
{

}

APlayer::APlayer()
{
	// UEngineAPICore::GetCore()->CreateLevel("Title");
	SetActorLocation({ 100, 100 });

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("LinkMoveDown.png");
	SpriteRenderer->SetSpriteScale(3.0f);
	//SpriteRenderer->SetComponentScale({ 300, 300 });

	// SpriteRenderer->CreateAnimation("bomb", 0, 2, 0.1f);

	SpriteRenderer->CreateAnimation("Run_Right", "LinkMoveDown.png", 1, 9, 0.1f);
	SpriteRenderer->CreateAnimation("Run_Left", "LinkMoveLeft.png", 1, 9, 0.1f);
	SpriteRenderer->CreateAnimation("Run_Up", "LinkMoveUp.png", 1, 9, 0.1f);
	SpriteRenderer->CreateAnimation("Run_Down", "LinkMoveRight.png", 1, 9, 0.1f);

	SpriteRenderer->CreateAnimation("Idle_Right", "LinkMoveDown.png", 0, 0, 0.1f);
	SpriteRenderer->CreateAnimation("Idle_Left", "LinkMoveDown.png", 0, 0, 0.1f);
	SpriteRenderer->CreateAnimation("Idle_Up", "LinkMoveDown.png", 0, 0, 0.1f);
	SpriteRenderer->CreateAnimation("Idle_Down", "LinkMoveDown.png", 0, 0, 0.1f);

	SpriteRenderer->ChangeAnimation("Idle_Down");

	// SpriteRenderer->CreateAnimation("Test", "Player_Right.png", { 5,  4,  3}, 0.1f);
	//SpriteRenderer->SetAnimationEvent("Run_Right", 2, std::bind(&APlayer::RunSoundPlay, this));
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	// 직접 카메라 피봇을 설정해줘야 한다.
	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	GetWorld()->SetCameraPivot(Size.Half() * -1.0f);
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
		SpriteRenderer->ChangeAnimation("Run_Right");
		AddActorLocation(FVector2D::LEFT * _DeltaTime * Speed);
	}
	if (true == UEngineInput::GetInst().IsPress('S'))
	{
		SpriteRenderer->ChangeAnimation("Run_Right");
		AddActorLocation(FVector2D::DOWN * _DeltaTime * Speed);
	}
	if (true == UEngineInput::GetInst().IsPress('W'))
	{
		SpriteRenderer->ChangeAnimation("Run_Right");
		AddActorLocation(FVector2D::UP * _DeltaTime * Speed);
	}

	if (false == UEngineInput::GetInst().IsPress('A') &&
		false == UEngineInput::GetInst().IsPress('D') &&
		false == UEngineInput::GetInst().IsPress('W') &&
		false == UEngineInput::GetInst().IsPress('S'))
	{
		SpriteRenderer->ChangeAnimation("Idle_Right");
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