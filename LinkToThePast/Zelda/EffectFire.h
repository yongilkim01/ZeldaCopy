#pragma once
#include "Effect.h"

/**
 *	설명
 */
class AEffectFire : public AEffect
{
public:
	/** 생성자, 소멸자 */
	AEffectFire();
	~AEffectFire();

	/** 객체 값 복사 방지 */
	AEffectFire(const AEffectFire& _Other) = delete;
	AEffectFire(AEffectFire&& _Other) noexcept = delete;
	AEffectFire& operator=(const AEffectFire& _Other) = delete;
	AEffectFire& operator=(AEffectFire&& _Other) noexcept = delete;

	/** 액터 객체 상속 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

private:

};

