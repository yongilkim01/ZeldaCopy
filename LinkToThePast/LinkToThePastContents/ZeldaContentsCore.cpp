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

// 엔진이 실행되고 단 1번 실행된다.
void ZeldaContentsCore::BeginPlay()
{
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("A Link to the past");

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 1280, 720 });

	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");

	UEngineAPICore::GetCore()->OpenLevel("Play");
	// CreateLevel();

}

void ZeldaContentsCore::Tick()
{
}