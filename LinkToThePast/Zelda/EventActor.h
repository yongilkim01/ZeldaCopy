#pragma once
#include <EngineCore/Actor.h>

#include "ContentsEnum.h"

class UEngineWinImage;
class USpriteRenderer;
class UCollision2D;
class ABaseCharacter;
class ARoom;

/**
 *	설명
 */
class AEventActor : public AActor
{
public:
	/** 생성자, 소멸자 */
	AEventActor();
	~AEventActor();

	/** 객체 값 복사 방지 */
	AEventActor(const AEventActor& _Other) = delete;
	AEventActor(AEventActor&& _Other) noexcept = delete;
	AEventActor& operator=(const AEventActor& _Other) = delete;
	AEventActor& operator=(AEventActor&& _Other) noexcept = delete;

	/** 액터 공통 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DetlaTime) override;

	/** 이벤트 액터 상속 메소드 */
	virtual void Interact(ABaseCharacter* Character) {}
	virtual void Throw() {}
	virtual void DestoryEventActor() {}

	/** 이벤트 액터 공통 메소드 */
	void HoldToCharacter(FVector2D CharacterDirction);
	void AddEventActorLocation(FVector2D Location);

	/** 겟 셋 메소드 */
	void SetCurRoom(ARoom* Room, ERoomFloor RoomFloor);
	ARoom* GetCurRoom()
	{
		return CurRoom;
	}
	bool GetIsControl()
	{
		return IsControl;
	}
protected:
	USpriteRenderer* SpriteRenderer = nullptr;
	UCollision2D* Collision = nullptr;
	UCollision2D* ImmuneCollision = nullptr;
	FVector2D CurDirection = FVector2D::ZERO;

	bool IsControl = false;

private:
	ARoom* CurRoom = nullptr;
	UEngineWinImage* CollisionImage = nullptr;
};

