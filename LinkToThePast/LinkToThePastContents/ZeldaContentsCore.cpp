#include "PreCompile.h"
#include "ZeldaContentsCore.h"
#include <EngineCore/EngineAPICore.h>

ZeldaContentsCore::ZeldaContentsCore()
{
}

ZeldaContentsCore::~ZeldaContentsCore()
{
}

// ������ ����ǰ� �� 1�� ����ȴ�.
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