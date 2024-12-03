#pragma once
#include <functional>
#include <map>
#include "EngineDebug.h"

/**
 *	����
 */
class UFSMStateManager
{
public:
	/** ������, �Ҹ��� */
	UFSMStateManager() {	}
	~UFSMStateManager() {	}

	/** ��ü �� ������� */
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
			MSGASSERT("�̹� �����ϴ� ������Ʈ�� �� ������� �߽��ϴ�.");
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
			MSGASSERT("�������� ���� ������Ʈ�� ü���� �Ϸ��� �߽��ϴ�.");
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

