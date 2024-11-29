#pragma once
#include "ZeldaGameMode.h"

class ARoom;
class AUIBox;
class AHouseBed;
class AFade;
class APlayerCharacter;
class ALinkFather;

enum class ECastleUnderWaterState
{
	NONE,
	LINK_FALL,
	GAMEPLAY,
	ITEM_GET,
};

class USpriteRenderer;

/**
 *	설명
 */
class ACastleUnderWaterGameMode : public AZeldaGameMode
{
public:
	/** 생성자, 소멸자 */
	ACastleUnderWaterGameMode();
	~ACastleUnderWaterGameMode();

	/** 객체 값 복사 방지 */
	ACastleUnderWaterGameMode(const ACastleUnderWaterGameMode& _Other) = delete;
	ACastleUnderWaterGameMode(ACastleUnderWaterGameMode&& _Other) noexcept = delete;
	ACastleUnderWaterGameMode& operator=(const ACastleUnderWaterGameMode& _Other) = delete;
	ACastleUnderWaterGameMode& operator=(ACastleUnderWaterGameMode&& _Other) noexcept = delete;

	/** 클래스 상태 메소드 */
	void StartFallLink();
	void FallLink (float DeltaTime);

	void StartGetWeapon();
	void GetWeapon(float DeltaTime);

	void StartGamePlay();
	void GamePlay(float DeltaTime);

	void ChangeState(ECastleUnderWaterState State);

	/** 겟, 셋 메소드 */
	ARoom* GetCastleUnderWater()
	{
		return CastleUnderWater;
	}
	void SetCastleUnderWater(ARoom* Room)
	{
		CastleUnderWater = Room;
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
	float CurTime = 0.0f;

	APlayerCharacter* Player = nullptr;
	AUIBox* UIBox = nullptr;
	ARoom* CastleUnderWater = nullptr;
	ALinkFather* LinkFather = nullptr;

	FVector2D LinkStartLocation = FVector2D(1152, 0);
	FVector2D LinkDestLocation = FVector2D(1152, 308);

	USpriteRenderer* FadeRenderer = nullptr;
	ECastleUnderWaterState CurState = ECastleUnderWaterState::NONE;
};

