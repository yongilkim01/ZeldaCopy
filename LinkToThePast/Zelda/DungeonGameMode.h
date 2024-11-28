#pragma once
#include "ZeldaGameMode.h"

class AUIBox;

/**
 *	설명
 */
class ACastleDungeonGameMode : public AZeldaGameMode
{
public:
	/** 생성자, 소멸자 */
	ACastleDungeonGameMode();
	~ACastleDungeonGameMode();

	/** 객체 값 복사 방지 */
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

