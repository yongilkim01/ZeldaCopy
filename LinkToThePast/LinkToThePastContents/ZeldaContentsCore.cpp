#include "PreCompile.h"
#include "ZeldaContentsCore.h"
#include <EngineCore/EngineAPICore.h>

#include "PlayGameMode.h"
#include "Player.h"

ZeldaContentsCore::ZeldaContentsCore()
{
}

ZeldaContentsCore::~ZeldaContentsCore()
{
}

// ������ ����ǰ� �� 1�� ����ȴ�.
void ZeldaContentsCore::BeginPlay()
{
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");

	UEngineAPICore::GetCore()->OpenLevel("Play");
	// CreateLevel();

}

void ZeldaContentsCore::Tick()
{
}