#pragma once
#include "EventActor.h"

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

protected:

private:

};

