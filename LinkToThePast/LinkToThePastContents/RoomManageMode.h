#pragma once
#include <EngineCore/GameMode.h>

/** Std Header */
#include <vector>
#include <string>
#include <iostream>

class ARoom;
class AUserInterface;
// ���� :
class ARoomManageMode : public AGameMode
{
public:
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
	ARoom* FindRoomToName(std::string_view RoomName);
	
protected:

private:
	class APlayer* PlayerCharacter = nullptr;
	const int RoomCount = 8;

	/** ���� �� ��� ���� */
	std::vector<ARoom*> Roomes;
	std::vector<FVector2D> RoomLocations;
	std::vector<FVector2D> RoomSizes;

	/** ���� �������̽� ��� ���� */
	AUserInterface* UI = nullptr;
};