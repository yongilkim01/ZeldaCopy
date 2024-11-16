#pragma once
#include <EngineCore/Actor.h>

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

	/** ĳ���� ���� �޼ҵ� */
	void AddCharacterLocation(FVector2D Location);
	FVector2D GetDirectionToTargetLocation(FVector2D TargetLocation);
	FVector2D GetNormalDirectionToTargetLocation(FVector2D TargetLocation);
	FVector2D GetNormalDirectionToThisLocation(FVector2D TargetLocation);
	float GetDistanceToTargetLocation(FVector2D TargetLocation);

	/** ����/���� �޼ҵ� */
	void SetSpeed(float Speed) { this->Speed = Speed; }
	float GetSpeed() { return this->Speed; }

protected:
	/** ���� ���� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	int MaxHP = 100;
	int CurrentHP = 40;
	float Speed = 80.0f;

private:

};