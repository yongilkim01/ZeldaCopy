#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class UCollision2D;
class ABaseCharacter;

/**
 *	����
 */
class AEventActor : public AActor
{
public:
	/** ������, �Ҹ��� */
	AEventActor();
	~AEventActor();

	/** ��ü �� ���� ���� */
	AEventActor(const AEventActor& _Other) = delete;
	AEventActor(AEventActor&& _Other) noexcept = delete;
	AEventActor& operator=(const AEventActor& _Other) = delete;
	AEventActor& operator=(AEventActor&& _Other) noexcept = delete;

	/** ���� ���� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DetlaTime) override;

	/** �̺�Ʈ ���� ��� �޼ҵ� */
	virtual void Interact(ABaseCharacter* Character) {}
	virtual void Throw() {}

	/** �̺�Ʈ ���� ���� �޼ҵ� */
	void HoldToCharacter(FVector2D CharacterDirction);
	bool GetIsControl()
	{
		return IsControl;
	}
protected:
	USpriteRenderer* SpriteRenderer = nullptr;
	UCollision2D* Collision = nullptr;
	FVector2D CurDirection = FVector2D::ZERO;

	bool IsControl = false;

private:
};

