#include "PreCompile.h"
#include "RoomManageMode.h"

#include <EngineBase/EngineMath.h>

#include <EnginePlatform/EngineInput.h>
#include <EnginePlatform/EngineWinImage.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>

#include "Room.h"
#include "ContentsEnum.h"
#include "PlayerCharacter.h"
#include "UserInterface.h"
#include "RoomMove.h"

bool ARoomManageMode::IsMapMoving = false;

ARoomManageMode::ARoomManageMode()
{

}

ARoomManageMode::~ARoomManageMode()
{
}

void ARoomManageMode::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = GetWorld()->GetPawn<APlayerCharacter>();

}

void ARoomManageMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurRoom == nullptr)
	{
		MSGASSERT("현재 룸이 존재하지 않습니다.");
		return;
	}

	switch (RoomMoveState)
	{
	case ERoomMoveState::CHECK:
		CheckRoomMove();
		break;
	case ERoomMoveState::MOVE:
		MoveRoom();
		break;
	case ERoomMoveState::END:
		EndRoomMove();
		break;
	default:
		break;
	}
}


void ARoomManageMode::UIBeginPlay()
{
	UI = GetWorld()->SpawnActor<AUserInterface>();
	UI->SetPlayer(this->PlayerCharacter);
}

void ARoomManageMode::UITick()
{

}

void ARoomManageMode::CheckStart()
{

}

void ARoomManageMode::CheckRoomMove()
{
	if (CurRoomDir != ERoomDirection::NONE)
	{
		return;
	}

	// 현재 룸의 콜리전 이미지를 가져온다
	UEngineWinImage* RoomWinImage = CurRoom->GetColWinImage();
	CurRoomDir = ERoomDirection::NONE;
	
	if (RoomWinImage != nullptr)
	{
		// 현재 플레이어의 위치
		FVector2D PlayerLocation = PlayerCharacter->GetActorLocation() - CurRoom->GetActorLocation();
		// 현재 플레이어의 위치에 있는 콜리전 색상
		UColor Color = RoomWinImage->GetColor(PlayerLocation);

		UEngineDebug::CoreOutPutString("Current RGB : " + Color.ToString());
		UEngineDebug::CoreOutPutString("Current Room Name : " + CurRoom->GetName());
		UEngineDebug::CoreOutPutString("Current Room Collision Name : " + RoomWinImage->GetName());

		if (Color == UColor::ROOM_RIGHT)
		{
			CurRoomDir = ERoomDirection::RIGHT;
			MoveStart(CurRoomDir);
		}
		else if (Color == UColor::ROOM_RIGHT_2F)
		{
			CurRoomDir = ERoomDirection::RIGHT_2F;
			MoveStart(CurRoomDir);
		}
		else if (Color == UColor::ROOM_RIGHT_DIRECT)
		{
			CurRoomDir = ERoomDirection::RIGHT_DIRECT;
			MoveStart(CurRoomDir);
		}
		else if (Color == UColor::ROOM_LEFT)
		{
			CurRoomDir = ERoomDirection::LEFT;
			MoveStart(CurRoomDir);
		}
		else if (Color == UColor::ROOM_LEFT_2F)
		{
			CurRoomDir = ERoomDirection::LEFT_2F;
			MoveStart(CurRoomDir);
		}
		else if (Color == UColor::ROOM_LEFT_DIRECT)
		{
			CurRoomDir = ERoomDirection::LEFT_DIRECT;
			MoveStart(CurRoomDir);
		}
		else if (Color == UColor::ROOM_UP)
		{
			CurRoomDir = ERoomDirection::UP;
			MoveStart(CurRoomDir);
		}
		else if (Color == UColor::ROOM_UP_2F)
		{
			CurRoomDir = ERoomDirection::UP_2F;
			MoveStart(CurRoomDir);
		}
		else if (Color == UColor::ROOM_UP_DIRECT)
		{
			CurRoomDir = ERoomDirection::UP_DIRECT;
			MoveStart(CurRoomDir);
		}
		else if (Color == UColor::ROOM_DOWN)
		{
			CurRoomDir = ERoomDirection::DOWN;
			MoveStart(CurRoomDir);
		}
		else if (Color == UColor::ROOM_DOWN_2F)
		{
			CurRoomDir = ERoomDirection::DOWN_2F;
			MoveStart(CurRoomDir);
		}
		else if (Color == UColor::ROOM_DOWN_DIRECT)
		{
			CurRoomDir = ERoomDirection::DOWN_DIRECT;
			MoveStart(CurRoomDir);
		}
	}
}

void ARoomManageMode::MoveStart(ERoomDirection RoomMoveDirection)
{
	FVector2D MoveSize = FVector2D::ZERO;

	switch (RoomMoveDirection)
	{
	case ERoomDirection::NONE:
		break;
	case ERoomDirection::RIGHT:
	case ERoomDirection::RIGHT_2F:
	case ERoomDirection::RIGHT_DIRECT:
		MoveSize = { UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().X, 0.0f };
		break;
	case ERoomDirection::LEFT:
	case ERoomDirection::LEFT_2F:
	case ERoomDirection::LEFT_DIRECT:
		MoveSize = { (UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().X * -1.0f), 0.0f };
		break;
	case ERoomDirection::UP:
	case ERoomDirection::UP_2F:
	case ERoomDirection::UP_DIRECT:
		MoveSize = { 0.0f, UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Y * -1.0f };
		break;
	case ERoomDirection::DOWN:
	case ERoomDirection::DOWN_2F:
	case ERoomDirection::DOWN_DIRECT:
		MoveSize = { 0.0f, UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Y };
		break;
	default:
		break;
	}

	CurRoomDir = RoomMoveDirection;
	RoomMoveState = ERoomMoveState::MOVE;
	CameraStartLocation = GetWorld()->GetCameraPos();
	CameraEndLocation = CameraStartLocation + MoveSize;
}

void ARoomManageMode::MoveRoom()
{
	ARoomManageMode::IsMapMoving = false;

	if (CurRoomDir != ERoomDirection::NONE)
	{
		ARoomManageMode::IsMapMoving = true;
		FVector2D CameraMovePosition = FVector2D::ZERO;

		switch (CurRoomDir)
		{
		case ERoomDirection::RIGHT:
		case ERoomDirection::RIGHT_2F:
		case ERoomDirection::RIGHT_DIRECT:
			CameraMovePosition = GetWorld()->GetCameraPos() + FVector2D(CameraMoveSpeed, 0.0f);
			GetWorld()->SetCameraPos(CameraMovePosition);
			if (CameraMovePosition.iX() > CameraEndLocation.iX())
			{
				EndStart();
			}
			break;
		case ERoomDirection::LEFT:
		case ERoomDirection::LEFT_2F:
		case ERoomDirection::LEFT_DIRECT:
			CameraMovePosition = GetWorld()->GetCameraPos() + FVector2D(-CameraMoveSpeed, 0.0f);
			GetWorld()->SetCameraPos(CameraMovePosition);
			if (CameraMovePosition.iX() < CameraEndLocation.iX())
			{
				EndStart();
			}
			break;
		case ERoomDirection::UP:
		case ERoomDirection::UP_2F:
		case ERoomDirection::UP_DIRECT:
			CameraMovePosition = GetWorld()->GetCameraPos() + FVector2D(0.0f, -CameraMoveSpeed);
			GetWorld()->SetCameraPos(CameraMovePosition);
			if (CameraMovePosition.iY() < CameraEndLocation.iY())
			{
				EndStart();
			}
			break;
		case ERoomDirection::DOWN:
		case ERoomDirection::DOWN_2F:
		case ERoomDirection::DOWN_DIRECT:
			CameraMovePosition = GetWorld()->GetCameraPos() + FVector2D(0.0f, CameraMoveSpeed);
			GetWorld()->SetCameraPos(CameraMovePosition);
			if (CameraMovePosition.iY() > CameraEndLocation.iY())
			{
				EndStart();
			}
			break;
		default:
			break;
		}
	}
}

void ARoomManageMode::EndStart()
{
	RoomMoveState = ERoomMoveState::END;
}

void ARoomManageMode::EndRoomMove()
{
	ARoomManageMode::IsMapMoving = false;
	CameraStartLocation = FVector2D::ZERO;
	CameraEndLocation = FVector2D::ZERO;
	RoomMoveState = ERoomMoveState::CHECK;
	
	FVector2D MoveSize = FVector2D::ZERO;

	switch (CurRoomDir)
	{
	case ERoomDirection::NONE:
		break;
	case ERoomDirection::RIGHT:
		MoveSize = { 
			UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half().X + RoomMovePadding, 
			0.0f };
		PlayerCharacter->SetActorLocation(PlayerCharacter->GetActorLocation() + MoveSize);
		break;
	case ERoomDirection::RIGHT_2F:
		MoveSize = {
			(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half().X + RoomMovePadding) * RoomSizeRatio,
			0.0f };
		PlayerCharacter->SetActorLocation(PlayerCharacter->GetActorLocation() + MoveSize);
		break;
	case ERoomDirection::RIGHT_DIRECT:
		MoveSize = {
			DirectMoveDistance,
			0.0f};
		PlayerCharacter->SetActorLocation(PlayerCharacter->GetActorLocation() + MoveSize);
		break;
	case ERoomDirection::LEFT:
		MoveSize = {
			( (UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half().X) * -1.0f) - RoomMovePadding, 
			0.0f };
		PlayerCharacter->SetActorLocation(PlayerCharacter->GetActorLocation() + MoveSize);
		break;
	case ERoomDirection::LEFT_2F:
		MoveSize = {
			(((UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half().X) * -1.0f) - RoomMovePadding) * RoomSizeRatio,
			0.0f };
		PlayerCharacter->SetActorLocation(PlayerCharacter->GetActorLocation() + MoveSize);
		break;
	case ERoomDirection::LEFT_DIRECT:
		MoveSize = {
			-DirectMoveDistance,
			0.0f};
		PlayerCharacter->SetActorLocation(PlayerCharacter->GetActorLocation() + MoveSize);
		break;
	case ERoomDirection::UP:
		MoveSize = {
			0.0f, 
			UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half().Y * -1.0f };
		PlayerCharacter->SetActorLocation(PlayerCharacter->GetActorLocation() + MoveSize);
		break;
	case ERoomDirection::UP_2F:
		MoveSize = {
			0.0f,
			(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half().Y * -1.0f) * RoomSizeRatio };
		PlayerCharacter->SetActorLocation(PlayerCharacter->GetActorLocation() + MoveSize);
		break;
	case ERoomDirection::UP_DIRECT:
		MoveSize = {
			0.0f,
			-DirectMoveDistance };
		PlayerCharacter->SetActorLocation(PlayerCharacter->GetActorLocation() + MoveSize);
		break;
	case ERoomDirection::DOWN:
		MoveSize = {
			0.0f,
			UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half().Y };
		PlayerCharacter->SetActorLocation(PlayerCharacter->GetActorLocation() + MoveSize);	
		break;
	case ERoomDirection::DOWN_2F:
		MoveSize = { 
			0.0f,
			UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half().Y * RoomSizeRatio };
		PlayerCharacter->SetActorLocation(PlayerCharacter->GetActorLocation() + MoveSize);
		break;
	case ERoomDirection::DOWN_DIRECT	:
		MoveSize = {
			0.0f,
			DirectMoveDistance };
		PlayerCharacter->SetActorLocation(PlayerCharacter->GetActorLocation() + MoveSize);
		break;
	default:
		break;
	}
	CheckCollisionRoom();
	CurRoomDir = ERoomDirection::NONE;
}

void ARoomManageMode::CreateRoomActor(std::string_view MapName, int StartRoomIndex)
{
	for (size_t i = 0; i < RoomDataes.size(); i++)
	{
		ARoom* DungeonRoom = GetWorld()->SpawnActor<ARoom>();
		std::string DungeonName = MapName.data();
		DungeonName.append(std::to_string(i + 1));
		std::string SpriteName = DungeonName + ".png";
		std::string CollisionSpriteName = DungeonName + "Collision.png";
		DungeonRoom->SetRoomSprite(SpriteName, CollisionSpriteName, ERenderOrder::BACKGROUND, RoomDataes[i].Location, 1.0f);
		DungeonRoom->SetRoomSize(RoomDataes[i].Scale);
		DungeonRoom->SetName(DungeonName);

		Roomes.push_back(DungeonRoom);
	}

	SetCurRoom(StartRoomIndex);
}

ARoom* ARoomManageMode::FindRoomToName(std::string_view RoomName)
{
	for (size_t i = 0; i < Roomes.size(); i++)
	{
		if (Roomes[i]->GetName() == RoomName)
		{
			return Roomes[i];
		}
	}

	return nullptr;
}

void ARoomManageMode::SetCurRoom(int _Index)
{
	PlayerCharacter->SetCurRoom(Roomes[_Index]);
	this->CurRoom = Roomes[_Index];
}

bool ARoomManageMode::CheckPlayerInRoom(ARoom* CheckRoom)
{
	return (PlayerCharacter->GetActorLocation().iX() > CheckRoom->LeftTopPos.iX()
		&& PlayerCharacter->GetActorLocation().iY() > CheckRoom->LeftTopPos.iY()
		&& PlayerCharacter->GetActorLocation().iX() < CheckRoom->RightBottomPos.iX()
		&& PlayerCharacter->GetActorLocation().iY() < CheckRoom->RightBottomPos.iY());
}

void ARoomManageMode::CheckCollisionRoom()
{
	if (Roomes.size() > 0)
	{
		for (int i = 0; i < Roomes.size(); i++)
		{
			if (CheckPlayerInRoom(Roomes[i]))
			{
				int TestIndex = i;
				//PlayerCharacter->CurRoom->SetPlayer(nullptr);
				PlayerCharacter->SetCurRoom(Roomes[i]);
				PlayerCharacter->SetCollisionImage(Roomes[i]->GetColWinImage()->GetName());
				this->CurRoom = Roomes[i];
				return;

			}
		}
	}
}
