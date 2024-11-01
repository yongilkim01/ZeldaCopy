#include "PreCompile.h"
#include "Room.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"

ARoom::ARoom()
{
	USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
	SpriteRenderer->SetSprite("Dungeon1.png");

	FVector2D MapScale = SpriteRenderer->SetSpriteScale(3.0f);
	//FVector2D HalfScale = { MapScale.Half().X * -1, MapScale.Half().Y * -1 };
	SpriteRenderer->SetComponentLocation(MapScale.Half());
	SetActorLocation({ 0, 0 });
}

ARoom::~ARoom()
{
}

