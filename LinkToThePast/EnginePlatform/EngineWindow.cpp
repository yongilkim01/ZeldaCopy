#include "PreCompile.h"
#include "EngineWindow.h"
#include <EngineBase/EngineDebug.h>

//#ifdef _WINDOWS
//#include <Windows.h>
//#elseif _������
//#include <Windows.h>
//#elseif �ȵ���̵�
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
        // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
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

    // ������ ������ ����� �Ѵٸ� ���⼭ �Ϸ��� �Ѱ�.
    // ����Ʈ ������ Ŭ���� ���
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
        MSGASSERT(std::string(_Class.lpszClassName) + " ���� �̸��� ������ Ŭ������ 2�� ����߽��ϴ�");
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

    // �������ϴ� ������ �ظ��ϸ� ������� ������ ������ ����.
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
        MSGASSERT(std::string(_ClassName) + " ������� ���� Ŭ������ ������â�� ������� �߽��ϴ�");
        return;
    }

    WindowHandle = CreateWindowA(_ClassName.data(), _TitleName.data(), WS_OVERLAPPEDWINDOW,
        0, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (nullptr == WindowHandle)
    {
        MSGASSERT(std::string(_TitleName) + " ������ ������ �����߽��ϴ�.");
        return;
    }

    HDC WindowMainDC = GetDC(WindowHandle);

    WindowImage = new UEngineWinImage();

    WindowImage->Create(WindowMainDC);
}

void UEngineWindow::Open(std::string_view _TitleName /*= "Window"*/)
{
    // �� window �ȸ���� ������ �ϳ�?
    if (nullptr == WindowHandle)
    {
        // �����
        Create(_TitleName);
    }

    if (0 == WindowHandle)
    {
        return;
    }

    // �ܼ��� ����â�� �����ִ� �͸��� �ƴ϶�
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

    // �̰� �� ������ִ� �Լ��̴�.
    // Ÿ��Ʋ�� ũ����� ������ ũ��� �ش�.
    // ������ ����
    // ���� �������� ��Ÿ���� �־���� �Ѵ�.

    // �׷��� �� �̳༮�� 
    // �����쿡�� �������� ��ġ�� ������ ũ�⸦ �ְ� �ȴ�.
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

    ::SetWindowPos(WindowHandle, nullptr, _Pos.iX(), _Pos.iY(), Rc.right - Rc.left, Rc.bottom - Rc.top, SWP_NOZORDER);
}