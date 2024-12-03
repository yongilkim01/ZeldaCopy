#pragma once
#include <EngineBase/EngineDelegate.h>
#include <EngineBase/EngineDebug.h>

#include <vector>
#include <functional>
#include <map>

/** Ű �̺�Ʈ */
enum class KeyEvent
{
	Down,
	Press,
	Free,
	Up,
};

/** 
 *	���� �Է� ó�� Ŭ����
 */
class UEngineInput
{
public:
	/** ������, �Ҹ��� */
	~UEngineInput();

	/** ��ü �� ���� ���� */
	UEngineInput(const UEngineInput& Other) = delete;
	UEngineInput(UEngineInput&& Other) noexcept = delete;
	UEngineInput& operator=(const UEngineInput& Other) = delete;
	UEngineInput& operator=(UEngineInput&& Other) noexcept = delete;

	static UEngineInput& GetInst()
	{
		static UEngineInput Inst = UEngineInput();
		return Inst;
	}

protected:

private:
	/** Ű �̺�Ʈ */
	class UEngineKey
	{
	public:
		int Key = -1;

		bool IsDown = false;

		bool IsPress = false;

		bool IsUp = false;

		bool IsFree = true;

		float PressTime = 0.0f;

		std::vector<std::function<void()>> PressEvents;
		std::vector<std::function<void()>> DownEvents;
		std::vector<std::function<void()>> UpEvents;
		std::vector<std::function<void()>> FreeEvents;

		UEngineKey()
		{

		}

		UEngineKey(int KeyValue)
			: Key(KeyValue)
		{

		}

		void EventCheck();
		void KeyCheck(float DeltaTime);
	};

public:
	void KeyCheck(float DeltaTime);
	void EventCheck(float DeltaTime);

	bool IsDown(int KeyIndex)
	{
		if (Keys.contains(KeyIndex) == false)
		{
			MSGASSERT("��ϵ��� ���� Ű�� �����մϴ�.");
			return false;
		}

		return Keys[KeyIndex].IsDown;
	}

	bool IsPress(int KeyIndex)
	{
		if (false == Keys.contains(KeyIndex))
		{
			MSGASSERT("������ ��ϵ��� ���� Ű�� �����մϴ�.");
			return false;
		}

		return Keys[KeyIndex].IsPress;
	}

	float IsPreeTime(int KeyIndex)
	{
		if (false == Keys.contains(KeyIndex))
		{
			MSGASSERT("������ ��ϵ��� ���� Ű�� �����մϴ�.");
			return false;
		}

		return Keys[KeyIndex].PressTime;
	}


	bool IsFree(int KeyIndex)
	{
		if (false == Keys.contains(KeyIndex))
		{
			MSGASSERT("������ ��ϵ��� ���� Ű�� �����մϴ�.");
			return false;
		}

		return Keys[KeyIndex].IsFree;
	}

	void BindAction(int KeyIndex, KeyEvent EventType, std::function<void()> Function);

protected:

private:
	std::map<int, UEngineKey> Keys;

	UEngineInput();
};

