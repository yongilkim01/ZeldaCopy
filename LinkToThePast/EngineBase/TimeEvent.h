#pragma once
#include <functional>

class TimeEventFunction
{
public:
	float Time = 0.0f;
	float MaxTime = 0.0f;
	std::function<void()> Event;
	bool IsUpdate = false;
	bool Loop = false;
};

/**
 *	����
 */
class UTimeEvent
{
public:
	/** ������, �Ҹ��� */
	UTimeEvent();
	~UTimeEvent();

	/** ��ü �� ���� ���� */
	UTimeEvent(const UTimeEvent& _Other) = delete;
	UTimeEvent(UTimeEvent&& _Other) noexcept = delete;
	UTimeEvent& operator=(const UTimeEvent& _Other) = delete;
	UTimeEvent& operator=(UTimeEvent&& _Other) noexcept = delete;

	void PushEvent(float Time, std::function<void()> Function, bool IsUpdate = false, bool IsLoop = false)
	{
		Events.push_front({ Time, Time, Function, IsUpdate, IsLoop });
	}

	void Update(float DeltaTime)
	{
		std::list<TimeEventFunction>::iterator StartIter = Events.begin();
		std::list<TimeEventFunction>::iterator EndIter = Events.end();

		for (; StartIter != EndIter;)
		{
			TimeEventFunction& TimeEvent = *StartIter;
			TimeEvent.Time -= DeltaTime;

			if (TimeEvent.IsUpdate && 0.0f < TimeEvent.Time == true)
			{
				TimeEvent.Event();
			}

			if (TimeEvent.Time <= 0.0f)
			{
				TimeEvent.Event();
				if (TimeEvent.Loop == false)
				{
					// TODO: ��Ȯ�� � ��������?
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

