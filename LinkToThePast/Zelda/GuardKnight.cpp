#include "PreCompile.h"
#include "GuardKnight.h"
#include "PlayerCharacter.h"
#include "ContentsEnum.h"
#include "UIBox.h"


#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/Collision2D.h>

AGuardKnight::AGuardKnight()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("GuardKnight.png", 0);
		SpriteRenderer->SetOrder(ERenderOrder::FIRST_FLOOR_OBJ);
		SpriteRenderer->SetSpriteScale(3.0f);
	}
	{
		EventCollison = CreateDefaultSubObject<UCollision2D>();
		EventCollison->SetComponentLocation({ 0, 0 });
		EventCollison->SetComponentScale({ 80, 80 });
		EventCollison->SetCollisionGroup(ECollisionGroup::EventTarget);
		EventCollison->SetCollisionType(ECollisionType::Rect);
		EventCollison->SetActive(true);
	}

	DebugOn();
}

AGuardKnight::~AGuardKnight()
{
}

void AGuardKnight::BeginPlay()
{
	Super::BeginPlay();

	ChangeState(EGuardState::IDLE);

}

void AGuardKnight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (CurState)
	{
	case EGuardState::IDLE:
		Idle(DeltaTime);
		break;
	case EGuardState::EVENT:
		Event(DeltaTime);
		break;
	default:
		break;
	}

}

void AGuardKnight::StartIdle()
{
}

void AGuardKnight::Idle(float DeltaTime)
{
	Player = dynamic_cast<APlayerCharacter*>(EventCollison->CollisionOnce(ECollisionGroup::PlayerBody));

	if (nullptr != Player)
	{
		ChangeState(EGuardState::EVENT);
	}
}

void AGuardKnight::StartEvent()
{
	EventCollison->SetActive(false);

	UIBox = GetWorld()->SpawnActor<AUIBox>();
	UIBox->SetActorLocation(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half() + FVector2D(10.0f, 200.0f));

	std::vector<std::string> StrValues;
	StrValues.push_back("Hey hey! You are not allowed in");
	StrValues.push_back("the castle, son!");
	StrValues.push_back("Go home and get some sleep!");

	UIBox->CreateUIText(StrValues, 0.5f);

	CurTime = 0.0f;
}

void AGuardKnight::Event(float DeltaTime)
{
	CurTime += DeltaTime;

	if (CurTime > 3.0f)
	{
		UIBox->ResetText();
		ChangeState(EGuardState::IDLE);
	}
}

void AGuardKnight::ChangeState(EGuardState State)
{
	if (State == CurState) return;

	switch (State)
	{
	case EGuardState::IDLE:
		StartIdle();
		break;
	case EGuardState::EVENT:
		StartEvent();
		break;
	default:
		break;
	}
	
	CurState = State;
}
