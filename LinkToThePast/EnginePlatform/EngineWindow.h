#pragma once
/** OS Header */
#include <Windows.h>

/** Std Header */
#include <map>
#include <string>
#include <functional>

/** Engine Header */
#include <EngineBase/EngineDelegate.h>
#include <EngineBase/EngineMath.h>
#include "EngineWinImage.h"

/**
* ������ â Ŭ����
*/
class UEngineWindow
{
public:
	/** ������, �Ҹ��� */
	UEngineWindow();
	~UEngineWindow();

	/** ��ü ���� ���� */
	UEngineWindow(const UEngineWindow& _Other) = delete;
	UEngineWindow(UEngineWindow&& _Other) noexcept = delete;
	UEngineWindow& operator=(const UEngineWindow& _Other) = delete;
	UEngineWindow& operator=(UEngineWindow&& _Other) noexcept = delete;

	/** ������ ���� �ʱ�ȭ �޼ҵ� */
	static void EngineWindowInit(HINSTANCE _Instance);
	static void CreateWindowClass(const WNDCLASSEXA& _Class);
	/** ������ ���� ������Ʈ �޼ҵ� */
	static int WindowMessageLoop(EngineDelegate _StartFunction, EngineDelegate _FrameFunction);

	/** ������ ���� �޼ҵ� */
	void Create(std::string_view _TitleName, std::string_view _ClassName = "Default");
	/** ������ ���� �޼ҵ� */
	void Open(std::string_view _TitleName = "Window");

	void SetWindowPosAndScale(FVector2D _Pos, FVector2D _Scale);
	void SetWindowTitle(std::string_view Text) { SetWindowTextA(WindowHandle, Text.data()); }
	FVector2D GetWindowSize() const { return WindowSize; }
	UEngineWinImage* GetWindowImage() const { return WindowImage; }
	UEngineWinImage* GetBackBuffer() const { return BackBufferImage; }
	FVector2D GetMousePos();

protected:

private:
	/** ���� ���ٿ� ���� ��ü */
	static HINSTANCE hInstance;
	/** ������ �������� ��� �� */
	static std::map<std::string, WNDCLASSEXA> WindowClasses;

	// ������������ �������� �ȵǰų� ������ �ȵǴ� �ڵ尡 �ȴ�.
	// hwnd => ������ â 1��
	UEngineWinImage* BackBufferImage = nullptr;
	UEngineWinImage* WindowImage = nullptr;
	HWND WindowHandle = nullptr;

	FVector2D WindowSize;
};