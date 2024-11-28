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
 *	����
 */
class ALinkFather : public AActor
{
public:
	/** ������, �Ҹ��� */
	ALinkFather();
	~ALinkFather();

	/** ��ü �� ���� ���� */
	ALinkFather(const ALinkFather& _Other) = delete;
	ALinkFather(ALinkFather&& _Other) noexcept = delete;
	ALinkFather& operator=(const ALinkFather& _Other) = delete;
	ALinkFather& operator=(ALinkFather&& _Other) noexcept = delete;

	/** ���� �޼ҵ� */
	void StartSitDown();
	void SitDown(float DeltaTime);

	void StartSitLeft();
	void SitLeft(float DeltaTime);

	void StartMoveLeft();
	void MoveLeft(float DeltaTime);

	void StartMoveDown();
	void MoveDown(float DeltaTime);

	void ChangeState(ELinkFatherState State);

	/** ��, �� �޼ҵ� */
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
	/** ���� ��� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	float CurTime = 0.0f;

	USpriteRenderer* SpriteRenderer = nullptr;
	ELinkFatherState CurState = ELinkFatherState::NONE;
	FVector2D StartLocation = FVector2D::ZERO;
	FVector2D DestLocation = FVector2D::ZERO;
};

