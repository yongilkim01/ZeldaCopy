#include "PreCompile.h"
#include "StatueStone.h"
#include "ContentsEnum.h"
#include "Room.h"

#include <EngineCore/SpriteRenderer.h>

AStatueStone::AStatueStone()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("StoneStatue.png");
		FVector2D MapScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(MapScale.Half());
		SpriteRenderer->SetOrder(ERenderOrder::FIRST_FLOOR);
	}
}

AStatueStone::~AStatueStone()
{
}

void AStatueStone::BeginPlay()
{
	AStatue::BeginPlay();
	int FloorOrder = static_cast<int>(ERenderOrder::FIRST_FLOOR_OBJ);
	int Padding = GetActorLocation().iY() - GetCurRoom()->GetActorLocation().iY();
	Padding += 50;
	this->SpriteRenderer->SetOrder(FloorOrder + Padding);
}
                                                                
void AStatueStone::Tick(float DeltaTime)
{
	AStatue::Tick(DeltaTime);
}
