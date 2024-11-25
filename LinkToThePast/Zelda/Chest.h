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
 *	설명
 */
class AChest : public AEventActor
{
public:
	/** 생성자, 소멸자 */
	AChest();
	~AChest();

	/** 객체 값 복사 방지 */
	AChest(const AChest& _Other) = delete;
	AChest(AChest&& _Other) noexcept = delete;
	AChest& operator=(const AChest& _Other) = delete;
	AChest& operator=(AChest&& _Other) noexcept = delete;

	/** 액터 공통 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** 이벤트 액터 공통 메소드 */
	virtual int Interact(ABaseCharacter* Character) override;

	/** 항아리 액터 상태 머신 메소드 */
	void ChangeState(EChestState ChestState);

	void StartClose();
	void StartOpen();

	void Close(float DeltaTime);
	void Open(float DeltaTime);

	/** 겟, 셋 메소드 */
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

