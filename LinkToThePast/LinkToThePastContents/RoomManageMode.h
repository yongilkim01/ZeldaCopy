#pragma once
#include <EngineCore/GameMode.h>

/** Std Header */
#include <vector>
#include <string>
#include <iostream>

class ARoom;
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
	virtual void Tick(float DeltaTime) override;
	void RoomesBeginPlay();
	void RommesTick();

	void UIBeginPlay();
	void UITick();
	bool CheckRoomInPlayer(ARoom* CheckRoom);
	void CheckMoveRoom();
	ARoom* FindRoomToName(std::string_view RoomName);

	void TranslateRoom(float DeltaTime);
	
protected:

private:
	class APlayer* PlayerCharacter = nullptr;
	const int RoomCount = 8;
	FVector2D MoveDir = FVector2D::ZERO;

	/** 던전 방 멤버 변수 */
	ARoom* CurRoom = nullptr;
	std::vector<ARoom*> Roomes;
	std::vector<FVector2D> RoomLocations;
	std::vector<FVector2D> RoomSizes;

	/** 유저 인터페이스 멤버 변수 */
	AUserInterface* UI = nullptr;
};