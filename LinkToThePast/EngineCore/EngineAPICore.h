#pragma once
#include <string>
// �����е��� ���⿡�ٰ� �̷��� Ư�� ����� ������
// F5�� ����������. #include <Windows.h>�� ����� �ȴ�.
// �̸������ϵ� ����� ����ϸ�
// �̸������ϵ� ����� �־��� ����� ���带�ϸ� .pch���Ͽ� �������� ����
// ���Ŀ��� ������� �ʴ´�.
// ������ �ð��� 
#include <Windows.h>
#include <EnginePlatform/EngineWindow.h>
#include <EngineBase/EngineTimer.h>

#pragma comment (lib, "EngineBase.lib")
#pragma comment (lib, "EnginePlatform.lib")

#include "Level.h"

// �Լ�������
// �����Լ�

class UContentsCore
{
public:
	virtual void BeginPlay() = 0;
	virtual void Tick() = 0;
};

// ���� :
class UEngineAPICore
{
public:
	// constrcuter destructer
	UEngineAPICore();
	~UEngineAPICore();

	// delete Function
	UEngineAPICore(const UEngineAPICore& _Other) = delete;
	UEngineAPICore(UEngineAPICore&& _Other) noexcept = delete;
	UEngineAPICore& operator=(const UEngineAPICore& _Other) = delete;
	UEngineAPICore& operator=(UEngineAPICore&& _Other) noexcept = delete;

	static int EngineStart(HINSTANCE _Inst, UContentsCore* _UserCore);

	static class UEngineAPICore* GetCore()
	{
		return MainCore;
	}

	UEngineWindow& GetMainWindow()
	{
		return EngineMainWindow;
	}

	float GetDeltaTime()
	{
		return DeltaTimer.GetDeltaTime();
	}

	template<typename GameModeType, typename MainPawnType>
	ULevel* CreateLevel(std::string_view _LevelName)
	{
		ULevel* NewLevel = new ULevel();

		NewLevel->CreateGameMode<GameModeType, MainPawnType>();

		Levels.insert({ _LevelName.data(), NewLevel });

		return NewLevel;
	}

	void OpenLevel(std::string_view _LevelName);

protected:

private:
	static void EngineBeginPlay();
	static void EngineTick();
	static UEngineAPICore* MainCore;
	static UContentsCore* UserCore;

	UEngineTimer DeltaTimer = UEngineTimer();
	UEngineWindow EngineMainWindow = UEngineWindow(); // ���� ���� ������

	std::map<std::string, class ULevel*> Levels;

	class ULevel* CurLevel = nullptr;

	// �̳༮���� ���ư��� ������ ���ư���.
	void Tick();
};

