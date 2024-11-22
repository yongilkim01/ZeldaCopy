#include "PreCompile.h"
#include "UIHeartManager.h"
#include "ContentsEnum.h"
#include "PlayerDataManager.h"

#include <EngineCore/Collision2D.h>
#include <EngineCore/SpriteRenderer.h>

AUIHeartManager::AUIHeartManager()
{
	HeartSprites.reserve(MAX_HEART_COUNT);

	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetSprite("LifeBackground.png");
	FVector2D MainSpriteScale = Renderer->SetSpriteScale(1.0f);
	Renderer->SetComponentLocation(FVector2D::ZERO);
	Renderer->SetComponentScale(MainSpriteScale);
	Renderer->SetOrder(ERenderOrder::UI);
	Renderer->SetCameraEffect(false);
	// Renderer->TestDebugCheckOn();

	FVector2D HeartLocation = { -108, 1 };
	int MaxHP = PlayerDataManager::GetInstance().GetMaxHP();

	for (size_t i = 1; i <= MAX_HEART_COUNT; i++)
	{
		if (0 == i % 2)
		{
			if (MaxHP >= i)
			{
				USpriteRenderer* EmptySprite = CreateDefaultSubObject<USpriteRenderer>();
				EmptySprite->SetSprite("Heart.png", 2);

				FVector2D EmptyScale = EmptySprite->SetSpriteScale(1.0f);
				EmptySprite->SetComponentScale(EmptyScale);
				EmptySprite->SetComponentLocation(HeartLocation);
				EmptySprite->SetOrder(ERenderOrder::UI);
				EmptySprite->SetCameraEffect(false);
			}
		}

		USpriteRenderer* HeartSprite = CreateDefaultSubObject<USpriteRenderer>();
		int TestNum = i % 2;
		HeartSprite->SetSprite("Heart.png", i % 2);

		//HeartSprite->ChangeAnimation("FullHeart");

		FVector2D SpriteScale = HeartSprite->SetSpriteScale(1.0f);
		HeartSprite->SetComponentScale(SpriteScale);
		HeartSprite->SetComponentLocation(HeartLocation);
		int RenderOrder = static_cast<int>(ERenderOrder::UI_FRAME) - i % 2;
		HeartSprite->SetOrder(RenderOrder);
		HeartSprite->SetCameraEffect(false);
		HeartSprite->SetActive(false);
		HeartSprites.push_back(HeartSprite);

		if (0 == i % 2)
		{
			HeartLocation += FVector2D(24.0f, 0.0f);
			if (HeartSprites.size() == 20)
			{
				HeartLocation = FVector2D(-108.0f, 25.0f);
			}
		}
	}
}

AUIHeartManager::~AUIHeartManager()
{
}

void AUIHeartManager::BeginPlay()
{
	Super::BeginPlay();

	int MaxHP = PlayerDataManager::GetInstance().GetMaxHP();

	for (int i = 0; i < 1; i++)
	{
		HeartSprites[i]->SetActive(true);
	}
	//PlayerDataManager::GetInstance().AddHP(-2);
	
}

void AUIHeartManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	int CurrentHP = PlayerDataManager::GetInstance().GetHP();

	for (int i = 0; i < MAX_HEART_COUNT; i++)
	{
		HeartSprites[i]->SetActive(false);
	}

	for (int i = 0; i < CurrentHP; i++)
	{
		HeartSprites[i]->SetActive(true);
	}
	
}

