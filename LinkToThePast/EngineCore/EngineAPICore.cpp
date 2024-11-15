#include "PreCompile.h"
#include "EngineAPICore.h"

#include <EnginePlatform/EngineWindow.h>
#include <EnginePlatform/EngineInput.h>
#include <EnginePlatform/EngineSound.h>

#include <EngineBase/EngineDelegate.h>
#include <EngineBase/EngineDebug.h>

#include <Windows.h>

/** ���� ������ nullptr�� �ʱ�ȭ */
UEngineAPICore* UEngineAPICore::MainCore = nullptr;
UContentsCore* UEngineAPICore::UserCore = nullptr;

UEngineAPICore::UEngineAPICore()
{
	// == �𸮾� GEngine()
	//MainCore = this;
}

UEngineAPICore::~UEngineAPICore()
{
	// �����ϰ� �ִ� �������� �޸� ����
	{
		std::map<std::string, class ULevel*>::iterator StartIter = Levels.begin();
		std::map<std::string, class ULevel*>::iterator EndIter = Levels.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (nullptr != StartIter->second)
			{
				delete StartIter->second;
				StartIter->second = nullptr;
			}
		}
		Levels.clear();

		UEngineSound::Release();
	}
}


int UEngineAPICore::EngineStart(HINSTANCE hInstance, UContentsCore* ContentsCore)
{
	// �޸� �� üũ ����
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// �Լ� ���ڷ� ���޹��� ���� �ھ ���� �ھ��� ���� �ھ�� �Ҵ�
	UserCore = ContentsCore;

	// �Լ� ���ڷ� ���޹��� HInstance �ڵ鷯�� ������ �ʱ�ȭ
	UEngineWindow::EngineWindowInit(hInstance);

	// ���� �ھ� ��ü ����
	UEngineAPICore Core = UEngineAPICore();
	// ���� �ھ� ��ü�� ������ ����
	Core.EngineMainWindow.Open();
	// ���� ���� �ھ� ������ ������ ���� �ھ��� �ּҰ��� �Ҵ�
	MainCore = &Core;

	EngineDelegate Start = EngineDelegate(std::bind(EngineBeginPlay));
	EngineDelegate FrameLoop = EngineDelegate(std::bind(EngineTick));

	return UEngineWindow::WindowMessageLoop(Start, FrameLoop);
}


void UEngineAPICore::EngineBeginPlay()
{
	UserCore->BeginPlay();
}

void UEngineAPICore::EngineTick()
{
	UserCore->Tick();
	MainCore->Tick();
}

void UEngineAPICore::Tick()
{

	if (true == IsCurLevelReset)
	{
		delete CurLevel;
		CurLevel = nullptr;
		IsCurLevelReset = false;
	}

	/** ���� �̵� ��� */
	if (nullptr != NextLevel)
	{
		// �������� �Դٰ��� �Ҷ��� �ֱ� ������.
		// �� �������� �����е��� ������ ���ְ� �������� �ִ�.
		if (nullptr != CurLevel)
		{
			CurLevel->LevelChangeEnd();
		}
		CurLevel = NextLevel;

		NextLevel->LevelChangeStart();

		NextLevel = nullptr;
		// ��ŸŸ���� �����ɼ� �����Ƿ� ��ŸŸ���� �ʱ�ȭ�����ִ°��� ����.
		DeltaTimer.TimeStart();

	}

	DeltaTimer.TimeCheck();
	float DeltaTime = DeltaTimer.GetDeltaTime();

	UEngineSound::Update();

	// Űüũ
	UEngineInput::GetInst().KeyCheck(DeltaTime);

	if (CurLevel == nullptr)
	{
		MSGASSERT("���� �ھ ���� ������ �������� �ʾҽ��ϴ�");
		return;
	}

	UEngineInput::GetInst().EventCheck(DeltaTime);
	CurLevel->Tick(DeltaTime);
	CurLevel->Render(DeltaTime);
	CurLevel->Release(DeltaTime);
}

void UEngineAPICore::OpenLevel(std::string_view _LevelName)
{
	std::string UpperName = UEngineString::ToUpper(_LevelName);

	std::map<std::string, class ULevel*>::iterator FindIter = Levels.find(UpperName);
	std::map<std::string, class ULevel*>::iterator EndIter = Levels.end();

	if (EndIter == FindIter)
	{
		MSGASSERT(UpperName + " ��� �̸��� ������ �������� �ʽ��ϴ�.");
		return;
	}

	// �ֽ� ���
	NextLevel = FindIter->second;
}