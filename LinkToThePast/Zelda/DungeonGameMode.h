#pragma once
#include "ZeldaGameMode.h"

// Ό³Έν :
class DungeonGameMode : public AZeldaGameMode
{
public:
	// constrcuter destructer
	DungeonGameMode();
	~DungeonGameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void RoomBeginPlay();

	// delete Function
	DungeonGameMode(const DungeonGameMode& _Other) = delete;
	DungeonGameMode(DungeonGameMode&& _Other) noexcept = delete;
	DungeonGameMode& operator=(const DungeonGameMode& _Other) = delete;
	DungeonGameMode& operator=(DungeonGameMode&& _Other) noexcept = delete;

protected:

private:

};

