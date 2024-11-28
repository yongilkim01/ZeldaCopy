#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;

/**
 *	����
 */
class AHouseBed : public AActor
{
public:
	/** ������, �Ҹ��� */
	AHouseBed();
	~AHouseBed();

	/** ��ü �� ���� ���� */
	AHouseBed(const AHouseBed& _Other) = delete;
	AHouseBed(AHouseBed&& _Other) noexcept = delete;
	AHouseBed& operator=(const AHouseBed& _Other) = delete;
	AHouseBed& operator=(AHouseBed&& _Other) noexcept = delete;

	/** Ŭ���� �޼ҵ� */

	/** ��, �� �޼ҵ� */

protected:
	/** ���� ��� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	USpriteRenderer* SpriteRenderer = nullptr;
};

