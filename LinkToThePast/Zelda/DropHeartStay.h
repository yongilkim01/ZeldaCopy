#pragma once
#include "DropItem.h"

/**
 *	설명
 */
class ADropHeartStayItem : public ADropItem
{
public:
	/** 생성자, 소멸자 */
	ADropHeartStayItem();
	~ADropHeartStayItem();

	/** 객체 값 복사 방지 */
	ADropHeartStayItem(const ADropHeartStayItem& _Other) = delete;
	ADropHeartStayItem(ADropHeartStayItem&& _Other) noexcept = delete;
	ADropHeartStayItem& operator=(const ADropHeartStayItem& _Other) = delete;
	ADropHeartStayItem& operator=(ADropHeartStayItem&& _Other) noexcept = delete;

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
};

