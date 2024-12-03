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
	UObject(const UObject& Other) = delete;
	UObject(UObject&& Other) noexcept = delete;
	UObject& operator=(const UObject& Other) = delete;
	UObject& operator=(UObject&& Other) noexcept = delete;

	virtual void SetName(std::string_view NewName) 
	{ 
		Name = NewName.data(); 
	}
	std::string GetName() const
	{ 
		return Name;
	}
	std::string_view GetNameView() const 
	{ 
		return Name.c_str(); 
	}

	virtual bool IsActive()
	{
		return IsActiveValue && false == IsDestroyValue;
	}
	virtual bool IsDestroy()
	{
		return IsDestroyValue;
	}

	void Destroy(float Time = 0.0f)
	{
		DeathTime = Time;
		if (0.0f < Time)
		{
			IsDeathTimeCheck = true;
			return;
		}
		IsDestroyValue = true;
	}

	virtual void ReleaseCheck(float DeltaTime)
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

