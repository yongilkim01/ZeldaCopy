#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class APlayerCharacter;

/**
 *	설명
 */
class AUIItemBox : public AActor
{
public:
	/** 생성자, 소멸자 */
	AUIItemBox();
	~AUIItemBox();

	/** 객체 값 복사 방지 */
	AUIItemBox(const AUIItemBox& _Other) = delete;
	AUIItemBox(AUIItemBox&& _Other) noexcept = delete;
	AUIItemBox& operator=(const AUIItemBox& _Other) = delete;
	AUIItemBox& operator=(AUIItemBox&& _Other) noexcept = delete;

	/** 액터 상속 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

private:
	USpriteRenderer* FrameRenderer = nullptr;
	USpriteRenderer* ItemRenderer = nullptr;


	APlayerCharacter* Player = nullptr;

};

