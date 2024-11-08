#include "PreCompile.h"
#include "RoomManageMode.h"

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

	//CheckRoomCollision();

	// 현재 룸의 콜리전 이미지를 가져온다
	UEngineWinImage* RoomWinImage = CurRoom->GetColWinImage();
	CurRoomDir = ERoomDirection::NONE;

	if (RoomWinImage != nullptr)
	{
		// 현재 플레이어의 위치
		FVector2D PlayerLocation = PlayerCharacter->GetActorLocation();
		// 현재 플레이어의 위치에 있는 콜리전 색상
		UColor Color = RoomWinImage->GetColor(PlayerLocation);

		// 
		if (Color == UColor::ROOM_UP)
		{
			CurRoomDir = ERoomDirection::UP;
			MoveStart(CurRoomDir);
		}
		else if (Color == UColor::ROOM_DOWN)
		{
			CurRoomDir = ERoomDirection::DOWN;
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
		MoveSize = { UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().X, 0.0f };
		break;
	case ERoomDirection::LEFT:
		MoveSize = { (UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().X * -1.0f), 0.0f };
		break;
	case ERoomDirection::UP:
		MoveSize = { 0.0f, (UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Y * -1.0f) };
		break;
	case ERoomDirection::DOWN:
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
		case ERoomDirection::NONE:
			break;
		case ERoomDirection::RIGHT:
			CameraMovePosition = GetWorld()->GetCameraPos() + FVector2D(1.0f, 0.0f);
			GetWorld()->SetCameraPos(CameraMovePosition);
			break;
		case ERoomDirection::LEFT:
			CameraMovePosition = GetWorld()->GetCameraPos() + FVector2D(-1.0f, 0.0f);
			GetWorld()->SetCameraPos(CameraMovePosition);
			break;
		case ERoomDirection::UP:
			CameraMovePosition = GetWorld()->GetCameraPos() + FVector2D(0.0f, -0.5f);
			GetWorld()->SetCameraPos(CameraMovePosition);
			break;
		case ERoomDirection::DOWN:
			CameraMovePosition = GetWorld()->GetCameraPos() + FVector2D(0.0f, 0.5f);
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
	PlayerCharacter->AddActorLocation({ 0.0f, 293.0f });
	CheckCollisionRoom();
	RoomMoveState = ERoomMoveState::CHECK;
}

void ARoomManageMode::CreateRoomActor(std::string_view _MapName, int StartRoomIndex)
{
	for (size_t i = 0; i < RoomDataes.size(); i++)
	{
		ARoom* DungeonRoom = GetWorld()->SpawnActor<ARoom>();
		DungeonName = _MapName;
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
	if (Roomes.size() > 0) {
		for (int i = 0; i < Roomes.size(); i++)
		{
			if (CheckPlayerInRoom(Roomes[i]))
			{
				//PlayerCharacter->CurRoom->SetPlayer(nullptr);
				PlayerCharacter->SetCurRoom(Roomes[i]);
				this->CurRoom = Roomes[i];

			}
		}
	}
}
