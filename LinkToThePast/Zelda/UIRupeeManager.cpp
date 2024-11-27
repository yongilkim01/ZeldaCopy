#include "PreCompile.h"
#include "UIRupeeManager.h"
#include "ContentsEnum.h"
#include "PlayerDataManager.h"

#include "UIText.h"

#include <EngineCore/SpriteRenderer.h>

AUIRupeeManager::AUIRupeeManager()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetSprite("RupeeBackground.png");
	FVector2D RupeeBGScale = Renderer->SetSpriteScale(1.0f);
	Renderer->SetComponentLocation(FVector2D::ZERO);
	Renderer->SetComponentScale(RupeeBGScale);
	Renderer->SetOrder(ERenderOrder::UI);
	Renderer->SetCameraEffect(false);
}

AUIRupeeManager::~AUIRupeeManager()
{
}

void AUIRupeeManager::BeginPlay()
{
	Super::BeginPlay();

	UIText = GetWorld()->SpawnActor<AHUDText>();
	UIText->SetActorLocation(GetActorLocation() + FVector2D(0.0f, 14.0f));
	UIText->InitText(FVector2D(24.0f, 0.0f), 3);
}

void AUIRupeeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UIText->SetValue(PlayerDataManager::GetInstance().GetRupee());
}

