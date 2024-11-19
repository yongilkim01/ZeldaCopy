#include "PreCompile.h"
#include "LevelMove.h"
#include "ContentsEnum.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision2D.h>
#include <EngineCore/EngineCoreDebug.h>

ALevelMove::ALevelMove()
{
	// ��������Ʈ ������Ʈ ����
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::FADE);
		SpriteRenderer->SetSprite("DefaultSprite.png");
		FVector2D SpriteScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(SpriteScale.Half());
		SpriteRenderer->SetCameraEffect(false);
		SpriteRenderer->SetAlphafloat(0.0f);
	}
	{
		// �浹 ������Ʈ ����
		Collision = CreateDefaultSubObject<UCollision2D>();
		Collision->SetComponentLocation({ 0, 0 });
		Collision->SetComponentScale({ 50, 50 });
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
}

void ALevelMove::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AActor* Result = Collision->CollisionOnce(ECollisionGroup::PlayerBody);

	if (nullptr != Result)
	{
		UEngineDebug::CoreOutPutString("�÷��̾� �ȿ� ����");
	}
}

