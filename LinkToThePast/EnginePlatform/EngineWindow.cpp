#include "PreCompile.h"
#include "EngineWindow.h"
#include <EngineBase/EngineDebug.h>

//#ifdef _WINDOWS
//#include <Windows.h>
//#elseif _리눅스
//#include <Windows.h>
//#elseif 안드로이드
//#endif 

HINSTANCE UEngineWindow::hInstance = nullptr;
std::map<std::string, WNDCLASSEXA> UEngineWindow::WindowClasses;
int WindowCount = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        --WindowCount;
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


void UEngineWindow::EngineWindowInit(HINSTANCE _Instance)
{
    hInstance = _Instance;

    // 어차피 무조건 해줘야 한다면 여기서 하려고 한것.
    // 디폴트 윈도우 클래스 등록
    WNDCLASSEXA wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "Default";
    wcex.hIconSm = nullptr;
    CreateWindowClass(wcex);
}

int UEngineWindow::WindowMessageLoop(EngineDelegate _StartFunction, EngineDelegate _FrameFunction)
{
    MSG msg = MSG();

    if (true == _StartFunction.IsBind())
    {
        _StartFunction();
    }

    while (0 != WindowCount)
    {
        if (0 != PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (true == _FrameFunction.IsBind())
        {
            _FrameFunction();
        }
    }

    return (int)msg.wParam;
}

void UEngineWindow::CreateWindowClass(const WNDCLASSEXA& _Class)
{
    std::map<std::string, WNDCLASSEXA>::iterator EndIter = WindowClasses.end();
    std::map<std::string, WNDCLASSEXA>::iterator FindIter = WindowClasses.find(std::string(_Class.lpszClassName));

    if (EndIter != FindIter)
    {
        MSGASSERT(std::string(_Class.lpszClassName) + " 같은 이름의 윈도우 클래스를 2번 등록했습니다");
        return;
    }

    RegisterClassExA(&_Class);

    WindowClasses.insert(std::pair{ _Class.lpszClassName, _Class });
}

UEngineWindow::UEngineWindow()
{


}

UEngineWindow::~UEngineWindow()
{
    if (nullptr != WindowImage)
    {
        delete WindowImage;
        WindowImage = nullptr;
    }

    if (nullptr != BackBufferImage)
    {
        delete BackBufferImage;
        BackBufferImage = nullptr;
    }

    // 릴리즈하는 순서는 왠만하면 만들어진 순서의 역순이 좋다.
    if (nullptr != WindowHandle)
    {
        DestroyWindow(WindowHandle);
        WindowHandle = nullptr;
    }
}

void UEngineWindow::Create(std::string_view _TitleName, std::string_view _ClassName)
{
    if (false == WindowClasses.contains(_ClassName.data()))
    {
        MSGASSERT(std::string(_ClassName) + " 등록하지 않은 클래스로 윈도우창을 만들려고 했습니다");
        return;
    }

    WindowHandle = CreateWindowA(_ClassName.data(), _TitleName.data(), WS_OVERLAPPEDWINDOW,
        0, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (nullptr == WindowHandle)
    {
        MSGASSERT(std::string(_TitleName) + " 윈도우 생성에 실패했습니다.");
        return;
    }

    HDC WindowMainDC = GetDC(WindowHandle);

    WindowImage = new UEngineWinImage();

    WindowImage->Create(WindowMainDC);
}

void UEngineWindow::Open(std::string_view _TitleName /*= "Window"*/)
{
    // 어 window 안만들고 띄우려고 하네?
    if (nullptr == WindowHandle)
    {
        // 만들어
        Create(_TitleName);
    }

    if (0 == WindowHandle)
    {
        return;
    }

    // 단순히 윈도창을 보여주는 것만이 아니라
    ShowWindow(WindowHandle, SW_SHOW);
    UpdateWindow(WindowHandle);
    ++WindowCount;
    // ShowWindow(WindowHandle, SW_HIDE);
}

void UEngineWindow::SetWindowPosAndScale(FVector2D _Pos, FVector2D _Scale)
{
    if (false == WindowSize.EqualToInt(_Scale))
    {
        if (nullptr != BackBufferImage)
        {
            delete BackBufferImage;
            BackBufferImage = nullptr;
        }

        BackBufferImage = new UEngineWinImage();
        BackBufferImage->Create(WindowImage, _Scale);
    }

    WindowSize = _Scale;

    RECT Rc = { 0, 0, _Scale.iX(), _Scale.iY() };

    // 이게 그 계산해주는 함수이다.
    // 타이틀바 크기까지 합쳐진 크기로 준다.
    // 윈도우 입장
    // 현재 윈도우의 스타일을 넣어줘야 한다.

    // 그러면 또 이녀석은 
    // 윈도우에서 가져야할 위치를 포함한 크기를 주게 된다.
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

    ::SetWindowPos(WindowHandle, nullptr, _Pos.iX(), _Pos.iY(), Rc.right - Rc.left, Rc.bottom - Rc.top, SWP_NOZORDER);
}