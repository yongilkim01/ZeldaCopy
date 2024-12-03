#pragma once
#include <functional>
#include <map>
#include "EngineDebug.h"

/**
 *	설명
 */
class UFSMStateManager
{
public:
	/** 생성자, 소멸자 */
	UFSMStateManager() {	}
	~UFSMStateManager() {	}

	/** 객체 값 복사방지 */
	UFSMStateManager(const UFSMStateManager& _Other) = delete;
	UFSMStateManager(UFSMStateManager&& _Other) noexcept = delete;
	UFSMStateManager& operator=(const UFSMStateManager& _Other) = delete;
	UFSMStateManager& operator=(UFSMStateManager&& _Other) noexcept = delete;

	class FSMState
	{
	public:
		std::function<void()> StartFunction = nullptr;
		std::function<void(float)> UpdateFunction = nullptr;
		std::function<void()> EndFunction = nullptr;
	};

	template<typename EnumType>
	void CreateState(EnumType Key, std::function<void(float)> UpdateFunction, std::function<void()> Start = nullptr)
	{
		CreateState(static_cast<int>(Key), UpdateFunction, Start);
	}

	void CreateState(int Key, std::function<void(float)> UpdateFunction, std::function<void()> Start = nullptr)
	{
		if (true == States.contains(Key))
		{
			MSGASSERT("이미 존재하는 스테이트를 또 만들려고 했습니다.");
			return;
		}

		States[Key].UpdateFunction = UpdateFunction;
		States[Key].StartFunction = Start;
	}

	void Update(float DeltaTime)
	{
		if (nullptr == CurState)
		{
			return;
		}

		CurState->UpdateFunction(DeltaTime);
	}

	template<typename EnumType>
	void ChangeState(EnumType Key)
	{
		ChangeState(static_cast<int>(Key));
	}

	void Stop()
	{
		CurState = nullptr;
	}

	void ChangeState(int Key)
	{
		if (false == States.contains(Key))
		{
			MSGASSERT("만든적이 없는 스테이트로 체인지 하려고 했습니다.");
			return;
		}

		CurState = &States[Key];
		if (nullptr != CurState->StartFunction)
		{
			CurState->StartFunction();
		}
	}

protected:

private:
	FSMState* CurState = nullptr;
	std::map<int, FSMState> States;
};

