#pragma once
#include <EngineBase/EngineDelegate.h>
#include <EngineBase/EngineDebug.h>

#include <vector>
#include <functional>
#include <map>

/** 키 이벤트 */
enum class KeyEvent
{
	Down,
	Press,
	Free,
	Up,
};

/** 
 *	엔진 입력 처리 클래스
 */
class UEngineInput
{
public:
	/** 생성자, 소멸자 */
	~UEngineInput();

	/** 객체 값 복사 방지 */
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
	/** 키 이벤트 */
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
			MSGASSERT("등록되지 않은 키가 존재합니다.");
			return false;
		}

		return Keys[KeyIndex].IsDown;
	}

	bool IsPress(int KeyIndex)
	{
		if (false == Keys.contains(KeyIndex))
		{
			MSGASSERT("아직도 등록되지 않은 키가 존재합니다.");
			return false;
		}

		return Keys[KeyIndex].IsPress;
	}

	float IsPreeTime(int KeyIndex)
	{
		if (false == Keys.contains(KeyIndex))
		{
			MSGASSERT("아직도 등록되지 않은 키가 존재합니다.");
			return false;
		}

		return Keys[KeyIndex].PressTime;
	}


	bool IsFree(int KeyIndex)
	{
		if (false == Keys.contains(KeyIndex))
		{
			MSGASSERT("아직도 등록되지 않은 키가 존재합니다.");
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

