#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class UCollision2D;
class APlayerCharacter;
class UEngineWinImage;
class ARoom;

enum class EArrowState
{
	NONE,
	THROW,
	HIT,
	STUCK,
};

/**
 *	����
 */
class AArrow : public AActor
{
public:
	/** ������, �Ҹ��� */
	AArrow();
	~AArrow();

	/** ��ü �� ���� ���� */
	AArrow(const AArrow& _Other) = delete;
	AArrow(AArrow&& _Other) noexcept = delete;
	AArrow& operator=(const AArrow& _Other) = delete;
	AArrow& operator=(AArrow&& _Other) noexcept = delete;

	/** ���� ��� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** ȭ�� �޼ҵ� */
	void StartThrow();
	void StartHit();
	void StartStuck();
	void Throw(float DeltaTime);
	void Hit(float DeltaTime);
	void Stuck(float DeltaTime);
	void ChangeState(EArrowState State);

	/** ��,�� �޼ҵ� */
	FVector2D GetDirection()
	{
		return CurDirection;
	}
	void SetDirection(FVector2D Direction)
	{
		CurDirection = Direction;
	}
	UEngineWinImage* GetCollisionImage()
	{
		return CollisionImage;
	}
	void SetCollisionImage(UEngineWinImage* Image)
	{
		CollisionImage = Image;
	}
	ARoom* GetCurRoom()
	{
		return CurRoom;
	}
	void SetCurRoom(ARoom* Room)
	{
		CurRoom = Room;
	}
	void SetOrder(int Order);

protected:

private:
	USpriteRenderer* SpriteRenderer = nullptr;
	UEngineWinImage* CollisionImage = nullptr;
	UCollision2D* Collision = nullptr;

	APlayerCharacter* PlayerCharacter = nullptr;
	ARoom* CurRoom = nullptr;
	EArrowState CurState = EArrowState::NONE;
	FVector2D CurDirection = FVector2D::ZERO;

	float Speed = 600.0f;
	float HitCheckTime = 0.5f;
	float HitCurrentTime = 0.0f;
};

