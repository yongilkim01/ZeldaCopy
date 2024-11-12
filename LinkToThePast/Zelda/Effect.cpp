#include "PreCompile.h"
#include "Effect.h"
#include "EngineCore/SpriteRenderer.h"

AEffect::AEffect()
{
}

AEffect::~AEffect()
{
}

bool AEffect::GetAnimationIsEnd()
{
	return this->SpriteRenderer->IsCurAnimationEnd();
}

