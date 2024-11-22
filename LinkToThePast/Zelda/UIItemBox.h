#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class APlayerCharacter;

/**
 *	����
 */
class AUIItemBox : public AActor
{
public:
	/** ������, �Ҹ��� */
	AUIItemBox();
	~AUIItemBox();

	/** ��ü �� ���� ���� */
	AUIItemBox(const AUIItemBox& _Other) = delete;
	AUIItemBox(AUIItemBox&& _Other) noexcept = delete;
	AUIItemBox& operator=(const AUIItemBox& _Other) = delete;
	AUIItemBox& operator=(AUIItemBox&& _Other) noexcept = delete;

	/** ���� ��� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

private:
	USpriteRenderer* FrameRenderer = nullptr;
	USpriteRenderer* ItemRenderer = nullptr;


	APlayerCharacter* Player = nullptr;

};

