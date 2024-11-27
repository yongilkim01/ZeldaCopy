#include "PreCompile.h"
#include "UIKeyManager.h"
#include "ContentsEnum.h"
#include "PlayerDataManager.h"

#include "UIText.h"

#include <EngineCore/SpriteRenderer.h>

AUIKeyManager::AUIKeyManager()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetSprite("KeyBackground.png");
	FVector2D RupeeBGScale = Renderer->SetSpriteScale(1.0f);
	Renderer->SetComponentLocation(FVector2D::ZERO);
	Renderer->SetComponentScale(RupeeBGScale);
	Renderer->SetOrder(ERenderOrder::UI);
	Renderer->SetCameraEffect(false);
}

AUIKeyManager::~AUIKeyManager()
{
}

void AUIKeyManager::BeginPlay()
{
	Super::BeginPlay();

	UIText = GetWorld()->SpawnActor<AHUDText>();
	UIText->SetActorLocation(GetActorLocation() + FVector2D(0.0f, 14.0f));
	UIText->InitText(FVector2D(24.0f, 0.0f), 1);
}

void AUIKeyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UIText->SetValue(PlayerDataManager::GetInstance().GetKey());
}

