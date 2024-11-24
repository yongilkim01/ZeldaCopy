#pragma once
#include "DropItem.h"

/**
 *	����
 */
	class ADropKeyItem : public ADropItem
{
public:
	/** ������, �Ҹ��� */
	ADropKeyItem();
	~ADropKeyItem();

	/** ��ü �� ���� ���� */
	ADropKeyItem(const ADropKeyItem& _Other) = delete;
	ADropKeyItem(ADropKeyItem&& _Other) noexcept = delete;
	ADropKeyItem& operator=(const ADropKeyItem& _Other) = delete;
	ADropKeyItem& operator=(ADropKeyItem&& _Other) noexcept = delete;

	/** ���� ��� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** ADropItem ��� �޼ҵ� */
	virtual void StartDrop() override;
	virtual void StartPickup() override;
	virtual void Drop(float DeltaTime) override;
	virtual void Pickup(float DeltaTime) override;

protected:

private:
	float DropSpeed = 300.0f;
	float DropLength = 50.0f;
	float DropFrequency = 1.0f;
};

