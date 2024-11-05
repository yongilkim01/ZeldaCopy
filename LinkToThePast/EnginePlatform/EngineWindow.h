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
* 윈도우 창 클래스
*/
class UEngineWindow
{
public:
	/** 생성자, 소멸자 */
	UEngineWindow();
	~UEngineWindow();

	/** 객체 복사 방지 */
	UEngineWindow(const UEngineWindow& _Other) = delete;
	UEngineWindow(UEngineWindow&& _Other) noexcept = delete;
	UEngineWindow& operator=(const UEngineWindow& _Other) = delete;
	UEngineWindow& operator=(UEngineWindow&& _Other) noexcept = delete;

	/** 윈도우 정적 초기화 메소드 */
	static void EngineWindowInit(HINSTANCE _Instance);
	static void CreateWindowClass(const WNDCLASSEXA& _Class);
	/** 윈도우 정적 업데이트 메소드 */
	static int WindowMessageLoop(EngineDelegate _StartFunction, EngineDelegate _FrameFunction);

	/** 윈도우 생성 메소드 */
	void Create(std::string_view _TitleName, std::string_view _ClassName = "Default");
	/** 윈도우 열기 메소드 */
	void Open(std::string_view _TitleName = "Window");

	void SetWindowPosAndScale(FVector2D _Pos, FVector2D _Scale);
	void SetWindowTitle(std::string_view Text) { SetWindowTextA(WindowHandle, Text.data()); }
	FVector2D GetWindowSize() const { return WindowSize; }
	UEngineWinImage* GetWindowImage() const { return WindowImage; }
	UEngineWinImage* GetBackBuffer() const { return BackBufferImage; }
	FVector2D GetMousePos();

protected:

private:
	/** 전역 접근용 정적 객체 */
	static HINSTANCE hInstance;
	/** 윈도우 정보들을 담는 맵 */
	static std::map<std::string, WNDCLASSEXA> WindowClasses;

	// 리눅스에서는 컴파일이 안되거나 실행이 안되는 코드가 된다.
	// hwnd => 위도우 창 1개
	UEngineWinImage* BackBufferImage = nullptr;
	UEngineWinImage* WindowImage = nullptr;
	HWND WindowHandle = nullptr;

	FVector2D WindowSize;
};