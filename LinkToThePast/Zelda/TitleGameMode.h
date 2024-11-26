#pragma once
#include <EngineCore/GameMode.h>
#include <EngineBase/TimeEvent.h>

class ATitleManager;

// Ό³Έν :
class ATitleGameMode : public AGameMode
{
public:
	// constrcuter destructer
	ATitleGameMode();
	~ATitleGameMode();

	// delete Function
	ATitleGameMode(const ATitleGameMode& _Other) = delete;
	ATitleGameMode(ATitleGameMode&& _Other) noexcept = delete;
	ATitleGameMode& operator=(const ATitleGameMode& _Other) = delete;
	ATitleGameMode& operator=(ATitleGameMode&& _Other) noexcept = delete;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	float CurTime = 0.0f;
	ATitleManager* ManagerActor = nullptr;
	UTimeEvent TimeEventer;
};

