#pragma once
#include "DropItem.h"

/**
 *	설명
 */
class ADropBowItem : public ADropItem
{
public:
	/** 생성자, 소멸자 */
	ADropBowItem();
	~ADropBowItem();

	/** 객체 값 복사 방지 */
	ADropBowItem(const ADropBowItem& _Other) = delete;
	ADropBowItem(ADropBowItem&& _Other) noexcept = delete;
	ADropBowItem& operator=(const ADropBowItem& _Other) = delete;
	ADropBowItem& operator=(ADropBowItem&& _Other) noexcept = delete;

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
	float CheckTime = 1.5f;
	float CurrentTime = 0.0f;

	FVector2D CurDropPower = FVector2D::ZERO;
};

