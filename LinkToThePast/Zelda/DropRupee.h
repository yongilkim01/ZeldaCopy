#pragma once
#include "DropItem.h"
#include <EnginePlatform/EngineSound.h>

/**
 *	����
 */
class ADropRupeeItem : public ADropItem
{
public:
	/** ������, �Ҹ��� */
	ADropRupeeItem();
	~ADropRupeeItem();

	/** ��ü �� ���� ���� */
	ADropRupeeItem(const ADropRupeeItem& _Other) = delete;
	ADropRupeeItem(ADropRupeeItem&& _Other) noexcept = delete;
	ADropRupeeItem& operator=(const ADropRupeeItem& _Other) = delete;
	ADropRupeeItem& operator=(ADropRupeeItem&& _Other) noexcept = delete;

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
	USoundPlayer SoundPlayer;
};

