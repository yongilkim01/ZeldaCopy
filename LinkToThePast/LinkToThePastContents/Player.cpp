#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineInput.h>
#include "Bullet.h"

APlayer::APlayer()
{
	// UEngineAPICore::GetCore()->CreateLevel("Title");
	SetActorLocation({ 100, 100 });
	SetActorScale({ 256, 256 });

	SetSprite("PlayerRunDown.png");
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();
	//UEngineInput::GetInst().BindAction('A', KeyEvent::Press, std::bind(&APlayer::MoveFunction, this, FVector2D::LEFT));
	//UEngineInput::GetInst().BindAction('D', KeyEvent::Press, std::bind(&APlayer::MoveFunction, this, FVector2D::RIGHT));
	//UEngineInput::GetInst().BindAction('S', KeyEvent::Press, std::bind(&APlayer::MoveFunction, this, FVector2D::DOWN));
	//UEngineInput::GetInst().BindAction('W', KeyEvent::Press, std::bind(&APlayer::MoveFunction, this, FVector2D::UP));
}

void APlayer::MoveFunction(FVector2D _Dir)
{
	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();

	AddActorLocation(_Dir * DeltaTime * Speed);
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (UEngineInput::GetInst().IsPress('D'))
	{
		AddActorLocation(FVector2D::RIGHT * _DeltaTime * Speed);
	}
	if (UEngineInput::GetInst().IsPress('A'))
	{
		AddActorLocation(FVector2D::LEFT * _DeltaTime * Speed);
	}
	if (UEngineInput::GetInst().IsPress('S'))
	{
		AddActorLocation(FVector2D::DOWN * _DeltaTime * Speed);
	}
	if (UEngineInput::GetInst().IsPress('W'))
	{
		AddActorLocation(FVector2D::UP * _DeltaTime * Speed);
	}

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		SetSprite("Player_Right.png", MySpriteIndex);
		++MySpriteIndex;
	}

}