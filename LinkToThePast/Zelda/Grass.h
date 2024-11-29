#pragma once
#include "EventActor.h"

class APlayerCharacter;

enum class EGrassState
{
	NONE,
	LIFT,
	FOLLOW,
	THROW,
};

/**
 *	����
 */
class AGrass : public AEventActor
{
public:
	/** ������, �Ҹ��� */
	AGrass();
	~AGrass();

	/** ��ü �� ���� ���� */
	AGrass(const AGrass& _Other) = delete;
	AGrass(AGrass&& _Other) noexcept = delete;
	AGrass& operator=(const AGrass& _Other) = delete;
	AGrass& operator=(AGrass&& _Other) noexcept = delete;

	/** ���� ���� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** �̺�Ʈ ���� ���� �޼ҵ� */
	virtual int Interact(ABaseCharacter* Character) override;
	virtual void Throw() override;
	virtual void DestoryEventActor() override;

	/** �׾Ƹ� ���� ���� �ӽ� �޼ҵ� */
	void ChangeState(EGrassState GrassState);

	void StartFollow();
	void StartThrow();

	void Follow(float DeltaTime);
	void Throw(float DeltaTime);

	/** �׾Ƹ� ���� ��ƿ �޼ҵ� */
	void EndBreak();
	void SetDropItemType(EDropItemType ItemType)
	{
		DropItemType = ItemType;
	}

protected:

private:
	EGrassState CurGrassState = EGrassState::NONE;

	APlayerCharacter* Owner = nullptr;
	EDropItemType DropItemType = EDropItemType::NONE;

	float ThrowSpeed = 1000.0f;

};

