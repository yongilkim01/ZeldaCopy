#pragma once
#include <Windows.h>
#include <assert.h>


#define MSGASSERT(VALUE) std::string ErrorText = VALUE; MessageBoxA(nullptr, ErrorText.c_str(), "ġ���� ����", MB_OK); assert(false);

namespace UEngineDebug
{
	// �и��ؾ� �ϰڳ׿�
	void OutPutString(const std::string& Text);
}

