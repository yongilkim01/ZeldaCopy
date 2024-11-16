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

	void SetCurDir(FVector2D Dir)
	{
		this->CurDir = Dir;
	}
	FVector2D GetCurDir()
	{
		return this->CurDir;
	}

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	USpriteRenderer* SpriteComponent = nullptr;
	UCollision2D* CollisionComponent = nullptr;

	FVector2D CurDir = FVector2D::ZERO;

private:

};

