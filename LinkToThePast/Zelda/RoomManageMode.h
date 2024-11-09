#pragma once
#include <EngineCore/GameMode.h>

/** Std Header */
#include <vector>
#include <string>
#include <iostream>

enum class ERoomDirection
{
	NONE,
	RIGHT,
	LEFT,
	UP,
	DOWN,
	RIGHT_2F,
	LEFT_2F,
	UP_2F,
	DOWN_2F,
};

enum class ERoomMoveState
{
	CHECK,
	MOVE,
	END,
};

class URoomData
{
public:
	FVector2D Location;
	FVector2D Scale;
};

class ARoom;
class URoomMove;
class AUserInterface;

/**
 *	�� ���� ���� ���
 */
class ARoomManageMode : public AGameMode
{

public:
	static bool IsMapMoving;

	/** ������, �Ҹ��� */
	ARoomManageMode();
	~ARoomManageMode();

	/** ��ü �� ���� ���� */
	ARoomManageMode(const ARoomManageMode& _Other) = delete;
	ARoomManageMode(ARoomManageMode&& _Other) noexcept = delete;
	ARoomManageMode& operator=(const ARoomManageMode& _Other) = delete;
	ARoomManageMode& operator=(ARoomManageMode&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** UI ���� �޼ҵ� */
	void UIBeginPlay();
	void UITick();

	ARoom* FindRoomToName(std::string_view RoomName);
	void CreateRoomActor(std::string_view _MapName, int StartRoomIndex);

	void SetCurRoom(int _Index);

	void CheckStart();
	void CheckRoomMove();

	void MoveStart(ERoomDirection RoomMoveDirection);
	void MoveRoom();

	void EndStart();
	void EndRoomMove();

	bool CheckPlayerInRoom(ARoom* CheckRoom);
	void CheckCollisionRoom();

protected:
	class APlayerCharacter* PlayerCharacter = nullptr;

	/** �� ��� ���� */
	ARoom* CurRoom = nullptr;
	std::vector<ARoom*> Roomes;
	std::vector<URoomData> RoomDataes;


	/** ���� �������̽� ��� ���� */
	AUserInterface* UI = nullptr;
	std::string DungeonName = "";

	// ���ο� ����
	FVector2D CameraStartLocation = FVector2D::ZERO;
	FVector2D CameraEndLocation = FVector2D::ZERO;

	ERoomDirection CurRoomDir = ERoomDirection::NONE;
	ERoomMoveState RoomMoveState = ERoomMoveState::CHECK;
private:
	float CameraMoveSpeed = 1.0f;
	float RoomSizeRatio = 1.4f;
	float RoomMovePadding = 15.0f;
};