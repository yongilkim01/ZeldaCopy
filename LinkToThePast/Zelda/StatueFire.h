#pragma once
#include "Statue.h"

/**
 *	설명
 */
class AStatueFire : public AStatue
{
public:
	/** 생성자, 소멸자 */
	AStatueFire();
	~AStatueFire();

	/** 객체 값 복사 방지 */
	AStatueFire(const AStatueFire& _Other) = delete;
	AStatueFire(AStatueFire&& _Other) noexcept = delete;
	AStatueFire& operator=(const AStatueFire& _Other) = delete;
	AStatueFire& operator=(AStatueFire&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

private:

};

