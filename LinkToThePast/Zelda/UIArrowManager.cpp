#include "PreCompile.h"
#include "UIArrowManager.h"
#include "ContentsEnum.h"
#include "PlayerDataManager.h"

#include "HUDText.h"

#include <EngineCore/SpriteRenderer.h>

AUIArrowManager::AUIArrowManager()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetSprite("ArrowBackground.png");
	FVector2D RupeeBGScale = Renderer->SetSpriteScale(1.0f);
	Renderer->SetComponentLocation(FVector2D::ZERO);
	Renderer->SetComponentScale(RupeeBGScale);
	Renderer->SetOrder(ERenderOrder::UI);
	Renderer->SetCameraEffect(false);
}

AUIArrowManager::~AUIArrowManager()
{
}

void AUIArrowManager::BeginPlay()
{
	Super::BeginPlay();

	UIText = GetWorld()->SpawnActor<AHUDText>();
	UIText->SetActorLocation(GetActorLocation() + FVector2D(0.0f, 14.0f));
	UIText->InitText(FVector2D(24.0f, 0.0f), 2);
}

void AUIArrowManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UIText->SetValue(PlayerDataManager::GetInstance().GetArrow());
}

