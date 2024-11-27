#pragma once
#include <EngineCore/Actor.h>

class AHUDText;
class USpriteRenderer;

/**
 *	설명
 */
class AUIRupeeManager : public AActor
{
public:
	/** 생성자, 소멸자 */
	AUIRupeeManager();
	~AUIRupeeManager();

	/** 객체 값 복사 방지 */
	AUIRupeeManager(const AUIRupeeManager& _Other) = delete;
	AUIRupeeManager(AUIRupeeManager&& _Other) noexcept = delete;
	AUIRupeeManager& operator=(const AUIRupeeManager& _Other) = delete;
	AUIRupeeManager& operator=(AUIRupeeManager&& _Other) noexcept = delete;

	/** 액터 상속 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:

private:
	USpriteRenderer* Renderer = nullptr;
	AHUDText* UIText = nullptr;

};