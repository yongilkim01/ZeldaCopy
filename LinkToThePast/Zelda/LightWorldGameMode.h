#pragma once
#include "ZeldaGameMode.h"

class ARoom;
class AUIBox;
class AHouseBed;
class AFade;
class APlayerCharacter;
class ALinkFather;

class USpriteRenderer;

/**
 *	����
 */
class ALightWorldGameMode : public AZeldaGameMode
{
public:
	/** ������, �Ҹ��� */
	ALightWorldGameMode();
	~ALightWorldGameMode();

	/** ��ü �� ���� ���� */
	ALightWorldGameMode(const ALightWorldGameMode& _Other) = delete;
	ALightWorldGameMode(ALightWorldGameMode&& _Other) noexcept = delete;
	ALightWorldGameMode& operator=(const ALightWorldGameMode& _Other) = delete;
	ALightWorldGameMode& operator=(ALightWorldGameMode&& _Other) noexcept = delete;

	/** ��, �� �޼ҵ� */

protected:
	/** ���� ��� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** �� ��� �޼ҵ� */
	virtual void BeginPlayRoomActor() override;
	virtual void BeginPlayEnvActor() override;

private:
	APlayerCharacter* Player = nullptr;
	AFade* Fade = nullptr;
};

