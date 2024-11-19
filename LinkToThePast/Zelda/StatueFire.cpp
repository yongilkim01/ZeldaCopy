#include "PreCompile.h"
#include "StatueFire.h"
#include "ContentsEnum.h"
#include "Room.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>

AStatueFire::AStatueFire()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("FireStatue.png");
		FVector2D MapScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(MapScale.Half());
		SpriteRenderer->SetOrder(ERenderOrder::FIRST_FLOOR);
	}
}

AStatueFire::~AStatueFire()
{
}

void AStatueFire::BeginPlay()
{
	AStatue::BeginPlay();
	int FloorOrder = static_cast<int>(ERenderOrder::FIRST_FLOOR_OBJ);
	int Padding = GetActorLocation().iY() - GetCurRoom()->GetActorLocation().iY();
	Padding += 50;
	this->SpriteRenderer->SetOrder(FloorOrder + Padding);
}

void AStatueFire::Tick(float DeltaTime)
{
	AStatue::Tick(DeltaTime);
}

