#pragma once
#include <Windows.h>
#include <assert.h>


#define MSGASSERT(VALUE) MessageBoxA(nullptr, VALUE, "ġ���� ����", MB_OK); assert(false);
