#include "PreCompile.h"
#include "TitleLogo.h"

#include <EngineCore/SpriteRenderer.h>

TitleLogo::TitleLogo()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("TitleScreen.png");
	SpriteRenderer->SetSpriteScale(3.0f);

	SetActorLocation({ 384, 336 });
}

TitleLogo::~TitleLogo()
{
}

