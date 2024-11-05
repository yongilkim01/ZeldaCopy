#pragma once
#include <EngineBase/EngineMath.h>
#include "Room.h"

// Ό³Έν :
class URoomMove
{
public:
	// constrcuter destructer
	URoomMove();
	URoomMove(FVector2D EntryLocation, ARoom* CurRoom, ARoom* MoveRoom, FVector2D MoveDir);
	~URoomMove();

	// delete Function
	URoomMove(const URoomMove& _Other) = delete;
	URoomMove(URoomMove&& _Other) noexcept = delete;
	URoomMove& operator=(const URoomMove& _Other) = delete;
	URoomMove& operator=(URoomMove&& _Other) noexcept = delete;

	void SetMoveDir(FVector2D ChangeDir) { MoveDir = ChangeDir; }
	void SetMoveDir(float X, float Y) { MoveDir = { X, Y }; }
	void SetMoveDir(int X, int Y) { MoveDir = { X, Y }; }
	FVector2D GetMoveDir() { return MoveDir; }

	void SetEntryLocation(FVector2D Location) { EntryLocation = Location; }
	void SetEntryLocation(float X, float Y) { EntryLocation = { X, Y }; }
	void SetEntryLocation(int X, int Y) { EntryLocation = { X, Y }; }
	FVector2D GetEntryLocation() { return EntryLocation; }

	void SetCurRoom(ARoom* Room) { CurRoom = Room; }
	ARoom* GetCurRoom() { return CurRoom; }
	void SetMoveRoom(ARoom* Room) { MoveRoom = Room; }
	ARoom* GetMoveRoom() { return MoveRoom; }

protected:

private:
	FVector2D MoveDir = FVector2D::ZERO;
	FVector2D EntryLocation = FVector2D::ZERO;

	ARoom* CurRoom = nullptr;
	ARoom* MoveRoom = nullptr;
};

