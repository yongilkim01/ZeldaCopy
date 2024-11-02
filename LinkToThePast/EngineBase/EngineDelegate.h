#pragma once
#include <functional>

/**
* 함수 포인터 리스트들을 관리하는 클래스
*/
class EngineDelegate
{
public:
	/** 생성자, 소멸자 */
	EngineDelegate();
	EngineDelegate(std::function<void()> Function) { Functions.push_back(Function); }
	~EngineDelegate();

	/** 연산자 */
	void operator+=(std::function<void()> _Function) { Functions.push_back(_Function);}
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

	/** 리스트 삭제 */
	void Clear() { Functions.clear(); }
	/** 함수들의 리스트가 비어져 있는지 여부를 반환 */
	bool IsBind() { return Functions.empty() == false; }
protected:

private:
	std::list<std::function<void()>> Functions;
};

