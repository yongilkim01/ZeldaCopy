#include "PreCompile.h"
#include "EventManager.h"


UEventManager::UEventManager()
{
}


UEventManager::~UEventManager()
{
}

void UEventManager::EventTimeBeginPlay(float CheckTime)
{
	this->CheckTime = CheckTime;
}

void UEventManager::EventTimeTick(float DeltaTime)
{
	CurrentTime += DeltaTime;
	if (CheckTime < CurrentTime)
	{

	}
}