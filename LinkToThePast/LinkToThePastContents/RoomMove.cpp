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
		MSGASSERT("URoomMove::CurRoom �Ǵ� URoomMove::MoveRoom �� null�Դϴ�.");
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

