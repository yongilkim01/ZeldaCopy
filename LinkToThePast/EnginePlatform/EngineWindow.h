#pragma once
#include <Windows.h>

// 정신 잘 붙

// 설명 :
class UEngineWindow
{
public:
	static void EngineWindowInit(HINSTANCE _Instance);

	static int WindowMessageLoop();
	// constrcuter destructer
	UEngineWindow();
	~UEngineWindow();

	// delete Function
	UEngineWindow(const UEngineWindow& _Other) = delete;
	UEngineWindow(UEngineWindow&& _Other) noexcept = delete;
	UEngineWindow& operator=(const UEngineWindow& _Other) = delete;
	UEngineWindow& operator=(UEngineWindow&& _Other) noexcept = delete;

	void Open();


protected:

private:
	static HINSTANCE hInstance;

	// 리눅스에서는 컴파일이 안되거나 실행이 안되는 코드가 된다.
	// hwnd => 위도우 창 1개
	HWND WindowHandle = nullptr;

};