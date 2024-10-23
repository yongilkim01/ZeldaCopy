#include "EngineWindow.h"
//#ifdef _WINDOWS
//#include <Windows.h>
//#elseif _������
//#include <Windows.h>
//#elseif �ȵ���̵�
//#endif 

HINSTANCE UEngineWindow::hInstance = nullptr;

void UEngineWindow::EngineWindowInit(HINSTANCE _Instance)
{
    hInstance = _Instance;
}

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
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int UEngineWindow::WindowMessageLoop()
{
    // ����Ű �ε� ����
// HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));
    MSG msg;

    // �⺻ �޽��� �����Դϴ�:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        // ����Ű�� �ƿ� �Ȼ���ϹǷ� ����Ű�� ó���Ѵٴ� �� ������ �����Ƿ� �ǹ̰� ���� �ڵ尡 �Ǿ���.
        if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

UEngineWindow::UEngineWindow()
{
    // �������� �� ��Ƽ����Ʈ ���·� �Լ����� ����ϰڴٰ� �����Ƿ� 
    // WNDCLASSEXW => WNDCLASSEXA 
    WNDCLASSEXA wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    // wcex.hInstance = nullptr;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "DefaultWindow";
    wcex.hIconSm = nullptr;
    // wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    RegisterClassExA(&wcex);

    WindowHandle = CreateWindowA("DefaultWindow", "MainWindow", WS_OVERLAPPEDWINDOW,
        -0, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!WindowHandle)
    {
        return;
    }


}

UEngineWindow::~UEngineWindow()
{
}

void UEngineWindow::Open()
{
    // �ܼ��� ����â�� �����ִ� �͸��� �ƴ϶�
    ShowWindow(WindowHandle, SW_SHOW);
    UpdateWindow(WindowHandle);
    // ShowWindow(WindowHandle, SW_HIDE);
}