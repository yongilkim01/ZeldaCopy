#pragma once
#include "Statue.h"

/**
 *	����
 */
class AStatueFire : public AStatue
{
public:
	/** ������, �Ҹ��� */
	AStatueFire();
	~AStatueFire();

	/** ��ü �� ���� ���� */
	AStatueFire(const AStatueFire& _Other) = delete;
	AStatueFire(AStatueFire&& _Other) noexcept = delete;
	AStatueFire& operator=(const AStatueFire& _Other) = delete;
	AStatueFire& operator=(AStatueFire&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

private:

};

