#include "PreCompile.h"
#include "LevelMove.h"
#include "ContentsEnum.h"
#include "Fade.h"
#include "PlayerCharacter.h"
#include "CastleUnderWaterGameMode.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision2D.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/EngineAPICore.h>

ALevelMove::ALevelMove()
{
	// 스프라이트 컴포넌트 생성
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::FADE);
		SpriteRenderer->SetSprite("DefaultSprite.png");
		FVector2D SpriteScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(SpriteScale.Half());
		SpriteRenderer->SetCameraEffect(false);
		SpriteRenderer->SetAlphafloat(0.0f);
	}
	// 충돌 컴포넌트 생성
	{		
		Collision = CreateDefaultSubObject<UCollision2D>();
		Collision->SetComponentLocation({ 0, -10 });
		Collision->SetComponentScale({ 10, 10 });
		Collision->SetCollisionGroup(ECollisionGroup::Potal);
		Collision->SetActive(true);
	}

	DebugOn();
}

ALevelMove::~ALevelMove()
{
}

void ALevelMove::BeginPlay()
{
	Super::BeginPlay();

	Player = dynamic_cast<APlayerCharacter*>(GetWorld()->GetPawn());

	FadeActor = GetWorld()->SpawnActor<AFade>();
	FadeActor->SetActorLocation(Player->GetActorLocation());
	FadeActor->SetFadeSize(EFadeSize::BIG);
	FadeActor->SetFadeOn(false);
	//FadeActor->FadeOut();
}

void ALevelMove::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FadeActor->SetActorLocation(Player->GetActorLocation());

	AActor* Result = Collision->CollisionOnce(ECollisionGroup::PLAYERMOVEABLE);

	if (nullptr != Result)
	{
		if (MoveLevel == "UnderWater")
		{
			Player->ChangeState(EPlayerState::Fall);
			Player->SetActorLocation(GetActorLocation());

			TimeEventer.PushEvent(1.5f, [this]()
				{
					//FadeActor->FadeIn();
					UEngineAPICore::GetCore()->ResetLevel<ACastleUnderWaterGameMode, APlayerCharacter>("UnderWater");
					UEngineAPICore::GetCore()->OpenLevel(MoveLevel);
				}
			);
		}
		else
		{
			UEngineDebug::CoreOutPutString("플레이어 안에 들어옴");
			//FadeActor->FadeIn();
			TimeEventer.PushEvent(1.0f, [this]()
				{
					UEngineAPICore::GetCore()->OpenLevel(MoveLevel);
				}
			);
		}
		Collision->SetActive(false);
	}
}