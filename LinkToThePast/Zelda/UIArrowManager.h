#pragma once
#include <EngineCore/Actor.h>

class AHUDText;
class USpriteRenderer;

/**
 *	설명
 */
class AUIArrowManager : public AActor
{
public:
	/** 생성자, 소멸자 */
	AUIArrowManager();
	~AUIArrowManager();

	/** 객체 값 복사 방지 */
	AUIArrowManager(const AUIArrowManager& _Other) = delete;
	AUIArrowManager(AUIArrowManager&& _Other) noexcept = delete;
	AUIArrowManager& operator=(const AUIArrowManager& _Other) = delete;
	AUIArrowManager& operator=(AUIArrowManager&& _Other) noexcept = delete;

	/** 액터 상속 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

private:
	USpriteRenderer* Renderer = nullptr;
	AHUDText* UIText = nullptr;

};