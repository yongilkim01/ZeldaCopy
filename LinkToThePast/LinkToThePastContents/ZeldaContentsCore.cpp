#include "PreCompile.h"
#include "ZeldaContentsCore.h"
#include <EngineCore/EngineAPICore.h>

ZeldaContentsCore::ZeldaContentsCore()
{
}

ZeldaContentsCore::~ZeldaContentsCore()
{
}

// 엔진이 실행되고 단 1번 실행된다.
void ZeldaContentsCore::BeginPlay()
{
	UEngineAPICore::GetCore()->CreateLevel("Title");
	UEngineAPICore::GetCore()->CreateLevel("Play");
	UEngineAPICore::GetCore()->CreateLevel("End");
	// CreateLevel();

}

void ZeldaContentsCore::Tick()
{
}