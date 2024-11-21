#include "PreCompile.h"
#include "UIMagicBar.h"
#include "ContentsEnum.h"
#include "PlayerDataManager.h"

#include <EngineCore/SpriteRenderer.h>

AUIMagicBar::AUIMagicBar()
{
	// SpriteRenderer 컴포넌트 초기화
	{
		BackGroundRenderer = CreateDefaultSubObject<USpriteRenderer>();
		BackGroundRenderer->SetSprite("MagicBarBackground.png");
		BackGroundRenderer->SetSpriteScale(1.0f);
		BackGroundRenderer->SetOrder(ERenderOrder::UI);
		BackGroundRenderer->SetCameraEffect(false);


		GageRenderer = CreateDefaultSubObject<USpriteRenderer>();
		GageRenderer->SetSprite("MagicBarGage.png");
		GageRenderer->SetSpriteScale(1.0f);
		GageRenderer->SetOrder(ERenderOrder::UI_GAGE);
		GageRenderer->SetCameraEffect(false);
		GageRenderer->SetPivotType(PivotType::Bot);
		GageRenderer->SetComponentLocation(FVector2D(0.0f, 52.0f));

		FrameRenderer = CreateDefaultSubObject<USpriteRenderer>();
		FrameRenderer->SetSprite("MagicBarFrame.png");
		FrameRenderer->SetSpriteScale(1.0f);
		FrameRenderer->SetOrder(ERenderOrder::UI_FRAME);
		FrameRenderer->SetCameraEffect(false);
	}
}

AUIMagicBar::~AUIMagicBar()
{
}

void AUIMagicBar::BeginPlay()
{
	Super::BeginPlay();
}

void AUIMagicBar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float MagicGauge = static_cast<float>(PlayerDataManager::GetInstance().GetMagicGauge());

	GageRenderer->SetComponentScale(FVector2D(40.0f, MagicGauge));
}

