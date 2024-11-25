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
 *	����
 */
class ADoor : public AEventActor
{
public:
	/** ������, �Ҹ��� */
	ADoor();
	~ADoor();

	/** ��ü �� ���� ���� */
	ADoor(const ADoor& _Other) = delete;
	ADoor(ADoor&& _Other) noexcept = delete;
	ADoor& operator=(const ADoor& _Other) = delete;
	ADoor& operator=(ADoor&& _Other) noexcept = delete;

	/** ���� ���� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** �̺�Ʈ ���� ���� �޼ҵ� */
	virtual int Interact(ABaseCharacter* Character) override;

	/** �׾Ƹ� ���� ���� �ӽ� �޼ҵ� */
	void ChangeState(EDoorState DoorState);

	void StartClose();
	void StartOpen();

	void Close(float DeltaTime);
	void Open(float DeltaTime);

	/** �� �� �޼ҵ� */
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

