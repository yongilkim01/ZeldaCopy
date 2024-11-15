#pragma once
#include <string>
#include <Windows.h>
#include <EnginePlatform/EngineWindow.h>
#include <EngineBase/EngineTimer.h>
#include <EngineBase/EngineString.h>

#pragma comment (lib, "EngineBase.lib")
#pragma comment (lib, "EnginePlatform.lib")

#include "Level.h"

/** 엔진 시작 구조
*
*   엔진 시작
*      |
*      V
*   레벨 생성
*      |
*      V
*   게임모드, 메인 폰 생성
*/

/** 컨텐츠 코어 인터페이스 */
class UContentsCore
{
public:
	virtual void BeginPlay() = 0;
	virtual void Tick() = 0;
};

/** 메인 엔진 코어 클래스 */
class UEngineAPICore
{
public:
	/** 생성자, 소멸자 */
	UEngineAPICore();
	~UEngineAPICore();

	/** 연산자 삭제 */
	UEngineAPICore(const UEngineAPICore& _Other) = delete;
	UEngineAPICore(UEngineAPICore&& _Other) noexcept = delete;
	UEngineAPICore& operator=(const UEngineAPICore& _Other) = delete;
	UEngineAPICore& operator=(UEngineAPICore&& _Other) noexcept = delete;

	/** 엔진 시작 정적 메소드 */
	static int EngineStart(HINSTANCE _Inst, UContentsCore* _UserCore);
	/** 레벨 관련 메소드 */
	void OpenLevel(std::string_view _LevelName);
	template<typename GameModeType, typename MainPawnType>
	ULevel* CreateLevel(std::string_view _LevelName)
	{
		std::string UpperName = UEngineString::ToUpper(_LevelName);
		if (false != Levels.contains(UpperName))
		{
			MSGASSERT("존재하는 이름의 레벨을 또 만들수 없습니다" + UpperName);
			return nullptr;
		}

		ULevel* NewLevel = new ULevel();

		NewLevel->CreateGameMode<GameModeType, MainPawnType>();

		NewLevel->SetName(UpperName);

		Levels.insert({ UpperName, NewLevel });

		return NewLevel;
	}

	template<typename GameModeType, typename MainPawnType>
	void ResetLevel(std::string_view _LevelName)
	{
		// DestroyLevelName = _LevelName;
		std::string UpperName = UEngineString::ToUpper(_LevelName);
		// 지금 당장 이녀석을 지우면 안된다.
		if (CurLevel->GetName() != UpperName)
		{
			DestroyLevel(_LevelName);
			CreateLevel<GameModeType, MainPawnType>(UpperName);
			return;
		}

		// CurLevel은 삭제되어야 한다.
		// 나의 포인터는 살아있다. CurLevel
		std::map<std::string, class ULevel*>::iterator FindIter = Levels.find(UpperName);
		Levels.erase(FindIter);
		NextLevel = CreateLevel<GameModeType, MainPawnType>(UpperName);
		IsCurLevelReset = true;
	}

	void DestroyLevel(std::string_view _LevelName)
	{
		std::string UpperName = UEngineString::ToUpper(_LevelName);
		if (false == Levels.contains(UpperName))
		{
			// MSGASSERT("존재하지 않는 레벨을 리셋할수 없습니다." + UpperName);
			return;
		}
		std::map<std::string, class ULevel*>::iterator FindIter = Levels.find(UpperName);
		if (nullptr != FindIter->second)
		{
			delete FindIter->second;
			FindIter->second = nullptr;
		}
		Levels.erase(FindIter);
	}

	/** 엔진 코어 반환 메소드 */
	static class UEngineAPICore* GetCore() { return MainCore; }
	/** 메인 윈도우 반환 메소드 */
	UEngineWindow& GetMainWindow() { return EngineMainWindow; }
	/** 델타 타임 반환 메소드 */
	float GetDeltaTime() { return DeltaTimer.GetDeltaTime(); }

private:
	/** 엔진 초기화 정적 메소드 */
	static void EngineBeginPlay();
	/** 엔진 업데이트 정적 메소드 */
	static void EngineTick();
	/** 게임 업데이트 메소드 */
	void Tick();

private:
	/** 엔진 코어 정적 멤버 변수 */
	static UEngineAPICore* MainCore;
	/** 콘텐츠 코어 정적 멤버 변수 */
	static UContentsCore* UserCore;
	/** 델타 타이머 멤버 변수 */
	UEngineTimer DeltaTimer = UEngineTimer();
	/** 엔진 메인 윈도우 멤버 변수 */
	UEngineWindow EngineMainWindow = UEngineWindow();
	/** 레벨들을 맵 형태로 관리하는 멤버 변수 */
	std::map<std::string, class ULevel*> Levels;
	/** 현재 레벨멤버 변수 */
	class ULevel* CurLevel = nullptr;
	/** 다음 이동할 레벨 멤버 변수 */
	class ULevel* NextLevel = nullptr;
	/** 레벨 리셋 여부 멤버 변수 */
	bool IsCurLevelReset = false;

};

