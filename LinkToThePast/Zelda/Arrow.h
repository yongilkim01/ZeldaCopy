#pragma once
#include <EngineCore/Actor.h>
#include <EnginePlatform/EngineSound.h>

class USpriteRenderer;
class UCollision2D;
class APlayerCharacter;
class ABaseCharacter;
class UEngineWinImage;
class ARoom;

enum class EArrowState
{
	NONE,
	THROW,
	HIT,
	STUCK,
	DESTROY
};

/**
 *	설명
 */
class AArrow : public AActor
{
public:
	/** 생성자, 소멸자 */
	AArrow();
	~AArrow();

	/** 객체 값 복사 방지 */
	AArrow(const AArrow& _Other) = delete;
	AArrow(AArrow&& _Other) noexcept = delete;
	AArrow& operator=(const AArrow& _Other) = delete;
	AArrow& operator=(AArrow&& _Other) noexcept = delete;

	/** 액터 상속 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** 화살 메소드 */
	void StartThrow();
	void StartHit();
	void StartStuck();
	void StartDestroy();
	void Throw(float DeltaTime);
	void Hit(float DeltaTime);
	void Stuck(float DeltaTime);
	void ChangeState(EArrowState State);

	/** 겟,셋 메소드 */
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
	ABaseCharacter* HitCharacter = nullptr;
	ARoom* CurRoom = nullptr;
	EArrowState CurState = EArrowState::NONE;
	USoundPlayer SoundPlayer;

	FVector2D CurDirection = FVector2D::ZERO;
	FVector2D PrevHitLocation = FVector2D::ZERO;

	float Speed = 600.0f;
	float HitCheckTime = 0.5f;
	float HitCurrentTime = 0.0f;
	float LifeCheckTime = 2.0f;
	float LifeCurrentTime = 0.0f;
};

