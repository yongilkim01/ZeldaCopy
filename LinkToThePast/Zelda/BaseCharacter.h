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

	void AddCharacterLocation(FVector2D Location);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	 
};