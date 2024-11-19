#pragma once
#include "Statue.h"

/**
 *	����
 */
class AStatueStone : public AStatue
{
public:
	/** ������, �Ҹ��� */
	AStatueStone();
	~AStatueStone();

	/** ��ü �� ���� ���� */
	AStatueStone(const AStatueStone& _Other) = delete;
	AStatueStone(AStatueStone&& _Other) noexcept = delete;
	AStatueStone& operator=(const AStatueStone& _Other) = delete;
	AStatueStone& operator=(AStatueStone&& _Other) noexcept = delete;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

private:

};

