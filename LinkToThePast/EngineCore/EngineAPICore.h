#pragma once
#include <string>
#include <Windows.h>
#include <EnginePlatform/EngineWindow.h>
#include <EngineBase/EngineTimer.h>

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
		ULevel* NewLevel = new ULevel();

		NewLevel->CreateGameMode<GameModeType, MainPawnType>();

		Levels.insert({ _LevelName.data(), NewLevel });

		return NewLevel;
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
};

