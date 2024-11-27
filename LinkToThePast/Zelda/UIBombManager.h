#pragma once
#include <EngineCore/Actor.h>

class AHUDText;
class USpriteRenderer;

/**
 *	설명
 */
class AUIBombManager : public AActor
{
public:
	/** 생성자, 소멸자 */
	AUIBombManager();
	~AUIBombManager();

	/** 객체 값 복사 방지 */
	AUIBombManager(const AUIBombManager& _Other) = delete;
	AUIBombManager(AUIBombManager&& _Other) noexcept = delete;
	AUIBombManager& operator=(const AUIBombManager& _Other) = delete;
	AUIBombManager& operator=(AUIBombManager&& _Other) noexcept = delete;

	/** 액터 상속 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

private:
	USpriteRenderer* Renderer = nullptr;
	AHUDText* UIText = nullptr;

};