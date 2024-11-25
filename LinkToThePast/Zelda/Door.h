#pragma once
#include "EventActor.h"
#include <EnginePlatform/EngineSound.h>

class APlayerCharacter;

enum class EDoorType
{
	NONE,
	KEYTYPE,
	GIMMICK,
};

enum class EDoorDirection
{
	NONE,
	RIGHT,
	LEFT,
	UP,
	DOWN,
};

enum class EDoorState
{
	NONE,
	CLOSE,
	OPEN
};

/**
 *	설명
 */
class ADoor : public AEventActor
{
public:
	/** 생성자, 소멸자 */
	ADoor();
	~ADoor();

	/** 객체 값 복사 방지 */
	ADoor(const ADoor& _Other) = delete;
	ADoor(ADoor&& _Other) noexcept = delete;
	ADoor& operator=(const ADoor& _Other) = delete;
	ADoor& operator=(ADoor&& _Other) noexcept = delete;

	/** 액터 공통 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** 이벤트 액터 공통 메소드 */
	virtual int Interact(ABaseCharacter* Character) override;

	/** 항아리 액터 상태 머신 메소드 */
	void ChangeState(EDoorState DoorState);

	void StartClose();
	void StartOpen();

	void Close(float DeltaTime);
	void Open(float DeltaTime);

	/** 겟 셋 메소드 */
	void SetDoorDirection(EDoorDirection Direction);
	EDoorDirection GetDoorDirection();
	void SetDoorType(EDoorType Type);
	EDoorType GetDoorType();
	void SetDoorRenderOrder(int Order);

protected:

private:
	EDoorState CurDoorState = EDoorState::NONE;
	EDoorDirection DoorDirection = EDoorDirection::NONE;
	EDoorType DoorType = EDoorType::NONE;

	APlayerCharacter* Owner = nullptr;
	USoundPlayer SoundPlayer;
};

