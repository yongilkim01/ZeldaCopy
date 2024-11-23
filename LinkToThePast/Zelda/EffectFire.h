#pragma once
#include "Effect.h"

/**
 *	����
 */
class AEffectFire : public AEffect
{
public:
	/** ������, �Ҹ��� */
	AEffectFire();
	~AEffectFire();

	/** ��ü �� ���� ���� */
	AEffectFire(const AEffectFire& _Other) = delete;
	AEffectFire(AEffectFire&& _Other) noexcept = delete;
	AEffectFire& operator=(const AEffectFire& _Other) = delete;
	AEffectFire& operator=(AEffectFire&& _Other) noexcept = delete;

	/** ���� ��ü ��� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

private:

};

