#include "PreCompile.h"
#include "EngineAPICore.h"

#include <EnginePlatform/EngineWindow.h>
#include <EnginePlatform/EngineInput.h>
#include <EnginePlatform/EngineSound.h>

#include <EngineBase/EngineDelegate.h>
#include <EngineBase/EngineDebug.h>

#include <Windows.h>

/** 정적 변수를 nullptr로 초기화 */
UEngineAPICore* UEngineAPICore::MainCore = nullptr;
UContentsCore* UEngineAPICore::UserCore = nullptr;

UEngineAPICore::UEngineAPICore()
{
	// == 언리얼 GEngine()
	//MainCore = this;
}

UEngineAPICore::~UEngineAPICore()
{
	// 저장하고 있던 레벨들의 메모리 해제
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
	// 메모리 릭 체크 설정
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 함수 인자로 전달받은 유저 코어를 엔진 코어의 유저 코어에게 할당
	UserCore = ContentsCore;

	// 함수 인자로 전달받은 HInstance 핸들러로 윈도우 초기화
	UEngineWindow::EngineWindowInit(hInstance);

	// 엔진 코어 객체 생성
	UEngineAPICore Core = UEngineAPICore();
	// 엔진 코어 객체의 윈도우 오픈
	Core.EngineMainWindow.Open();
	// 전역 정적 코어 변수에 생성된 엔진 코어의 주소값을 할당
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

	/** 레벨 이동 방법 */
	if (nullptr != NextLevel)
	{
		// 레벨들을 왔다갔다 할때가 있기 때문에.
		// 그 순간마다 여러분들이 뭔가를 해주고 싶을수가 있다.
		if (nullptr != CurLevel)
		{
			CurLevel->LevelChangeEnd();
		}
		CurLevel = NextLevel;

		NextLevel->LevelChangeStart();

		NextLevel = nullptr;
		// 델타타임이 지연될수 있으므로 델타타임을 초기화시켜주는것이 좋다.
		DeltaTimer.TimeStart();

	}

	DeltaTimer.TimeCheck();
	float DeltaTime = DeltaTimer.GetDeltaTime();

	UEngineSound::Update();

	// 키체크
	UEngineInput::GetInst().KeyCheck(DeltaTime);

	if (CurLevel == nullptr)
	{
		MSGASSERT("엔진 코어에 현재 레벨이 지정되지 않았습니다");
		return;
	}

	UEngineInput::GetInst().EventCheck(DeltaTime);
	CurLevel->Tick(DeltaTime);
	CurLevel->Render(DeltaTime);
	CurLevel->Collision(DeltaTime);
	CurLevel->Release(DeltaTime);
}

void UEngineAPICore::OpenLevel(std::string_view _LevelName)
{
	std::string UpperName = UEngineString::ToUpper(_LevelName);

	std::map<std::string, class ULevel*>::iterator FindIter = Levels.find(UpperName);
	std::map<std::string, class ULevel*>::iterator EndIter = Levels.end();

	if (EndIter == FindIter)
	{
		MSGASSERT(UpperName + " 라는 이름의 레벨은 존재하지 않습니다.");
		return;
	}

	// 최신 방식
	NextLevel = FindIter->second;
}