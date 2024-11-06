#pragma once
#include "RoomManageMode.h"

// Ό³Έν :
class DungeonGameMode : public ARoomManageMode
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

