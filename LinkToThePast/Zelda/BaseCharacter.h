#pragma once
#include "ContentsEnum.h"

#include <EngineCore/Actor.h>

class ARoom;
class UEngineWinImage;

class ABaseCharacter : public AActor
{
public:
	/** ������, �Ҹ��� */
	ABaseCharacter();
	~ABaseCharacter();

	/** ��ü �� ���� ���� */
	ABaseCharacter(const ABaseCharacter& _Other) = delete;
	ABaseCharacter(ABaseCharacter&& _Other) noexcept = delete;
	ABaseCharacter& operator=(const ABaseCharacter& _Other) = delete;
	ABaseCharacter& operator=(ABaseCharacter&& _Other) noexcept = delete;

	/** ĳ���� ���� �޼ҵ� */
	virtual void TakeDamage(int Damage, ABaseCharacter* Character) {}
	virtual void Death() {}
	virtual void Fall() {}

	/** ĳ���� ���� �޼ҵ� */
	void AddCharacterLocation(FVector2D MoveDirection);
	FVector2D GetDirectionToTargetLocation(FVector2D TargetLocation);
	FVector2D GetDirectionToThisLocation(FVector2D TargetLocation);
	FVector2D GetNormalDirectionToTargetLocation(FVector2D TargetLocation);
	FVector2D GetNormalDirectionToThisLocation(FVector2D TargetLocation);
	float GetDistanceToTargetLocation(FVector2D TargetLocation);
	void SetCurRoom(ARoom* Room, bool IsPlayer);
	void SetCollisionImage(std::string_view CollisionImageName);

	/** ����/���� �޼ҵ� */
	void SetSpeed(float Speed) 
	{ 
		this->Speed = Speed;
	}
	float GetSpeed() 
	{ 
		return this->Speed; 
	}
	void SetCurDirection(FVector2D Direction)
	{
		CurDirection = Direction;
	}
	FVector2D GetCurDirection()
	{
		return CurDirection;
	}
	void SetCurrentHP(int HP)
	{
		this->CurrentHP = HP;
	}
	ARoom* GetCurRoom()
	{
		return CurRoom;
	}
	void SetRoomFloor(ERoomFloor RoomFloor)
	{
		this->CurRoomFloor = RoomFloor;
	}
	ERoomFloor GetRoomFloor()
	{
		return this->CurRoomFloor;
	}
	UEngineWinImage* GetCollisionImage()
	{
		return this->CollisionImage;
	}
protected:
	/** ���� ���� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	int MaxHP = 100;
	int CurrentHP = 40;
	float Speed = 80.0f;
	FVector2D CollisionSize = { 20.0f, 30.0f };

private:
	FVector2D CurDirection = FVector2D::ZERO;

	ARoom* CurRoom = nullptr;
	ERoomFloor CurRoomFloor = ERoomFloor::FLOOR_1F;
	UEngineWinImage* CollisionImage = nullptr;

};