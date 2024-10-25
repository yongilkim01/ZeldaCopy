#include "PreCompile.h"
#include <LinkToThePastContents/ZeldaContentsCore.h>

#include <EngineCore/EngineAPICore.h>

#pragma comment (lib, "EngineCore.lib")
#pragma comment (lib, "LinkToThePastContents.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	ZeldaContentsCore User;
	return UEngineAPICore::EngineStart(hInstance, &User);
}