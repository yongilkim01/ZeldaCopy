#include "PreCompile.h"
#include "UIItemBox.h"
#include "ContentsEnum.h"
#include "PlayerCharacter.h"
#include "PlayerDataManager.h"

#include <EngineCore/SpriteRenderer.h>

AUIItemBox::AUIItemBox()
{
	FrameRenderer = CreateDefaultSubObject<USpriteRenderer>();
	FrameRenderer->SetSprite("ItemBackground.png");
	FVector2D RupeeBGScale = FrameRenderer->SetSpriteScale(1.0f);
	FrameRenderer->SetComponentLocation(FVector2D::ZERO);
	FrameRenderer->SetComponentScale(RupeeBGScale);
	FrameRenderer->SetOrder(ERenderOrder::UI);
	FrameRenderer->SetCameraEffect(false);

	ItemRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ItemRenderer->SetSprite("UILantern.png");
	FVector2D ItemRenderScale = ItemRenderer->SetSpriteScale(1.0f);
	ItemRenderer->SetComponentLocation(FVector2D::ZERO);
	ItemRenderer->SetComponentScale(ItemRenderScale);
	int RenderOrder = static_cast<int>(ERenderOrder::UI) + 1;
	ItemRenderer->SetOrder(RenderOrder);
	ItemRenderer->SetCameraEffect(false);
}

AUIItemBox::~AUIItemBox()
{
}

void AUIItemBox::BeginPlay()
{
	Super::BeginPlay();

	Player = dynamic_cast<APlayerCharacter*>(GetWorld()->GetPawn());
	ItemRenderer->SetActive(false);

}

void AUIItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	int WeaponSelectIndex = PlayerDataManager::GetInstance().GetSelectWeapon();

	if (-1 != WeaponSelectIndex)
	{
		std::string SpriteName = Player->GetWeaponUISpriteByIndex(WeaponSelectIndex);
		ItemRenderer->SetSprite(SpriteName);
		ItemRenderer->SetActive(true);
	}
}

