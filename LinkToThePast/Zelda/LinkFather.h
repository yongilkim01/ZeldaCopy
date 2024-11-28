#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;

enum class ELinkFatherState
{
	NONE,
	SIT_DOWN,
	SIT_LEFT,
	MOVE_LEFT,
	MOVE_DOWN
};

/**
 *	설명
 */
class ALinkFather : public AActor
{
public:
	/** 생성자, 소멸자 */
	ALinkFather();
	~ALinkFather();

	/** 객체 값 복사 방지 */
	ALinkFather(const ALinkFather& _Other) = delete;
	ALinkFather(ALinkFather&& _Other) noexcept = delete;
	ALinkFather& operator=(const ALinkFather& _Other) = delete;
	ALinkFather& operator=(ALinkFather&& _Other) noexcept = delete;

	/** 상태 메소드 */
	void StartSitDown();
	void SitDown(float DeltaTime);

	void StartSitLeft();
	void SitLeft(float DeltaTime);

	void StartMoveLeft();
	void MoveLeft(float DeltaTime);

	void StartMoveDown();
	void MoveDown(float DeltaTime);

	void ChangeState(ELinkFatherState State);

	/** 겟, 셋 메소드 */
	FVector2D GetStartLocation()
	{
		return StartLocation;
	}
	void SetStartLocation(FVector2D Location)
	{
		StartLocation = Location;
	}
	FVector2D GetDestLocation()
	{
		return DestLocation;
	}
	void SetDestLocaion(FVector2D Location)
	{
		DestLocation = Location;
	}

protected:
	/** 액터 상속 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	float CurTime = 0.0f;

	USpriteRenderer* SpriteRenderer = nullptr;
	ELinkFatherState CurState = ELinkFatherState::NONE;
	FVector2D StartLocation = FVector2D::ZERO;
	FVector2D DestLocation = FVector2D::ZERO;
};

