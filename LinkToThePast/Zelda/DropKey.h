#pragma once
#include "DropItem.h"

/**
 *	설명
 */
	class ADropKeyItem : public ADropItem
{
public:
	/** 생성자, 소멸자 */
	ADropKeyItem();
	~ADropKeyItem();

	/** 객체 값 복사 방지 */
	ADropKeyItem(const ADropKeyItem& _Other) = delete;
	ADropKeyItem(ADropKeyItem&& _Other) noexcept = delete;
	ADropKeyItem& operator=(const ADropKeyItem& _Other) = delete;
	ADropKeyItem& operator=(ADropKeyItem&& _Other) noexcept = delete;

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
	float DropSpeed = 300.0f;
	float DropLength = 50.0f;
	float DropFrequency = 1.0f;
};

