#pragma once
#include "DropItem.h"

/**
 *	����
 */
class ADropBowItem : public ADropItem
{
public:
	/** ������, �Ҹ��� */
	ADropBowItem();
	~ADropBowItem();

	/** ��ü �� ���� ���� */
	ADropBowItem(const ADropBowItem& _Other) = delete;
	ADropBowItem(ADropBowItem&& _Other) noexcept = delete;
	ADropBowItem& operator=(const ADropBowItem& _Other) = delete;
	ADropBowItem& operator=(ADropBowItem&& _Other) noexcept = delete;

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
	float CheckTime = 1.5f;
	float CurrentTime = 0.0f;

	FVector2D CurDropPower = FVector2D::ZERO;
};

