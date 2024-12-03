#pragma once
#include <Windows.h>

/**
 *	���� �ð� Ŭ���� 
 */
class UEngineTimer
{
public:
	/** ������, �Ҹ��� */
	UEngineTimer();
	~UEngineTimer();

	/** ��ü �� ���� ���� */
	UEngineTimer(const UEngineTimer& Other) = delete;
	UEngineTimer(UEngineTimer&& Other) noexcept = delete;
	UEngineTimer& operator=(const UEngineTimer& Other) = delete;
	UEngineTimer& operator=(UEngineTimer&& Other) noexcept = delete;

	void TimeCheck();
	float GetDeltaTime() 
	{ 
		return fDeltaTime; 
	}
	double GetDoubleDeltaTime()
	{ 
		return DeltaTime;
	}
	void TimeStart();
	float End();
	double DEnd();

protected:

private:
	LARGE_INTEGER Count = LARGE_INTEGER();
	LARGE_INTEGER PrevTime = LARGE_INTEGER();
	LARGE_INTEGER CurTime = LARGE_INTEGER();

	double TimeCounter = 0.0f;
	double DeltaTime = 0.0;
	float fDeltaTime = 0.0f;
};

