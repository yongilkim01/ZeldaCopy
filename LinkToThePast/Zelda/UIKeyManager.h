#pragma once
#include <EngineCore/Actor.h>

class AHUDText;
class USpriteRenderer;

/**
 *	설명
 */
class AUIKeyManager : public AActor
{
public:
	/** 생성자, 소멸자 */
	AUIKeyManager();
	~AUIKeyManager();

	/** 객체 값 복사 방지 */
	AUIKeyManager(const AUIKeyManager& _Other) = delete;
	AUIKeyManager(AUIKeyManager&& _Other) noexcept = delete;
	AUIKeyManager& operator=(const AUIKeyManager& _Other) = delete;
	AUIKeyManager& operator=(AUIKeyManager&& _Other) noexcept = delete;

	/** 액터 상속 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

private:
	USpriteRenderer* Renderer = nullptr;
	AHUDText* UIText = nullptr;

};