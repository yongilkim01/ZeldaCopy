#pragma once
#include "ZeldaGameMode.h"
#include <EnginePlatform/EngineSound.h>

/**
 *	����
 */
class AHyruleCastleGameMode : public AZeldaGameMode
{
public:
	/** ������, �Ҹ��� */
	AHyruleCastleGameMode();
	~AHyruleCastleGameMode();

	/** ��ü �� ���� ���� */
	AHyruleCastleGameMode(const AHyruleCastleGameMode& _Other) = delete;
	AHyruleCastleGameMode(AHyruleCastleGameMode&& _Other) noexcept = delete;
	AHyruleCastleGameMode& operator=(const AHyruleCastleGameMode& _Other) = delete;
	AHyruleCastleGameMode& operator=(AHyruleCastleGameMode&& _Other) noexcept = delete;

	/** ���� ��� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** ���� ���Ӹ�� ��� �޼ҵ� */
	virtual void BeginPlayRoomActor() override;
	virtual void BeginPlayEnvActor() override;
	virtual void BeginPlayEnemyActor() override;
protected:

private:
	USoundPlayer EffectSoundPlayer;
};