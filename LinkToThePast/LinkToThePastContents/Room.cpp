#include "PreCompile.h"
#include "Room.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"

ARoom::ARoom()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("Dungeon1.png");
}

ARoom::~ARoom()
{
}

void ARoom::SetRoomSprite(std::string_view SpriteName, ERenderOrder RenderOrder, FVector2D SpritePos, float SpriteScale /* = 3.0f */)
{
	SpriteRenderer->SetOrder(RenderOrder);
	SpriteRenderer->SetSprite(SpriteName);

	FVector2D MapScale = SpriteRenderer->SetSpriteScale(SpriteScale);
	SpriteRenderer->SetComponentLocation(MapScale.Half());
	SetActorLocation(SpritePos);
}

