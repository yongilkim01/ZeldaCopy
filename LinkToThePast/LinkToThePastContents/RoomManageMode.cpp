#include "PreCompile.h"
#include "RoomManageMode.h"
#include "Room.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "UserInterface.h"
#include "RoomMove.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>

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

	PlayerCharacter = GetWorld()->GetPawn<APlayer>();

}

void ARoomManageMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UEngineDebug::CoreOutPutString("  ");
	UEngineDebug::CoreOutPutString("CameraPos : " + GetWorld()->GetCameraPos().ToString());
	
	//RommesTick();

	if (ARoomManageMode::IsMapMoving == true)
	{
		FVector2D StartLocation = GetWorld()->GetCameraPos();
		FVector2D EndLocation = CurRoomMove->GetMoveRoom()->LeftTopPos;
		float CameraDistnace = CurRoomMove->GetDistance(GetWorld()->GetCameraPos(), CurRoomMove->GetCameraEndLocation());

		if (CameraDistnace >= 0.1f)
		{
			FVector2D LerpLocation = CurRoomMove->TranslateRoom(GetWorld()->GetCameraPos(), DeltaTime);
			GetWorld()->SetCameraPos(LerpLocation);
		}
		else
		{
			PlayerCharacter->SetActorLocation(CurRoomMove->GetExitLocation());
			PlayerCharacter->CurRoom->SetPlayer(nullptr);
			PlayerCharacter->CurRoom = CurRoomMove->GetMoveRoom();
			this->CurRoom = CurRoomMove->GetMoveRoom();
			ARoomManageMode::IsMapMoving = false;
		}
	}
	else
	{
		CheckMoveRoom();
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

bool ARoomManageMode::CheckRoomInPlayer(ARoom* CheckRoom)
{
	return (PlayerCharacter->GetActorLocation().iX() > CheckRoom->LeftTopPos.iX()
		&& PlayerCharacter->GetActorLocation().iY() > CheckRoom->LeftTopPos.iY()
		&& PlayerCharacter->GetActorLocation().iX() < CheckRoom->RightBottomPos.iX()
		&& PlayerCharacter->GetActorLocation().iY() < CheckRoom->RightBottomPos.iY());
}

void ARoomManageMode::CheckMoveRoom()
{
	if (PlayerCharacter->GetCurRoom() == nullptr)
	{
		MSGASSERT("플레이어의 현재 룸이 nullptr입니다.");
		return;
	}

	for (size_t i = 0; i < PlayerCharacter->GetCurRoom()->GetRoomMovesSize(); i++)
	{
		URoomMove* RoomMove = PlayerCharacter->GetCurRoom()->FindRoomMove(i);
		if (RoomMove->GetEntryLocation().iY() == PlayerCharacter->GetTransform().Location.iY())
		{
			ARoomManageMode::IsMapMoving = true;
			CurRoomMove = RoomMove;
		}
	}
}

ARoom* ARoomManageMode::FindRoomToName(std::string_view RoomName)
{
	for (int i = 0; i < RoomCount; i++)
	{
		if (Roomes[i]->GetName() == RoomName)
		{
			return Roomes[i];
		}
	}

	return nullptr;
}
void ARoomManageMode::CreateRoomActor(std::string_view _MapName)
{

	for (size_t i = 0; i < RoomDataes.size(); i++)
	{
		ARoom* DungeonRoom = GetWorld()->SpawnActor<ARoom>();
		DungeonName = _MapName;
		DungeonName.append(std::to_string(i + 1));
		std::string FileName = DungeonName + ".png";
		DungeonRoom->SetRoomSprite(FileName, ERenderOrder::BACKGROUND, RoomDataes[i].Location, 1.0f);
		DungeonRoom->SetRoomSize(RoomDataes[i].Scale);
		DungeonRoom->SetName(DungeonName);

		Roomes.push_back(DungeonRoom);
	}
}