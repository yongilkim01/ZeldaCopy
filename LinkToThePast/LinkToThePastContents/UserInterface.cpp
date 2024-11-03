#include "PreCompile.h"
#include "UserInterface.h"
#include "ContentsEnum.h"
#include "Player.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>

AUserInterface::AUserInterface()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetOrder(ERenderOrder::UI);
	SpriteRenderer->SetSprite("PlayerInfoUI.png");
	SpriteRenderer->SetSpriteScale(3.0f);

	SetActorLocation(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half());
}

AUserInterface::~AUserInterface()
{
}

void AUserInterface::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerCharacter != nullptr)
	{
		SetActorLocation(GetWorld()->GetCameraPos() - GetWorld()->GetCameraPivot());
	}
}
