#pragma once
#include "DropItem.h"
#include <EnginePlatform/EngineSound.h>

/**
 *	설명
 */
class ADropMagicDrinkItem : public ADropItem
{
public:
	/** 생성자, 소멸자 */
	ADropMagicDrinkItem();
	~ADropMagicDrinkItem();

	/** 객체 값 복사 방지 */
	ADropMagicDrinkItem(const ADropMagicDrinkItem& _Other) = delete;
	ADropMagicDrinkItem(ADropMagicDrinkItem&& _Other) noexcept = delete;
	ADropMagicDrinkItem& operator=(const ADropMagicDrinkItem& _Other) = delete;
	ADropMagicDrinkItem& operator=(ADropMagicDrinkItem&& _Other) noexcept = delete;

	/** 액터 상속 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** ADropItem 상속 메소드 */
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

