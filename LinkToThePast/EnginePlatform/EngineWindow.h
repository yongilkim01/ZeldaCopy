#pragma once
#include <Windows.h>

// ���� �� ��

// ���� :
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

	// ������������ �������� �ȵǰų� ������ �ȵǴ� �ڵ尡 �ȴ�.
	// hwnd => ������ â 1��
	HWND WindowHandle = nullptr;

};