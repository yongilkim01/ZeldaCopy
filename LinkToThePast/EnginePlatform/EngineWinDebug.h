#pragma once
#include <Windows.h>
#include <assert.h>

namespace UEngineDebug
{
	void WinAPIOutPutString(UEngineWinImage* WinImage, std::string_view OutputStr, FVector2D Position);
}