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
 *	설명
 */
class AGuardKnight : public AActor
{
public:
	/** 생성자, 소멸자 */
	AGuardKnight();
	~AGuardKnight();

	/** 객체 값 복사 방지 */
	AGuardKnight(const AGuardKnight& _Other) = delete;
	AGuardKnight(AGuardKnight&& _Other) noexcept = delete;
	AGuardKnight& operator=(const AGuardKnight& _Other) = delete;
	AGuardKnight& operator=(AGuardKnight&& _Other) noexcept = delete;

	/** 액터 상속 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** 상태 메소드 */
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

