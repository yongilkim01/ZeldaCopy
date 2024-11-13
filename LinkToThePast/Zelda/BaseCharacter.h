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

	void AddCharacterLocation(FVector2D Location);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	 
};