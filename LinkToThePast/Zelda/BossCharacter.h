#pragma once
#include "BaseCharacter.h"

class USpriteRenderer;
class UCollision2D;

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

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UCollision2D* HitCollision = nullptr;
	UCollision2D* AttackCollision = nullptr;


private:

};

