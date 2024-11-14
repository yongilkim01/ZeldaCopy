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
	RIGHT_DIRECT,
	LEFT_DIRECT,
	UP_DIRECT,
	DOWN_DIRECT,
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
class AZeldaGameMode : public AGameMode
{

public:
	static bool IsMapMoving;

	/** ������, �Ҹ��� */
	AZeldaGameMode();
	~AZeldaGameMode();

	/** ��ü �� ���� ���� */
	AZeldaGameMode(const AZeldaGameMode& _Other) = delete;
	AZeldaGameMode(AZeldaGameMode&& _Other) noexcept = delete;
	AZeldaGameMode& operator=(const AZeldaGameMode& _Other) = delete;
	AZeldaGameMode& operator=(AZeldaGameMode&& _Other) noexcept = delete;

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
	AUserInterface* UI = nullptr;

	// ���ο� ����
	FVector2D CameraStartLocation = FVector2D::ZERO;
	FVector2D CameraEndLocation = FVector2D::ZERO;

	ERoomDirection CurRoomDir = ERoomDirection::NONE;
	ERoomMoveState RoomMoveState = ERoomMoveState::CHECK;

private:
	const float CameraMoveSpeed = 1.0f;
	const float RoomSizeRatio = 1.4f;
	const float RoomMovePadding = 15.0f;
	const float DirectMoveDistance = 100.0f;
};