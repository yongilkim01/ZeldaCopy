#pragma once
#include <EngineBase/TimeEvent.h>

/**
 *	����
 */
class UEventManager
{
public:
	static UEventManager& GetInstance()
	{
		static UEventManager Inst = UEventManager();
		return Inst;
	}

	/** ������, �Ҹ��� */
	~UEventManager();

	/** ��ü �� ���� ���� */
	UEventManager(const UEventManager& _Other) = delete;
	UEventManager(UEventManager&& _Other) noexcept = delete;
	UEventManager& operator=(const UEventManager& _Other) = delete;
	UEventManager& operator=(UEventManager&& _Other) noexcept = delete;

	/** �̺�Ʈ �Ŵ��� �޼ҵ� */
	void EventTimeBeginPlay(float CheckTime);
	void EventTimeTick(float DeltaTime);
	void SetEventPause(float Time);

	/** ��, �� �޼ҵ� */
	void SwitchEventPause()
	{
		EventPause = !EventPause;
	}
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

	UTimeEvent TimeEventer;
};