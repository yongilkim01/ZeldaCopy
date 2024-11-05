#pragma once
#include <functional>
#include <map>
#include "EngineDebug.h"

// ���� :
class UFSMStateManager
{
public:
	// constrcuter destructer
	UFSMStateManager() {	}
	~UFSMStateManager() {	}

	// delete Function
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
	void CreateState(EnumType _Key, std::function<void(float)> _UpdateFunction, std::function<void()> _Start = nullptr)
	{
		CreateState(static_cast<int>(_Key), _UpdateFunction, _Start);
	}

	void CreateState(int _Key, std::function<void(float)> _UpdateFunction, std::function<void()> _Start = nullptr)
	{
		if (true == States.contains(_Key))
		{
			MSGASSERT("�̹� �����ϴ� ������Ʈ�� �� ������� �߽��ϴ�.");
			return;
		}

		States[_Key].UpdateFunction = _UpdateFunction;
		States[_Key].StartFunction = _Start;
	}

	void Update(float _DeltaTime)
	{
		if (nullptr == CurState)
		{
			MSGASSERT("���°� �������� ���� ������Ʈ�ӽ� �Դϴ�.");
			return;
		}

		CurState->UpdateFunction(_DeltaTime);
	}

	template<typename EnumType>
	void ChangeState(EnumType _Key)
	{
		ChangeState(static_cast<int>(_Key));
	}

	void ChangeState(int _Key)
	{
		if (false == States.contains(_Key))
		{
			MSGASSERT("�������� ���� ������Ʈ�� ü���� �Ϸ��� �߽��ϴ�.");
			return;
		}

		CurState = &States[_Key];
		if (nullptr != CurState->StartFunction)
		{
			CurState->StartFunction();
		}
	}

protected:
	// ChangeState("Idle")
	// ChangeState(EPlayerState::Idle)
	// Idle ������Ʈ�� �̵�����

private:
	FSMState* CurState = nullptr;
	std::map<int, FSMState> States;
};

