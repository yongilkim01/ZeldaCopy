#include "PreCompile.h"
#include "RoomMove.h"

#include <EngineBase/EngineDebug.h>
#include <EngineCore/EngineAPICore.h>

URoomMove::URoomMove()
{
}

URoomMove::URoomMove(FVector2D EntryLocation, ARoom* CurRoom, ARoom* MoveRoom, FVector2D MoveDir)
{
	if (CurRoom == nullptr || MoveRoom == nullptr)
	{
		MSGASSERT("URoomMove::CurRoom 또는 URoomMove::MoveRoom 이 null입니다.");
		return;
	}

	this->EntryLocation = EntryLocation;
	this->CurRoom = CurRoom;
	this->MoveRoom = MoveRoom;
	this->MoveDir = MoveDir;
}


URoomMove::~URoomMove()
{
}

