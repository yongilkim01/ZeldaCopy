#pragma once
#include <EngineCore/Actor.h>

enum class EGuardState
{
	NONE,
	IDLE,
	EVENT,
};

class UCollision2D;
class USpriteRenderer;
class APlayerCharacter;
class AUIBox;

/**
 *	����
 */
class AGuardKnight : public AActor
{
public:
	/** ������, �Ҹ��� */
	AGuardKnight();
	~AGuardKnight();

	/** ��ü �� ���� ���� */
	AGuardKnight(const AGuardKnight& _Other) = delete;
	AGuardKnight(AGuardKnight&& _Other) noexcept = delete;
	AGuardKnight& operator=(const AGuardKnight& _Other) = delete;
	AGuardKnight& operator=(AGuardKnight&& _Other) noexcept = delete;

	/** ���� ��� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** ���� �޼ҵ� */
	void StartIdle();
	void Idle(float DeltaTime);

	void StartEvent();
	void Event(float DeltaTime);

	void ChangeState(EGuardState State);

protected:

private:
	USpriteRenderer* SpriteRenderer = nullptr;
	UCollision2D* EventCollison = nullptr;
	EGuardState CurState = EGuardState::NONE;

	APlayerCharacter* Player = nullptr;
	AUIBox* UIBox = nullptr;
	float CurTime = 0.0f;
};

