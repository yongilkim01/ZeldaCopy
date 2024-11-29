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
 *	����
 */
class ACastleUnderWaterGameMode : public AZeldaGameMode
{
public:
	/** ������, �Ҹ��� */
	ACastleUnderWaterGameMode();
	~ACastleUnderWaterGameMode();

	/** ��ü �� ���� ���� */
	ACastleUnderWaterGameMode(const ACastleUnderWaterGameMode& _Other) = delete;
	ACastleUnderWaterGameMode(ACastleUnderWaterGameMode&& _Other) noexcept = delete;
	ACastleUnderWaterGameMode& operator=(const ACastleUnderWaterGameMode& _Other) = delete;
	ACastleUnderWaterGameMode& operator=(ACastleUnderWaterGameMode&& _Other) noexcept = delete;

	/** Ŭ���� ���� �޼ҵ� */
	void StartFallLink();
	void FallLink (float DeltaTime);

	void StartGetWeapon();
	void GetWeapon(float DeltaTime);

	void StartGamePlay();
	void GamePlay(float DeltaTime);

	void ChangeState(ECastleUnderWaterState State);

	/** ��, �� �޼ҵ� */
	ARoom* GetCastleUnderWater()
	{
		return CastleUnderWater;
	}
	void SetCastleUnderWater(ARoom* Room)
	{
		CastleUnderWater = Room;
	}

protected:
	/** ���� ��� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** �� ��� �޼ҵ� */
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

