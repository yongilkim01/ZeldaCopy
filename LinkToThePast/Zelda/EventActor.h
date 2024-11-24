#pragma once
#include <EngineCore/Actor.h>

#include "ContentsEnum.h"

class UEngineWinImage;
class USpriteRenderer;
class UCollision2D;
class ABaseCharacter;
class ARoom;

/**
 *	����
 */
class AEventActor : public AActor
{
public:
	/** ������, �Ҹ��� */
	AEventActor();
	~AEventActor();

	/** ��ü �� ���� ���� */
	AEventActor(const AEventActor& _Other) = delete;
	AEventActor(AEventActor&& _Other) noexcept = delete;
	AEventActor& operator=(const AEventActor& _Other) = delete;
	AEventActor& operator=(AEventActor&& _Other) noexcept = delete;

	/** ���� ���� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DetlaTime) override;

	/** �̺�Ʈ ���� ��� �޼ҵ� */
	virtual int Interact(ABaseCharacter* Character) { return 0; }
	virtual void Throw() {}
	virtual void DestoryEventActor() {}

	/** �̺�Ʈ ���� ���� �޼ҵ� */
	void HoldToCharacter(FVector2D CharacterDirction);
	void AddEventActorLocation(FVector2D Location);
	void SetEventActorRenderOrder();
	void SetEventActorRenderOrder(int Order);
	int GetEventActorRenderOrder();
	FVector2D GetDirectionToTargetLocation(FVector2D TargetLocation);
	FVector2D GetDirectionToThisLocation(FVector2D TargetLocation);
	FVector2D GetNormalDirectionToTargetLocation(FVector2D TargetLocation);
	FVector2D GetNormalDirectionToThisLocation(FVector2D TargetLocation);

	/** �� �� �޼ҵ� */
	void SetCurRoom(ARoom* Room, ERoomFloor RoomFloor);
	ARoom* GetCurRoom()
	{
		return CurRoom;
	}
	bool GetIsControl()
	{
		return IsControl;
	}
	bool GetIsEquipalbe()
	{
		return IsEquipable;
	}
protected:
	USpriteRenderer* SpriteRenderer = nullptr;
	UCollision2D* Collision = nullptr;
	UCollision2D* ImmuneCollision = nullptr;
	FVector2D CurDirection = FVector2D::ZERO;

	bool IsControl = false;
	bool IsEquipable = false;

private:
	ARoom* CurRoom = nullptr;
	UEngineWinImage* CollisionImage = nullptr;
};

