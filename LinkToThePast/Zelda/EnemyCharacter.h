#pragma once
#include <EngineCore/Actor.h>

/**
 *	����
 */
class AEnemyCharacter : public AActor
{
public:
	/** ������, �Ҹ��� */
	AEnemyCharacter();
	~AEnemyCharacter();

	/** ��ü �� ���� ���� */
	AEnemyCharacter(const AEnemyCharacter& _Other) = delete;
	AEnemyCharacter(AEnemyCharacter&& _Other) noexcept = delete;
	AEnemyCharacter& operator=(const AEnemyCharacter& _Other) = delete;
	AEnemyCharacter& operator=(AEnemyCharacter&& _Other) noexcept = delete;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

};

