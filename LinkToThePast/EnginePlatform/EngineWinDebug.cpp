#include "PreCompile.h"
#include "EngineWinDebug.h"


namespace UEngineDebug
{
	// f
	// �и��ؾ� �ϰڳ׿�
	void WinAPIOutPutString(UEngineWinImage* _Image, std::string_view _Text, FVector2D _Pos)
	{
		// ���Ⱑ ������ ��ƴ�.
		TextOutA(_Image->GetDC(), _Pos.iX(), _Pos.iY(), _Text.data(), static_cast<int>(_Text.size()));
	}
}