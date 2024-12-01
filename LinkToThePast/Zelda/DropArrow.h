#pragma once
#include "DropItem.h"
#include <EnginePlatform/EngineSound.h>

/**
 *	����
 */
class ADropArrowItem : public ADropItem
{
public:
	/** ������, �Ҹ��� */
	ADropArrowItem();
	~ADropArrowItem();

	/** ��ü �� ���� ���� */
	ADropArrowItem(const ADropArrowItem& _Other) = delete;
	ADropArrowItem(ADropArrowItem&& _Other) noexcept = delete;
	ADropArrowItem& operator=(const ADropArrowItem& _Other) = delete;
	ADropArrowItem& operator=(ADropArrowItem&& _Other) noexcept = delete;

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

