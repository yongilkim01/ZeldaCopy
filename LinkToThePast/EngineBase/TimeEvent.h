#pragma once
#include <functional>

class TimeEventFunction
{
public:
	float Time = 0.0f;
	float MaxTime = 0.0f;
	std::function<void()> Event;
	bool Loop = false;
};

/**
 *	설명
 */
class UTimeEvent
{
public:
	/** 생성자, 소멸자 */
	UTimeEvent();
	~UTimeEvent();

	/** 객체 값 복사 방지 */
	UTimeEvent(const UTimeEvent& _Other) = delete;
	UTimeEvent(UTimeEvent&& _Other) noexcept = delete;
	UTimeEvent& operator=(const UTimeEvent& _Other) = delete;
	UTimeEvent& operator=(UTimeEvent&& _Other) noexcept = delete;

	void PushEvent(float Time, std::function<void()> Function, bool IsLoop = false)
	{
		Events.push_front({ Time, Time, Function, IsLoop });
	}

	void Update(float DeltaTime)
	{
		std::list<TimeEventFunction>::iterator StartIter = Events.begin();
		std::list<TimeEventFunction>::iterator EndIter = Events.end();

		for (; StartIter != EndIter;)
		{
			TimeEventFunction& TimeEvent = *StartIter;
			TimeEvent.Time -= DeltaTime;

			if (TimeEvent.Time <= 0.0f)
			{
				TimeEvent.Event();
				if (TimeEvent.Loop == false)
				{
					// TODO: 정확히 어떤 동작이지?
					StartIter = Events.erase(StartIter);
				}
				else
				{
					StartIter++;
					TimeEvent.Time = TimeEvent.MaxTime;
				}
			}
			else
			{
				StartIter++;
			}
		}
	}

protected:

private:
	std::list<TimeEventFunction> Events;
};

