#pragma once
#include <functional>

/**
* EngineDelete
* �Լ� ������ ����Ʈ���� �����ϴ� Ŭ����.
*/
class EngineDelegate
{
public:
	/** �Ϲ� ������ */
	EngineDelegate();
	/** ������ ���ڷ� ���޹��� _Function�� ����Ʈ�� �߰�. */
	EngineDelegate(std::function<void()> Function)
	{
		Functions.push_back(Function);
	}
	/** �Ҹ��� */
	~EngineDelegate();

	/** ������ */
	void operator+=(std::function<void()> _Function)
	{
		Functions.push_back(_Function);
	}

	void operator()()
	{
		std::list<std::function<void()>>::iterator StartIter = Functions.begin();
		std::list<std::function<void()>>::iterator EndIter = Functions.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			std::function<void()>& Function = *StartIter;
			Function();
		}
	}

	/** ����Ʈ ���� */
	void Clear() { Functions.clear(); }
	/** �Լ����� ����Ʈ�� ����� �ִ��� ���θ� ��ȯ */
	bool IsBind() { return Functions.empty() == false; }
protected:

private:
	std::list<std::function<void()>> Functions;
};

