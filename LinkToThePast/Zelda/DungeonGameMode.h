#pragma once
#include "ZeldaGameMode.h"

// Ό³Έν :
class ACastleDungeonGameMode : public AZeldaGameMode
{
public:
	// constrcuter destructer
	ACastleDungeonGameMode();
	~ACastleDungeonGameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void RoomBeginPlay();

	// delete Function
	ACastleDungeonGameMode(const ACastleDungeonGameMode& _Other) = delete;
	ACastleDungeonGameMode(ACastleDungeonGameMode&& _Other) noexcept = delete;
	ACastleDungeonGameMode& operator=(const ACastleDungeonGameMode& _Other) = delete;
	ACastleDungeonGameMode& operator=(ACastleDungeonGameMode&& _Other) noexcept = delete;

protected:

private:

};

