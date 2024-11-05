#pragma once
#include <EngineBase/EngineMath.h>
#include "Room.h"

// ���� :
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

	void SetMoveSize(FVector2D ChangeSize) { MoveSize = ChangeSize; }
	void SetMoveSize(float X, float Y) { MoveSize = { X, Y }; }
	void SetMoveSize(int X, int Y) { MoveSize = { X, Y }; }
	FVector2D GetMoveSize() { return MoveSize; }

	void SetEntryLocation(FVector2D Location) { EntryLocation = Location; }
	void SetEntryLocation(float X, float Y) { EntryLocation = { X, Y }; }
	void SetEntryLocation(int X, int Y) { EntryLocation = { X, Y }; }
	FVector2D GetEntryLocation() { return EntryLocation; }

	void SetExitLocation(FVector2D Location) { ExitLocation = Location; }
	void SetExitLocation(float X, float Y) { ExitLocation = { X, Y }; }
	void SetExitLocation(int X, int Y) { ExitLocation = { X, Y }; }
	FVector2D GetExitLocation() { return ExitLocation; }

	void SetCurRoom(ARoom* Room) { CurRoom = Room; }
	ARoom* GetCurRoom() { return CurRoom; }
	void SetMoveRoom(ARoom* Room) { MoveRoom = Room; }
	ARoom* GetMoveRoom() { return MoveRoom; }

protected:

private:
	FVector2D MoveDir = FVector2D::ZERO;
	FVector2D MoveSize = FVector2D::ZERO;
	FVector2D EntryLocation = FVector2D::ZERO;
	FVector2D ExitLocation = FVector2D::ZERO;

	ARoom* CurRoom = nullptr;
	ARoom* MoveRoom = nullptr;
};

