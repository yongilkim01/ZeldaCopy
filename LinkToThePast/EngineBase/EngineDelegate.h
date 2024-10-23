#pragma once
#include <functional>

/**
* EngineDelete
* 함수 포인터 리스트들을 관리하는 클래스.
*/
class EngineDelegate
{
public:
	// constrcuter destructer
	EngineDelegate();

	/** 생성자 인자로 전달받은 _Function을 리스트에 추가. */
	EngineDelegate(std::function<void()> _Function)
	{
		Functions.push_back(_Function);
	}

	~EngineDelegate();

	// delete Function
	//EngineDelegate(const EngineDelegate& _Other) = delete;
	//EngineDelegate(EngineDelegate&& _Other) noexcept = delete;
	//EngineDelegate& operator=(const EngineDelegate& _Other) = delete;
	//EngineDelegate& operator=(EngineDelegate&& _Other) noexcept = delete;

	/** 함수들의 리스트가 비어져 있는지 여부를 반환 */
	bool IsBind()
	{
		return false == Functions.empty();
	}

	/** 할당 연산자 */
	void operator=(std::function<void()> _Function)
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

	void Clear()
	{
		Functions.clear();
	}

protected:

private:
	std::list<std::function<void()>> Functions;
};

