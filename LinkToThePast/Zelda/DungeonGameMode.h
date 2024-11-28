#pragma once
#include "ZeldaGameMode.h"

class AUIBox;

/**
 *	����
 */
class ACastleDungeonGameMode : public AZeldaGameMode
{
public:
	/** ������, �Ҹ��� */
	ACastleDungeonGameMode();
	~ACastleDungeonGameMode();

	/** ��ü �� ���� ���� */
	ACastleDungeonGameMode(const ACastleDungeonGameMode& _Other) = delete;
	ACastleDungeonGameMode(ACastleDungeonGameMode&& _Other) noexcept = delete;
	ACastleDungeonGameMode& operator=(const ACastleDungeonGameMode& _Other) = delete;
	ACastleDungeonGameMode& operator=(ACastleDungeonGameMode&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlayRoomActor() override;

protected:

private:
	AUIBox* UIBox = nullptr;
};

