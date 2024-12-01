#pragma once
#include "Effect.h"
#include <EnginePlatform/EngineSound.h>

/**
 *	설명
 */
class AEffectEnemyDeath : public AEffect
{
public:
	/** 생성자, 소멸자 */
	AEffectEnemyDeath();
	~AEffectEnemyDeath();

	/** 객체 값 복사 방지 */
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

