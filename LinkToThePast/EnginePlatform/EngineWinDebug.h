#pragma once
#include <Windows.h>
#include <assert.h>

namespace UEngineDebug
{
	// �ο��� ������ ����ϼ��� ����� ����� ��� ��Ȳ�� �����Ҽ� �ְ� ����Ƿ� 
	// ���ڰ� ���� ����ϱⰡ ��ƴ�.
	void WinAPIOutPutString(UEngineWinImage* _Image, std::string_view _Text, FVector2D _Pos);
	// �и��ؾ� �ϰڳ׿�
}