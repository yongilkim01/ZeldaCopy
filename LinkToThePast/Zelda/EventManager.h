#pragma once

/**
 *	설명
 */
class UEventManager
{
public:
	static UEventManager& GetInstance()
	{
		static UEventManager Inst = UEventManager();
		return Inst;
	}

	/** 생성자, 소멸자 */
	~UEventManager();

	/** 객체 값 복사 방지 */
	UEventManager(const UEventManager& _Other) = delete;
	UEventManager(UEventManager&& _Other) noexcept = delete;
	UEventManager& operator=(const UEventManager& _Other) = delete;
	UEventManager& operator=(UEventManager&& _Other) noexcept = delete;

	/** 이벤트 매니저 메소드 */
	void EventTimeBeginPlay(float CheckTime);
	void EventTimeTick(float DeltaTime);

	/** 겟, 셋 메소드 */
	void SetEventPause(bool Pause)
	{
		EventPause = Pause;
	}
	bool GetEventPause()
	{
		return EventPause;
	}
protected:

private:
	UEventManager();

	float CheckTime = 0.0f;
	float CurrentTime = 0.0f;

	bool EventPause = false;
};