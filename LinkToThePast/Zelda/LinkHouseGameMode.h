#pragma once
#include "ZeldaGameMode.h"

class ARoom;
class AUIBox;
class AHouseBed;
class AFade;
class APlayerCharacter;

enum class ELinkHouseState
{
	NONE,
	HELPMSG,
};

class USpriteRenderer;

/**
 *	����
 */
class ALinkHouseGameMode : public AZeldaGameMode
{
public:
	/** ������, �Ҹ��� */
	ALinkHouseGameMode();
	~ALinkHouseGameMode();

	/** ��ü �� ���� ���� */
	ALinkHouseGameMode(const ALinkHouseGameMode& _Other) = delete;
	ALinkHouseGameMode(ALinkHouseGameMode&& _Other) noexcept = delete;
	ALinkHouseGameMode& operator=(const ALinkHouseGameMode& _Other) = delete;
	ALinkHouseGameMode& operator=(ALinkHouseGameMode&& _Other) noexcept = delete;

	/** Ŭ���� ���� �޼ҵ� */
	void StartHelpMsg();
	void HelpMsg(float DeltaTime);

	void ChangeState(ELinkHouseState State);

	/** ��, �� �޼ҵ� */
	ARoom* GetLinkHouse()
	{
		return LinkHouse;
	}
	void SetLinkHouse(ARoom* Room)
	{
		LinkHouse = Room;
	}

protected:
	/** ���� ��� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** �� ��� �޼ҵ� */
	virtual void BeginPlayRoomActor() override;
	virtual void BeginPlayEnvActor() override;
	virtual void BeginPlayEnemyActor() override;


private:
	APlayerCharacter* Player = nullptr;
	AHouseBed* HouseBed = nullptr;
	AUIBox* UIBox = nullptr;
	ARoom* LinkHouse = nullptr;
	AFade* Fade = nullptr;

	USpriteRenderer* FadeBlueRenderer = nullptr;
	ELinkHouseState CurState = ELinkHouseState::NONE;
};

