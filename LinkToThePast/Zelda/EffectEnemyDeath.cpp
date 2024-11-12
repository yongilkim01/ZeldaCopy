#include "PreCompile.h"
#include "EffectEnemyDeath.h"

#include <EngineCore/SpriteRenderer.h>

AEffectEnemyDeath::AEffectEnemyDeath()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("EnemyDeathEffect.png");
		SpriteRenderer->SetComponentScale(FVector2D(1.0f, 1.0f));
		SpriteRenderer->SetSpriteScale(3.0f);

		SpriteRenderer->CreateAnimation("Enemy_Death", "EnemyDeathEffect.png", 0, 6, 0.2f);

		SpriteRenderer->SetAnimationEvent("Enemy_Death", 6, std::bind(&AEffectEnemyDeath::EndEffect, this));

		SpriteRenderer->ChangeAnimation("Enemy_Death");
	}
}

AEffectEnemyDeath::~AEffectEnemyDeath()
{
}

void AEffectEnemyDeath::BeginPlay()
{
	Super::BeginPlay();
}

void AEffectEnemyDeath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEffectEnemyDeath::EndEffect()
{
	this->Destroy();
	this->GetOwnerActor()->Destroy();
}