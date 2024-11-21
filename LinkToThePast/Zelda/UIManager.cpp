#include "PreCompile.h"
#include "UIManager.h"
#include "ContentsEnum.h"

#include "UIMagicBar.h"
#include "UIHeartManager.h"
#include "UIRupeeManager.h"

#include "PlayerCharacter.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>

AUIManager::AUIManager()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetOrder(ERenderOrder::UI);
	SpriteRenderer->SetSprite("PlayerInfoUI.png");
	SpriteRenderer->SetSpriteScale(1.0f);

	SetActorLocation(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half());
}

AUIManager::~AUIManager()
{
}

void AUIManager::BeginPlay()
{
	Super::BeginPlay();

	{
		MagicBar = GetWorld()->SpawnActor<AUIMagicBar>();
		MagicBar->SetActorLocation(FVector2D(84, 117));
	}

	{
		HeartManager = GetWorld()->SpawnActor<AUIHeartManager>();
		HeartManager->SetActorLocation(FVector2D(602, 81));
	}
	{

		RupeeManager = GetWorld()->SpawnActor<AUIRupeeManager>();
		RupeeManager->SetActorLocation(FVector2D(229, 69));
	}
}

void AUIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerCharacter != nullptr)
	{
		SetActorLocation(GetWorld()->GetCameraLocation() - GetWorld()->GetCameraPivot());
	}
}
