#include "PreCompile.h"
#include "UIBombManager.h"
#include "ContentsEnum.h"
#include "PlayerDataManager.h"

#include "UIText.h"

#include <EngineCore/SpriteRenderer.h>

AUIBombManager::AUIBombManager()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetSprite("BombBackground.png");
	FVector2D RupeeBGScale = Renderer->SetSpriteScale(1.0f);
	Renderer->SetComponentLocation(FVector2D::ZERO);
	Renderer->SetComponentScale(RupeeBGScale);
	Renderer->SetOrder(ERenderOrder::UI);
	Renderer->SetCameraEffect(false);
}

AUIBombManager::~AUIBombManager()
{
}

void AUIBombManager::BeginPlay()
{
	Super::BeginPlay();

	UIText = GetWorld()->SpawnActor<AHUDText>();
	UIText->SetActorLocation(GetActorLocation() + FVector2D(0.0f, 14.0f));
	UIText->InitText(FVector2D(24.0f, 0.0f), 2);
}

void AUIBombManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UIText->SetValue(PlayerDataManager::GetInstance().GetBomb());
}

