#pragma once
#include "EventActor.h"

class APlayerCharacter;

/**
 *	����
 */
class ADropItem : public AEventActor
{
public:
	/** ������, �Ҹ��� */
	ADropItem();
	~ADropItem();

	/** ��ü �� ���� ���� */
	ADropItem(const ADropItem& _Other) = delete;
	ADropItem(ADropItem&& _Other) noexcept = delete;
	ADropItem& operator=(const ADropItem& _Other) = delete;
	ADropItem& operator=(ADropItem&& _Other) noexcept = delete;

	/** ���� ��� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** ADropItem ��� �޼ҵ� */
	virtual void StartDrop();
	virtual void StartPickup();
	virtual void Drop(float DeltaTime);
	virtual void Pickup(float DeltaTime);

	/** ADropItem ���� �޼ҵ� */
	void ChangeState(EDropItemState State);

	/** ��, �� �޼ҵ� */
	void SetDropItemType(EDropItemType Type)
	{
		CurDropItemType = Type;
	}
	EDropItemType GetDropItemType()
	{
		return CurDropItemType;
	}
	void SetDropItemState(EDropItemState State)
	{
		CurDropItemState = State;
	}
	EDropItemState GetDropItemState()
	{
		return CurDropItemState;
	}
	APlayerCharacter* GetPlayerCharacter()
	{
		return PlayerCharacter;
	}

protected:

private:
	EDropItemType CurDropItemType = EDropItemType::NONE;
	EDropItemState CurDropItemState = EDropItemState::NONE;
	APlayerCharacter* PlayerCharacter = nullptr;
};

