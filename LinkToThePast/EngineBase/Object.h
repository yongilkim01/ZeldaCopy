#pragma once
#include <string>

/**
 *	엔진 최상위 부모 클래스
 */
class UObject
{
public:
	/** 생성자, 소멸자 */
	UObject();
	virtual ~UObject();

	/** 객체 값 복사 방지 */
	UObject(const UObject& _Other) = delete;
	UObject(UObject&& _Other) noexcept = delete;
	UObject& operator=(const UObject& _Other) = delete;
	UObject& operator=(UObject&& _Other) noexcept = delete;

	virtual void SetName(std::string_view _Name) { Name = _Name.data(); }
	std::string GetName() const { return Name; }
	std::string_view GetNameView() const { return Name.c_str(); }

	// bool IsActive()
	virtual bool IsActive()
	{
		return IsActiveValue && false == IsDestroyValue;
	}
	virtual bool IsDestroy()
	{
		return IsDestroyValue;
	}
	// 바로 죽겠죠?
	// _Time 시간후에 죽어라.
	void Destroy(float _Time = 0.0f)
	{
		DeathTime = _Time;
		if (0.0f < _Time)
		{
			IsDeathTimeCheck = true;
			return;
		}
		IsDestroyValue = true;
	}
	virtual void ReleaseCheck(float _DeltaTime)
	{
		if (false == IsDeathTimeCheck)
		{
			return;
		}
		CurDeathTime += _DeltaTime;
		if (DeathTime <= CurDeathTime)
		{
			IsDestroyValue = true;
		}
	}

	virtual void ReleaseTimeCheck(float DeltaTime)
	{
		if (false == IsDeathTimeCheck)
		{
			return;
		}

		CurDeathTime += DeltaTime;

		if (DeathTime <= CurDeathTime)
		{
			IsDestroyValue = true;
		}
	}

	// 모든 기능 정지.
	// 얼음 외부에서 다른 객체가 풀어줘야 한다.
	void SetActive(bool IsActive)
	{
		IsActiveValue = IsActive;
	}

	void SetActiveSwitch()
	{
		IsActiveValue = !IsActiveValue;
	}

	bool IsDebug()
	{
		return IsDebugValue;
	}

	void DebugOn()
	{
		IsDebugValue = true;
	}

	void DebugOff()
	{
		IsDebugValue = false;
	}

	void DebugSwitch()
	{
		IsDebugValue = !IsDebugValue;
	}

	void TestDebugCheckOn()
	{
		TestDebugCheckValue = true;
	}

	void TestDebugCheck()
	{
		if (true == TestDebugCheckValue)
		{
			int a = 0;
		}
	}


protected:

private:
	bool IsDestroyValue = false;
	bool IsActiveValue = true;
	bool IsDeathTimeCheck = false;
	float DeathTime = 0.0f;
	float CurDeathTime = 0.0f;
	std::string Name;
	bool IsDebugValue = false;
	bool TestDebugCheckValue = false;
};

