#pragma once
#include "DropItem.h"

/**
 *	����
 */
class ADropHeartStayItem : public ADropItem
{
public:
	/** ������, �Ҹ��� */
	ADropHeartStayItem();
	~ADropHeartStayItem();

	/** ��ü �� ���� ���� */
	ADropHeartStayItem(const ADropHeartStayItem& _Other) = delete;
	ADropHeartStayItem(ADropHeartStayItem&& _Other) noexcept = delete;
	ADropHeartStayItem& operator=(const ADropHeartStayItem& _Other) = delete;
	ADropHeartStayItem& operator=(ADropHeartStayItem&& _Other) noexcept = delete;

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

