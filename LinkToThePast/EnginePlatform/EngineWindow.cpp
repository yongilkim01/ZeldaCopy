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
std::map<std::string, WNDCLASSEXA> UEngineWindow::WindowClasss;
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

int UEngineWindow::WindowMessageLoop(EngineDelegate _FrameFunction)
{
    // ����Ű �ε� ����
    // HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));
    MSG msg;

    // �⺻ �޽��� �����Դϴ�:
    // �޼��� ������ getMessage��� ������ ������ ������ ����.
    // ���� �Լ��̱� �����̴�.
    // ���� �ڽ��� ������ ���������� �����ϴ� �Լ�.

    // GetMessage
    // �޼����� ���� => ������ ��ٸ�
    // �޼����� �ִ� => ó���ϰ� ����

    // ó���ϰ� ����
    // �޼����� ���� => ����
    // �޼����� �ִ� => ó���ϰ� ����

    // WindowCount;

    while (WindowCount)
    {
        // if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))  => ������ ����Ű ��ü�� �������
        // ���� ���̹Ƿ� �׳� ����

        // PM_REMOVE == ���� ó���Ҷ� ���ݱ��� ���� �޼��� ������.
        if (0 != PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (true == _FrameFunction.IsBind())
        {
            _FrameFunction();
        }
        // �޼����� ���� �ð��� �� ������ �����°ž�.
        // �޼��� ó���ϰ� ���� �� ���ӿ����� ������.
    }

    return (int)msg.wParam;
}

void UEngineWindow::CreateWindowClass(const WNDCLASSEXA& _Class)
{
    // �Ϲ����� ���� ����

    std::map<std::string, WNDCLASSEXA>::iterator EndIter = WindowClasss.end();
    std::map<std::string, WNDCLASSEXA>::iterator FindIter = WindowClasss.find(std::string(_Class.lpszClassName));

    // ckw
    if (EndIter != FindIter)
    {
        // std::string ErrorText = "���� �̸��� ������ Ŭ������ 2�� ����߽��ϴ�" + std::string(_Class.lpszClassName);

        // std::string ���ο� ��� �ִ� �ɹ����� => std::string => std::vector<char>
        // std::vector<char> char* = new char[100];
        // ErrorText const char* �������ִ� �Լ��� c_str()
        // const char* Text = ErrorText.c_str();
        MSGASSERT(std::string(_Class.lpszClassName) + " ���� �̸��� ������ Ŭ������ 2�� ����߽��ϴ�");
        return;
    }

    RegisterClassExA(&_Class);

    WindowClasss.insert(std::pair{ _Class.lpszClassName, _Class });
}

UEngineWindow::UEngineWindow()
{


}

UEngineWindow::~UEngineWindow()
{
}

void UEngineWindow::Create(std::string_view _TitleName, std::string_view _ClassName)
{
    if (false == WindowClasss.contains(_ClassName.data()))
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

}

void UEngineWindow::Open(std::string_view _TitleName /*= "Window"*/)
{
    // �� window �ȸ���� ������ �ϳ�?
    if (nullptr == WindowHandle)
    {
        // �����
        Create("Window");
    }

    // �ܼ��� ����â�� �����ִ� �͸��� �ƴ϶�
    ShowWindow(WindowHandle, SW_SHOW);
    UpdateWindow(WindowHandle);
    ++WindowCount;
    // ShowWindow(WindowHandle, SW_HIDE);
}