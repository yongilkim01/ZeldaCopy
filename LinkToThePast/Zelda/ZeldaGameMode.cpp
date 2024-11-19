#include "PreCompile.h"
#include "ZeldaGameMode.h"
#include "Room.h"
#include "ContentsEnum.h"
#include "PlayerCharacter.h"
#include "UserInterface.h"
#include "RoomMove.h"
#include "EnemyCharacter.h"

#include <EngineBase/EngineMath.h>

#include <EnginePlatform/EngineInput.h>
#include <EnginePlatform/EngineWinImage.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>

bool AZeldaGameMode::IsMapMoving = false;

AZeldaGameMode::AZeldaGameMode()
{

}

AZeldaGameMode::~AZeldaGameMode()
{
}

void AZeldaGameMode::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = GetWorld()->GetPawn<APlayerCharacter>();

}

void AZeldaGameMode::Tick(float DeltaTime)
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


void AZeldaGameMode::UIBeginPlay()
{
	UI = GetWorld()->SpawnActor<AUserInterface>();
	UI->SetPlayer(this->PlayerCharacter);
}

void AZeldaGameMode::UITick()
{

}

void AZeldaGameMode::CheckStart()
{

}

void AZeldaGameMode::CheckRoomMove()
{
	if (CurRoomDir != ERoomDirection::NONE)
	{
		return;
	}

	UEngineWinImage* RoomWinImage = nullptr;

	if (CurRoom->GetIsSecondFloor())
	{
		switch (PlayerCharacter->GetCurRoomFloor())
		{
		case ERoomFloor::FLOOR_1F:
			RoomWinImage = CurRoom->GetColWinImage1F();
			break;
		case ERoomFloor::FLOOR_2F:
			RoomWinImage = CurRoom->GetColWinImage2F();
			break;
		default:
			break;
		}
	}
	else
	{
		RoomWinImage = CurRoom->GetColWinImage1F();
	}

	// 현재 룸의 콜리전 이미지를 가져온다
	CurRoomDir = ERoomDirection::NONE;
	
	if (RoomWinImage != nullptr)
	{
		// 현재 플레이어의 위치
		FVector2D PlayerLocation = PlayerCharacter->GetActorLocation() - CurRoom->GetActorLocation();
		// 현재 플레이어의 위치에 있는 콜리전 색상
		UColor Color = RoomWinImage->GetColor(PlayerLocation);

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
		else if (Color == UColor::ROOM_RIGHT_SMALL)
		{
			CurRoomDir = ERoomDirection::RIGHT_SMALL;
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
		else if (Color == UColor::ROOM_LEFT_SMALL)
		{
			CurRoomDir = ERoomDirection::LEFT_SMALL;
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

void AZeldaGameMode::MoveStart(ERoomDirection RoomMoveDirection)
{
	FVector2D MoveSize = FVector2D::ZERO;

	switch (RoomMoveDirection)
	{
	case ERoomDirection::NONE:
		break;
	case ERoomDirection::RIGHT:
	case ERoomDirection::RIGHT_2F:
	case ERoomDirection::RIGHT_DIRECT:
	case ERoomDirection::RIGHT_SMALL:
		MoveSize = { UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().X, 0.0f };
		break;
	case ERoomDirection::LEFT:
	case ERoomDirection::LEFT_2F:
	case ERoomDirection::LEFT_DIRECT:
	case ERoomDirection::LEFT_SMALL:
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
	CameraStartLocation = GetWorld()->GetCameraLocation();
	CameraEndLocation = CameraStartLocation + MoveSize;
}

void AZeldaGameMode::MoveRoom()
{
	AZeldaGameMode::IsMapMoving = false;

	if (CurRoomDir != ERoomDirection::NONE)
	{
		AZeldaGameMode::IsMapMoving = true;
		FVector2D CameraMovePosition = FVector2D::ZERO;

		switch (CurRoomDir)
		{
		case ERoomDirection::RIGHT:
		case ERoomDirection::RIGHT_2F:
		case ERoomDirection::RIGHT_DIRECT:
		case ERoomDirection::RIGHT_SMALL:
			CameraMovePosition = GetWorld()->GetCameraLocation() + FVector2D(CameraMoveSpeed, 0.0f);
			GetWorld()->SetCameraLocation(CameraMovePosition);
			//PlayerCharacter->SetActorLocation(PlayerCharacter->GetActorLocation() + FVector2D(0.3f, 0.0f));
			if (CameraMovePosition.iX() > CameraEndLocation.iX())
			{
				EndStart();
			}
			break;
		case ERoomDirection::LEFT:
		case ERoomDirection::LEFT_2F:
		case ERoomDirection::LEFT_DIRECT:
		case ERoomDirection::LEFT_SMALL:
			CameraMovePosition = GetWorld()->GetCameraLocation() + FVector2D(-CameraMoveSpeed, 0.0f);
			GetWorld()->SetCameraLocation(CameraMovePosition);
			//PlayerCharacter->SetActorLocation(PlayerCharacter->GetActorLocation() + FVector2D(-0.3f, 0.0f));
			if (CameraMovePosition.iX() < CameraEndLocation.iX())
			{
				EndStart();
			}
			break;
		case ERoomDirection::UP:
		case ERoomDirection::UP_2F:
		case ERoomDirection::UP_DIRECT:
			CameraMovePosition = GetWorld()->GetCameraLocation() + FVector2D(0.0f, -CameraMoveSpeed);
			GetWorld()->SetCameraLocation(CameraMovePosition);
			if (CameraMovePosition.iY() < CameraEndLocation.iY())
			{
				EndStart();
			}
			break;
		case ERoomDirection::DOWN:
		case ERoomDirection::DOWN_2F:
		case ERoomDirection::DOWN_DIRECT:
			CameraMovePosition = GetWorld()->GetCameraLocation() + FVector2D(0.0f, CameraMoveSpeed);
			GetWorld()->SetCameraLocation(CameraMovePosition);
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

void AZeldaGameMode::EndStart()
{
	RoomMoveState = ERoomMoveState::END;
}

void AZeldaGameMode::EndRoomMove()
{
	AZeldaGameMode::IsMapMoving = false;
	CameraStartLocation = FVector2D::ZERO;
	CameraEndLocation = FVector2D::ZERO;
	RoomMoveState = ERoomMoveState::CHECK;

	float RightLeftPadding = 160.0f;
	float UpDownPadding = 180.0f;
	
	FVector2D MoveSize = FVector2D::ZERO;

	switch (CurRoomDir)
	{
	case ERoomDirection::NONE:
		break;
	case ERoomDirection::RIGHT:
		MoveSize = { 
			UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half().X + RoomMovePadding - RightLeftPadding,
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
	case ERoomDirection::RIGHT_SMALL:
		MoveSize = {
			SmallMoveDistance - RightLeftPadding,
			0.0f };
		PlayerCharacter->SetActorLocation(PlayerCharacter->GetActorLocation() + MoveSize);
		break;
	case ERoomDirection::LEFT:
		MoveSize = {
			( (UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half().X) * -1.0f) - RoomMovePadding + RightLeftPadding,
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
	case ERoomDirection::LEFT_SMALL:
		MoveSize = {
			-SmallMoveDistance + RightLeftPadding,
			0.0f };
		PlayerCharacter->SetActorLocation(PlayerCharacter->GetActorLocation() + MoveSize);
		break;
	case ERoomDirection::UP:
		MoveSize = {
			0.0f, 
			(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half().Y * -1.0f) + UpDownPadding };
		PlayerCharacter->SetActorLocation(PlayerCharacter->GetActorLocation() + MoveSize);
		break;
	case ERoomDirection::UP_2F:
		MoveSize = {
			0.0f,
			((UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half().Y * -1.0f) * RoomSizeRatio) + UpDownPadding };
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
			(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half().Y) - UpDownPadding };
		PlayerCharacter->SetActorLocation(PlayerCharacter->GetActorLocation() + MoveSize);	
		break;
	case ERoomDirection::DOWN_2F:
		MoveSize = { 
			0.0f,
			(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half().Y * RoomSizeRatio ) - UpDownPadding };
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

void AZeldaGameMode::CreateRoomActor(std::string_view MapName, int StartRoomIndex)
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

ARoom* AZeldaGameMode::FindRoomToName(std::string_view RoomName)
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

void AZeldaGameMode::SetCurRoom(int _Index)
{
	PlayerCharacter->SetCurRoom(Roomes[_Index], true);
	this->CurRoom = Roomes[_Index];
}

void AZeldaGameMode::CheckCollisionRoom()
{
	if (Roomes.size() == 0)
	{
		MSGASSERT("초기화 된 룸이 없습니다.");
		return;
	}

	for (int i = 0; i < Roomes.size(); i++)
	{
		if (CheckPlayerInRoom(Roomes[i]))
		{
			PlayerCharacter->SetCurRoom(Roomes[i], true);
			this->CurRoom = Roomes[i];
			return;

		}
	}
}

bool AZeldaGameMode::CheckPlayerInRoom(ARoom* CheckRoom)
{
	return (PlayerCharacter->GetActorLocation().iX() > CheckRoom->LeftTopPos.iX()
		&& PlayerCharacter->GetActorLocation().iY() > CheckRoom->LeftTopPos.iY()
		&& PlayerCharacter->GetActorLocation().iX() < CheckRoom->RightBottomPos.iX()
		&& PlayerCharacter->GetActorLocation().iY() < CheckRoom->RightBottomPos.iY());
}

void AZeldaGameMode::CheckCharacterInRoom(ABaseCharacter* Character)
{
	if (Roomes.size() == 0)
	{
		MSGASSERT("초기화 된 룸이 없습니다.");
		return;
	}

	for (int i = 0; i < Roomes.size(); i++)
	{
		if (Character->GetActorLocation().iX() > Roomes[i]->LeftTopPos.iX()
			&& Character->GetActorLocation().iY() > Roomes[i]->LeftTopPos.iY()
			&& Character->GetActorLocation().iX() < Roomes[i]->RightBottomPos.iX()
			&& Character->GetActorLocation().iY() < Roomes[i]->RightBottomPos.iY())
		{
			Character->SetCurRoom(Roomes[i], false);
			return;

		}
	}
}
