#include "PreCompile.h"
#include "RoomMove.h"

#include <EngineBase/EngineDebug.h>
#include <EnginePlatform/EngineWindow.h>
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

	if (MoveDir == FVector2D::ZERO)
	{
		MSGASSERT("URoomMove::MoveDir의 값의 0, 0 입니다.");
		return;
	}

	this->EntryLocation = EntryLocation;
	this->CurRoom = CurRoom;
	this->MoveRoom = MoveRoom;
	this->MoveDir = MoveDir;

	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half();

	if (this->MoveDir == FVector2D::RIGHT)
	{
		MoveSize = { WindowSize.X, 0.0f };
	}
	else if (this->MoveDir == FVector2D::LEFT)
	{
		MoveSize = { -WindowSize.X, 0.0f };
	}
	else if (this->MoveDir == FVector2D::UP)
	{
		MoveSize = { 0.0f, -WindowSize.Y };
	}
	else if (this->MoveDir == FVector2D::DOWN)
	{
		MoveSize = { 0.0f, WindowSize.Y };
	}

	this->ExitLocation = EntryLocation + MoveSize;
	//this->ExitLocation = this->ExitLocation + (UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half() * -1.0f);
}


URoomMove::~URoomMove()
{
}

