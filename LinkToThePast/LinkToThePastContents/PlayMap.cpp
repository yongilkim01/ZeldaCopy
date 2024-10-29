#include "PreCompile.h"
#include "PlayMap.h"
#include <EngineCore/EngineAPICore.h>

APlayMap::APlayMap()
{
	//SetActorScale({ 1200, 800 });
	//SetActorLocation({ 600, 400 });

	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

	SetActorScale(WindowSize.Half());
	SetActorLocation(WindowSize.Half());
}

APlayMap::~APlayMap()
{
}

