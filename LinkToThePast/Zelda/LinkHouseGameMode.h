#pragma once
#include "ZeldaGameMode.h"

class ARoom;
class AUIBox;
class AHouseBed;
class AFade;
class APlayerCharacter;
class ALinkFather;

enum class ELinkHouseState
{
	NONE,
	HELPMSG,
	SKIP,
	FADE_OUT,
	NPC_TALK,
	NPC_MOVE_LEFT,
	NPC_MOVE_DOWN,
	GAMEPLAY,
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

	void StartFadeOut();
	void FadeOut(float DeltaTime);

	void StartSkip();
	void Skip(float DeltaTime);

	void StartNPCTalk();
	void NPCTalk(float DeltaTime);

	void StartNPCMoveLeft();
	void NPCMoveLeft(float DeltaTime);

	void StartNPCMoveDown();
	void NPCMoveDown(float DeltaTime);

	void StartGamePlay();
	void GamePlay(float DeltaTime);

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

private:
	float FadeAlpha = 0.9f;

	APlayerCharacter* Player = nullptr;
	AHouseBed* HouseBed = nullptr;
	AUIBox* UIBox = nullptr;
	ARoom* LinkHouse = nullptr;
	AFade* Fade = nullptr;
	ALinkFather* LinkFather = nullptr;

	USpriteRenderer* FadeBlueRenderer = nullptr;
	ELinkHouseState CurState = ELinkHouseState::NONE;
};

