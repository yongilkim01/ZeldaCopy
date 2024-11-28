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
 *	설명
 */
class ALinkHouseGameMode : public AZeldaGameMode
{
public:
	/** 생성자, 소멸자 */
	ALinkHouseGameMode();
	~ALinkHouseGameMode();

	/** 객체 값 복사 방지 */
	ALinkHouseGameMode(const ALinkHouseGameMode& _Other) = delete;
	ALinkHouseGameMode(ALinkHouseGameMode&& _Other) noexcept = delete;
	ALinkHouseGameMode& operator=(const ALinkHouseGameMode& _Other) = delete;
	ALinkHouseGameMode& operator=(ALinkHouseGameMode&& _Other) noexcept = delete;

	/** 클래스 상태 메소드 */
	void StartHelpMsg();
	void HelpMsg(float DeltaTime);

	void ChangeState(ELinkHouseState State);

	/** 겟, 셋 메소드 */
	ARoom* GetLinkHouse()
	{
		return LinkHouse;
	}
	void SetLinkHouse(ARoom* Room)
	{
		LinkHouse = Room;
	}

protected:
	/** 액터 상속 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** 룸 상속 메소드 */
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

