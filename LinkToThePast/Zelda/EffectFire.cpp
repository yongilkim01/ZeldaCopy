#include "PreCompile.h"
#include "EffectFire.h"
#include "ContentsEnum.h"

#include <EngineCore/SpriteRenderer.h>

AEffectFire::AEffectFire()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("FireEffect.png");
		SpriteRenderer->SetComponentScale(FVector2D(1.0f, 1.0f));
		SpriteRenderer->SetOrder(ERenderOrder::UI);
		SpriteRenderer->SetSpriteScale(1.0f);

		SpriteRenderer->CreateAnimation("Fire", "FireEffect.png", 0, 3, 0.08f);
		SpriteRenderer->SetAnimationEvent("Fire", 3, [this]()
			{
				Destroy();
			});

		SpriteRenderer->ChangeAnimation("Fire");
	}
}

AEffectFire::~AEffectFire()
{
}

void AEffectFire::BeginPlay()
{
	Super::BeginPlay();
}

void AEffectFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}