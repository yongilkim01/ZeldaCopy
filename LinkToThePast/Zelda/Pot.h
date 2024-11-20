#pragma once
#include "EventActor.h"

class APlayerCharacter;

enum class EPotState
{
	NONE,
	LIFT,
	FOLLOW,
	THROW,
};

/**
 *	����
 */
class APot : public AEventActor
{
public:
	/** ������, �Ҹ��� */
	APot();
	~APot();

	/** ��ü �� ���� ���� */
	APot(const APot& _Other) = delete;
	APot(APot&& _Other) noexcept = delete;
	APot& operator=(const APot& _Other) = delete;
	APot& operator=(APot&& _Other) noexcept = delete;

	/** ���� ���� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** �̺�Ʈ ���� ���� �޼ҵ� */
	virtual void Interact(ABaseCharacter* Character) override;
	virtual void Throw() override;
	virtual void DestoryEventActor() override;

	/** �׾Ƹ� ���� ���� �ӽ� �޼ҵ� */
	void ChangeState(EPotState PotState);
	
	void StartFollow();
	void StartThrow();

	void Follow(float DeltaTime);
	void Throw(float DeltaTime);

	/** �׾Ƹ� ���� ��ƿ �޼ҵ� */
	void EndBreak();

protected:

private:
	EPotState CurPotState = EPotState::NONE;

	APlayerCharacter* Owner = nullptr;

};

