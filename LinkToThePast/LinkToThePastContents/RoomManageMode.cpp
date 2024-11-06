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

	RoomesBeginPlay();
	UIBeginPlay();

	PlayerCharacter->CurRoom = Roomes[0];
	this->CurRoom = Roomes[0];
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
		//float CameraDistnace = GetWorld()->GetCameraPos().DistanceTo(CurRoomMove->GetCameraEndLocation());
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

void ARoomManageMode::RoomesBeginPlay()
{
	Roomes.reserve(10);
	RoomLocations.reserve(10);
	RoomSizes.reserve(10);

	RoomLocations.push_back({ 0, 0 });				// Dungeon1
	RoomLocations.push_back({ 0, 720 });			// Dungeon2
	RoomLocations.push_back({ 780, 720 });			// Dungeon3
	RoomLocations.push_back({ 1540, 720 });			// Dungeon4
	RoomLocations.push_back({ 1752, 0 });			// Dungeon5
	RoomLocations.push_back({ 1546, 1480 });		// Dungeon6
	RoomLocations.push_back({ 1546, 2100 });		// Dungeon7
	RoomLocations.push_back({ 0, 1480 });			// Dungeon8

	RoomSizes.push_back({ 780, 720 });				// Dungeon1
	RoomSizes.push_back({ 780, 760 });				// Dungeon2
	RoomSizes.push_back({ 760, 760 });				// Dungeon3
	RoomSizes.push_back({ 1412, 760 });				// Dungeon4
	RoomSizes.push_back({ 1200, 720 });				// Dungeon5
	RoomSizes.push_back({ 1406, 620 });				// Dungeon6
	RoomSizes.push_back({ 1406, 824 });				// Dungeon7
	RoomSizes.push_back({ 1546, 1444 });			// Dungeon8

	for (int i = 0; i < RoomCount; i++)
	{
		ARoom* DungeonRoom = GetWorld()->SpawnActor<ARoom>();
		std::string DungeonName = "Dungeon";
		DungeonName.append(std::to_string(i + 1));
		std::string FileName = DungeonName + ".png";
		DungeonRoom->SetRoomSprite(FileName, ERenderOrder::BACKGROUND, RoomLocations[i], 1.0f);
		DungeonRoom->SetRoomSize(RoomSizes[i]);
		DungeonRoom->SetName(DungeonName);

		Roomes.push_back(DungeonRoom);
	}

	FindRoomToName("Dungeon1")->LinkRoom(FindRoomToName("Dungeon2"));
	FindRoomToName("Dungeon2")->LinkRoom(FindRoomToName("Dungeon3"));

	// 던전1 <=> 던전2로 링크
	Roomes[0]->AddRoomMove(new URoomMove({ 380.0f, 610.0f }, Roomes[0], Roomes[1], FVector2D::DOWN));
	//Roomes[1]->AddRoomMove(new URoomMove({ 380.0f, 894.0f }, Roomes[1], Roomes[0], FVector2D::UP));
}

void ARoomManageMode::RommesTick()
{
	for (int i = 0; i < RoomCount; i++)
	{
		if (CheckRoomInPlayer(Roomes[i]))
		{
			PlayerCharacter->CurRoom->SetPlayer(nullptr);
			PlayerCharacter->CurRoom = Roomes[i];
			this->CurRoom = Roomes[i];
		}
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
//
//void ARoomManageMode::TranslateRoom(FVector2D StartPos, FVector2D EndPos, float DeltaTime)
//{
//	//FVector2D CurCameraPos = GetWorld()->GetCameraPos();
//	//GetWorld()->SetCameraPos(CurCameraPos + (CurRoomMove->GetMoveDir() * DeltaTime * 300.0f));
//	//CurCameraPos = GetWorld()->GetCameraPos();
//	////FVector2D
//
//	//if (CurRoomMove->GetMoveDir() == FVector2D::RIGHT)
//	//{
//	//	if (CurCameraPos.iX() > GolLocation.iX())
//	//	{
//	//		GetWorld()->SetCameraPos({ GolLocation.X, CurCameraPos.Y});
//	//		ARoomManageMode::IsMapMoving = false;
//	//		PlayerCharacter->CurRoom->SetPlayer(nullptr);
//	//		PlayerCharacter->CurRoom = MoveRoom;
//	//		this->CurRoom = MoveRoom;
//
//	//		GolLocation = FVector2D::ZERO;
//	//		CurRoomMove = nullptr;
//	//	}
//	//}
//	//else if (CurRoomMove->GetMoveDir() == FVector2D::LEFT)
//	//{
//	//	if (CurCameraPos.iX() < GolLocation.iX())
//	//	{
//	//		GetWorld()->SetCameraPos({ GolLocation.X, CurCameraPos.Y });
//	//		ARoomManageMode::IsMapMoving = false;
//	//		PlayerCharacter->CurRoom->SetPlayer(nullptr);
//	//		PlayerCharacter->CurRoom = MoveRoom;
//	//		this->CurRoom = MoveRoom;
//
//	//		GolLocation = FVector2D::ZERO;
//	//		CurRoomMove = nullptr;
//	//	}
//	//}
//	//else if (CurRoomMove->GetMoveDir() == FVector2D::UP)
//	//{
//	//	if (CurCameraPos.iY() < GolLocation.iY())
//	//	{
//	//		GetWorld()->SetCameraPos({ CurCameraPos.X, GolLocation.Y });
//	//		ARoomManageMode::IsMapMoving = false;
//	//		PlayerCharacter->CurRoom->SetPlayer(nullptr);
//	//		PlayerCharacter->CurRoom = MoveRoom;
//	//		this->CurRoom = MoveRoom;
//
//	//		GolLocation = FVector2D::ZERO;
//	//		CurRoomMove = nullptr;
//	//	}
//	//}
//	//else if (CurRoomMove->GetMoveDir() == FVector2D::DOWN)
//	//{
//	//	int CurY = CurCameraPos.iY();
//	//	int ExitY = GolLocation.iY();
//
//	//	if (CurCameraPos.iY() > GolLocation.iY())
//	//	{
//	//		GetWorld()->SetCameraPos({ CurCameraPos.X, GolLocation.Y });
//	//		ARoomManageMode::IsMapMoving = false;
//	//		PlayerCharacter->CurRoom->SetPlayer(nullptr);
//	//		PlayerCharacter->CurRoom = Roomes[1];
//	//		PlayerCharacter->AddActorLocation(CurRoomMove->GetMoveSize());
//	//		PlayerCharacter->AddActorLocation({0, 15});
//	//		this->CurRoom = Roomes[1];
//
//	//		GolLocation = FVector2D::ZERO;
//	//		CurRoomMove = nullptr;
//	//	}
//	//}
//}
