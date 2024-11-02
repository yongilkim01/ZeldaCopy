#include "PreCompile.h"
#include "EngineWinDebug.h"


namespace UEngineDebug
{
	void WinAPIOutPutString(UEngineWinImage* WinImage, std::string_view OutputStr, FVector2D Position)
	{
		TextOutA(WinImage->GetDC(), Position.iX(), Position.iY(), OutputStr.data(), static_cast<int>(OutputStr.size()));
	}
}