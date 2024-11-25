#pragma once
#include "EventActor.h"
#include "ContentsEnum.h"

class APlayerCharacter;

enum class EChestState
{
	NONE,
	CLOSE,
	OPEN
};

/**
 *	����
 */
class AChest : public AEventActor
{
public:
	/** ������, �Ҹ��� */
	AChest();
	~AChest();

	/** ��ü �� ���� ���� */
	AChest(const AChest& _Other) = delete;
	AChest(AChest&& _Other) noexcept = delete;
	AChest& operator=(const AChest& _Other) = delete;
	AChest& operator=(AChest&& _Other) noexcept = delete;

	/** ���� ���� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** �̺�Ʈ ���� ���� �޼ҵ� */
	virtual int Interact(ABaseCharacter* Character) override;

	/** �׾Ƹ� ���� ���� �ӽ� �޼ҵ� */
	void ChangeState(EChestState ChestState);

	void StartClose();
	void StartOpen();

	void Close(float DeltaTime);
	void Open(float DeltaTime);

	/** ��, �� �޼ҵ� */
	void SetDropItemType(EDropItemType ItemType)
	{
		DropItemType = ItemType;
	}

protected:

private:
	EChestState CurChestState = EChestState::NONE;
	APlayerCharacter* Owner = nullptr;
	EDropItemType DropItemType = EDropItemType::NONE;

};

