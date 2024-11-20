#include "PreCompile.h"
#include "Pot.h"

#include "ContentsEnum.h"
#include "BaseCharacter.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision2D.h>
#include <EngineCore/EngineCoreDebug.h>

APot::APot()
{
	// ��������Ʈ ������Ʈ ����
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Pot.png");
		SpriteRenderer->SetSpriteScale(1.0f);

	}
	{
		// �浹 ������Ʈ ����
		Collision = CreateDefaultSubObject<UCollision2D>();
		Collision->SetComponentLocation({ 0, 0 });
		Collision->SetComponentScale({ 30, 30 });
		Collision->SetCollisionGroup(ECollisionGroup::EventTarget);
		Collision->SetActive(true);

	}

	//DebugOn();
}

APot::~APot()
{
}

void APot::BeginPlay()
{
	AEventActor::BeginPlay();
}

void APot::Tick(float DeltaTime)
{
	AEventActor::Tick(DeltaTime);
}

void APot::Interact(ABaseCharacter* Character)
{
	UEngineDebug::CoreOutPutString("�÷��̾� �� �ǵ���");
	std::string CharacterName = Character->GetName();
}

