#pragma once
#include "BaseItem.h"

class USpriteRenderer;

/**
 *	����
 */
class AWeaponItem : public ABaseItem
{
public:
	/** ������, �Ҹ��� */
	AWeaponItem();
	~AWeaponItem();

	/** ��ü �� ���� ���� */
	AWeaponItem(const AWeaponItem& _Other) = delete;
	AWeaponItem(AWeaponItem&& _Other) noexcept = delete;
	AWeaponItem& operator=(const AWeaponItem& _Other) = delete;
	AWeaponItem& operator=(AWeaponItem&& _Other) noexcept = delete;

	/** ���� ��� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** ���� ���� ��� �޼ҵ� */
	void SetId(int Id)
	{
		this->Id = Id;
	}
	int GetId()
	{
		return this->Id;
	}

protected:
	USpriteRenderer* UISpriteRenderer = nullptr;
private:
	int Id = 0;
};
