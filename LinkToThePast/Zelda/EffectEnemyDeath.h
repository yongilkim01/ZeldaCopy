#pragma once
#include "Effect.h"
#include <EnginePlatform/EngineSound.h>

/**
 *	����
 */
class AEffectEnemyDeath : public AEffect
{
public:
	/** ������, �Ҹ��� */
	AEffectEnemyDeath();
	~AEffectEnemyDeath();

	/** ��ü �� ���� ���� */
	AEffectEnemyDeath(const AEffectEnemyDeath& _Other) = delete;
	AEffectEnemyDeath(AEffectEnemyDeath&& _Other) noexcept = delete;
	AEffectEnemyDeath& operator=(const AEffectEnemyDeath& _Other) = delete;
	AEffectEnemyDeath& operator=(AEffectEnemyDeath&& _Other) noexcept = delete;

	virtual void EndEffect() override;
	void DestroyOwner();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	USoundPlayer SoundPlayer;
};

