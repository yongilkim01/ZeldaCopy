#pragma once
#include "BaseCharacter.h"

class USpriteRenderer;
class UCollision2D;
class ADropItem;

/**
 *	����
 */
class ABossCharacter : public ABaseCharacter
{
public:
	/** ������, �Ҹ��� */
	ABossCharacter();
	~ABossCharacter();

	/** ��ü �� ���� ���� */
	ABossCharacter(const ABossCharacter& _Other) = delete;
	ABossCharacter(ABossCharacter&& _Other) noexcept = delete;
	ABossCharacter& operator=(const ABossCharacter& _Other) = delete;
	ABossCharacter& operator=(ABossCharacter&& _Other) noexcept = delete;

	/** ���� ��� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** ��, �� �޼ҵ� */

protected:

	UCollision2D* HitCollision = nullptr;
	UCollision2D* AttackCollision = nullptr;

	ADropItem* DropItem = nullptr;

private:

};

