#pragma once
#include <EngineCore/Actor.h>

class ABaseCharacter : public AActor
{
public:
	/** 생성자, 소멸자 */
	ABaseCharacter();
	~ABaseCharacter();

	/** 객체 값 복사 방지 */
	ABaseCharacter(const ABaseCharacter& _Other) = delete;
	ABaseCharacter(ABaseCharacter&& _Other) noexcept = delete;
	ABaseCharacter& operator=(const ABaseCharacter& _Other) = delete;
	ABaseCharacter& operator=(ABaseCharacter&& _Other) noexcept = delete;

	/** 캐릭터 가상 메소드 */
	virtual void TakeDamage(int Damage, ABaseCharacter* Character) {}
	virtual void Death() {}

	/** 캐릭터 공통 메소드 */
	void AddCharacterLocation(FVector2D Location);
	FVector2D GetDirectionToTargetLocation(FVector2D TargetLocation);
	FVector2D GetDirectionToThisLocation(FVector2D TargetLocation);
	FVector2D GetNormalDirectionToTargetLocation(FVector2D TargetLocation);
	FVector2D GetNormalDirectionToThisLocation(FVector2D TargetLocation);
	float GetDistanceToTargetLocation(FVector2D TargetLocation);

	/** 게터/세터 메소드 */
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
protected:
	/** 액터 가상 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	int MaxHP = 100;
	int CurrentHP = 40;
	float Speed = 80.0f;

private:
	FVector2D CurDirection = FVector2D::ZERO;
};