#include "PreCompile.h"
#include "HouseBed.h"
#include "ContentsEnum.h"

#include <EngineCore/SpriteRenderer.h>

AHouseBed::AHouseBed()
{
	// 스프라이트 렌더러 컴포넌트 초기화
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("LinkBed.png", 0);
		FVector2D Location = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(FVector2D::ZERO);
		SpriteRenderer->SetOrder(ERenderOrder::FIRST_FLOOR_OBJ);
		SpriteRenderer->SetActive(true);
	}
}

AHouseBed::~AHouseBed()
{
}

void AHouseBed::BeginPlay()
{
	Super::BeginPlay();

}

void AHouseBed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}