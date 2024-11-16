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

	/** 캐릭터 공통 메소드 */
	void AddCharacterLocation(FVector2D Location);

	/** 게터/세터 메소드 */
	void SetSpeed(float Speed) { this->Speed = Speed; }
	float GetSpeed() { return this->Speed; }

protected:
	/** 액터 가상 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	int MaxHP = 100;
	int CurrentHP = 40;
	float Speed = 80.0f;

private:

};