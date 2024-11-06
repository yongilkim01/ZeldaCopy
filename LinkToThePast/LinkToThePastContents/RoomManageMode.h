#pragma once
#include <EngineCore/GameMode.h>

/** Std Header */
#include <vector>
#include <string>
#include <iostream>

class URoomData
{
public:
	FVector2D Location;
	FVector2D Scale;
};

class ARoom;
class URoomMove;
class AUserInterface;
// 설명 :
class ARoomManageMode : public AGameMode
{

public:
	static bool IsMapMoving;

	// constrcuter destructer
	ARoomManageMode();
	~ARoomManageMode();

	// delete Function
	ARoomManageMode(const ARoomManageMode& _Other) = delete;
	ARoomManageMode(ARoomManageMode&& _Other) noexcept = delete;
	ARoomManageMode& operator=(const ARoomManageMode& _Other) = delete;
	ARoomManageMode& operator=(ARoomManageMode&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	void UIBeginPlay();

	virtual void Tick(float DeltaTime) override;
	void UITick();

	bool CheckRoomInPlayer(ARoom* CheckRoom);
	void CheckMoveRoom();
	ARoom* FindRoomToName(std::string_view RoomName);
	void CreateRoomActor(std::string_view _MapName);

protected:
	class APlayer* PlayerCharacter = nullptr;
	const int RoomCount = 8;

	/** 던전 방 멤버 변수 */
	ARoom* CurRoom = nullptr;
	ARoom* MoveRoom = nullptr;
	URoomMove* CurRoomMove = nullptr;
	std::vector<ARoom*> Roomes;
	std::vector<FVector2D> RoomLocations;
	std::vector<FVector2D> RoomSizes;

	std::vector<URoomData> RoomDataes;


	/** 유저 인터페이스 멤버 변수 */
	AUserInterface* UI = nullptr;
	std::string DungeonName = "";

private:


};