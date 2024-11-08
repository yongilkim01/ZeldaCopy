#include "PreCompile.h"
#include "RoomMove.h"

#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineMath.h>

#include <EnginePlatform/EngineWindow.h>

#include <EngineCore/EngineAPICore.h>

#include <cmath>

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
	this->CameraEndLocation = ExitLocation + (WindowSize * -1.0f);
	this->CameraEndLocation.X = 0.0f;
	this->CameraEndLocation.Y = MoveRoom->LeftTopPos.Y;

	//this->ExitLocation = this->ExitLocation + (UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half() * -1.0f);
}


URoomMove::~URoomMove()
{
}

FVector2D URoomMove::TranslateRoom(FVector2D StartLocation, float DeltaTime)
{
	float Distance = DeltaTime * Speed;

	return { 0.0f , StartLocation.Y + Distance };

	//FVector2D CurCameraPos = GetWorld()->GetCameraPos();
	//GetWorld()->SetCameraPos(CurCameraPos + (CurRoomMove->GetMoveDir() * DeltaTime * 300.0f));
	//CurCameraPos = GetWorld()->GetCameraPos();
	////FVector2D

	//if (CurRoomMove->GetMoveDir() == FVector2D::RIGHT)
	//{
	//	if (CurCameraPos.iX() > GolLocation.iX())
	//	{
	//		GetWorld()->SetCameraPos({ GolLocation.X, CurCameraPos.Y });
	//		ARoomManageMode::IsMapMoving = false;
	//		PlayerCharacter->CurRoom->SetPlayer(nullptr);
	//		PlayerCharacter->CurRoom = MoveRoom;
	//		this->CurRoom = MoveRoom;

	//		GolLocation = FVector2D::ZERO;
	//		CurRoomMove = nullptr;
	//	}
	//}
	//else if (CurRoomMove->GetMoveDir() == FVector2D::LEFT)
	//{
	//	if (CurCameraPos.iX() < GolLocation.iX())
	//	{
	//		GetWorld()->SetCameraPos({ GolLocation.X, CurCameraPos.Y });
	//		ARoomManageMode::IsMapMoving = false;
	//		PlayerCharacter->CurRoom->SetPlayer(nullptr);
	//		PlayerCharacter->CurRoom = MoveRoom;
	//		this->CurRoom = MoveRoom;

	//		GolLocation = FVector2D::ZERO;
	//		CurRoomMove = nullptr;
	//	}
	//}
	//else if (CurRoomMove->GetMoveDir() == FVector2D::UP)
	//{
	//	if (CurCameraPos.iY() < GolLocation.iY())
	//	{
	//		GetWorld()->SetCameraPos({ CurCameraPos.X, GolLocation.Y });
	//		ARoomManageMode::IsMapMoving = false;
	//		PlayerCharacter->CurRoom->SetPlayer(nullptr);
	//		PlayerCharacter->CurRoom = MoveRoom;
	//		this->CurRoom = MoveRoom;

	//		GolLocation = FVector2D::ZERO;
	//		CurRoomMove = nullptr;
	//	}
	//}
	//else if (CurRoomMove->GetMoveDir() == FVector2D::DOWN)
	//{
	//	int CurY = CurCameraPos.iY();
	//	int ExitY = GolLocation.iY();

	//	if (CurCameraPos.iY() > GolLocation.iY())
	//	{
	//		GetWorld()->SetCameraPos({ CurCameraPos.X, GolLocation.Y });
	//		ARoomManageMode::IsMapMoving = false;
	//		PlayerCharacter->CurRoom->SetPlayer(nullptr);
	//		PlayerCharacter->CurRoom = Roomes[1];
	//		PlayerCharacter->AddActorLocation(CurRoomMove->GetMoveSize());
	//		PlayerCharacter->AddActorLocation({ 0, 15 });
	//		this->CurRoom = Roomes[1];

	//		GolLocation = FVector2D::ZERO;
	//		CurRoomMove = nullptr;
	//	}
	//}
}

float URoomMove::GetDistance(FVector2D StartLocation, FVector2D EndLocation)
{
	if (GetMoveDir() == FVector2D::RIGHT)
	{
		return EndLocation.X - StartLocation.X;
	}
	else if (GetMoveDir() == FVector2D::LEFT)
	{
		return StartLocation.X - EndLocation.X;
	}
	else if (GetMoveDir() == FVector2D::UP)
	{
		return StartLocation.Y - EndLocation.Y;
	}
	else if (GetMoveDir() == FVector2D::DOWN)
	{
		return EndLocation.Y - StartLocation.Y;
	}

	return 0.0f;
}
