#pragma once
#include "DropItem.h"

/**
 *	����
 */
class ADropHeartItem : public ADropItem
{
public:
	/** ������, �Ҹ��� */
	ADropHeartItem();
	~ADropHeartItem();

	/** ��ü �� ���� ���� */
	ADropHeartItem(const ADropHeartItem& _Other) = delete;
	ADropHeartItem(ADropHeartItem&& _Other) noexcept = delete;
	ADropHeartItem& operator=(const ADropHeartItem& _Other) = delete;
	ADropHeartItem& operator=(ADropHeartItem&& _Other) noexcept = delete;

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
	float DropSpeed = 0.1f;
	float DropLength = 50.0f;
	float DropFrequency = 30.0f;
	float CurrentDeltaTime = 0.0f;

	FVector2D CurDropPower = FVector2D::ZERO;
};

