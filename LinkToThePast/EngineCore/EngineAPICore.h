#pragma once
#include <string>
#include <Windows.h>
#include <EnginePlatform/EngineWindow.h>
#include <EngineBase/EngineTimer.h>
#include <EngineBase/EngineString.h>

#pragma comment (lib, "EngineBase.lib")
#pragma comment (lib, "EnginePlatform.lib")

#include "Level.h"

/** ���� ���� ����
*
*   ���� ����
*      |
*      V
*   ���� ����
*      |
*      V
*   ���Ӹ��, ���� �� ����
*/

/** ������ �ھ� �������̽� */
class UContentsCore
{
public:
	virtual void BeginPlay() = 0;
	virtual void Tick() = 0;
};

/** ���� ���� �ھ� Ŭ���� */
class UEngineAPICore
{
public:
	/** ������, �Ҹ��� */
	UEngineAPICore();
	~UEngineAPICore();

	/** ������ ���� */
	UEngineAPICore(const UEngineAPICore& _Other) = delete;
	UEngineAPICore(UEngineAPICore&& _Other) noexcept = delete;
	UEngineAPICore& operator=(const UEngineAPICore& _Other) = delete;
	UEngineAPICore& operator=(UEngineAPICore&& _Other) noexcept = delete;

	/** ���� ���� ���� �޼ҵ� */
	static int EngineStart(HINSTANCE _Inst, UContentsCore* _UserCore);
	/** ���� ���� �޼ҵ� */
	void OpenLevel(std::string_view _LevelName);
	template<typename GameModeType, typename MainPawnType>
	ULevel* CreateLevel(std::string_view _LevelName)
	{
		std::string UpperName = UEngineString::ToUpper(_LevelName);
		if (false != Levels.contains(UpperName))
		{
			MSGASSERT("�����ϴ� �̸��� ������ �� ����� �����ϴ�" + UpperName);
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
		// ���� ���� �̳༮�� ����� �ȵȴ�.
		if (CurLevel->GetName() != UpperName)
		{
			DestroyLevel(_LevelName);
			CreateLevel<GameModeType, MainPawnType>(UpperName);
			return;
		}

		// CurLevel�� �����Ǿ�� �Ѵ�.
		// ���� �����ʹ� ����ִ�. CurLevel
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
			// MSGASSERT("�������� �ʴ� ������ �����Ҽ� �����ϴ�." + UpperName);
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

	/** ���� �ھ� ��ȯ �޼ҵ� */
	static class UEngineAPICore* GetCore() { return MainCore; }
	/** ���� ������ ��ȯ �޼ҵ� */
	UEngineWindow& GetMainWindow() { return EngineMainWindow; }
	/** ��Ÿ Ÿ�� ��ȯ �޼ҵ� */
	float GetDeltaTime() { return DeltaTimer.GetDeltaTime(); }

private:
	/** ���� �ʱ�ȭ ���� �޼ҵ� */
	static void EngineBeginPlay();
	/** ���� ������Ʈ ���� �޼ҵ� */
	static void EngineTick();
	/** ���� ������Ʈ �޼ҵ� */
	void Tick();

private:
	/** ���� �ھ� ���� ��� ���� */
	static UEngineAPICore* MainCore;
	/** ������ �ھ� ���� ��� ���� */
	static UContentsCore* UserCore;
	/** ��Ÿ Ÿ�̸� ��� ���� */
	UEngineTimer DeltaTimer = UEngineTimer();
	/** ���� ���� ������ ��� ���� */
	UEngineWindow EngineMainWindow = UEngineWindow();
	/** �������� �� ���·� �����ϴ� ��� ���� */
	std::map<std::string, class ULevel*> Levels;
	/** ���� ������� ���� */
	class ULevel* CurLevel = nullptr;
	/** ���� �̵��� ���� ��� ���� */
	class ULevel* NextLevel = nullptr;
	/** ���� ���� ���� ��� ���� */
	bool IsCurLevelReset = false;

};

