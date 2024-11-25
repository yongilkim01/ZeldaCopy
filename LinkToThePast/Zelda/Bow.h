#pragma once
#include "WeaponItem.h"

/**
 *	����
 */
class ABow : public AWeaponItem
{
public:
	/** ������, �Ҹ��� */
	ABow();
	~ABow();

	/** ��ü �� ���� ���� */
	ABow(const ABow& _Other) = delete;
	ABow(ABow&& _Other) noexcept = delete;
	ABow& operator=(const ABow& _Other) = delete;
	ABow& operator=(ABow&& _Other) noexcept = delete;

	/** ���� ��� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** ���� ���� ��� �޼ҵ� */
	virtual void Action(float DeltaTime) override;

protected:

private:

};

