#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;

/**
 *	설명
 */
class AHouseBed : public AActor
{
public:
	/** 생성자, 소멸자 */
	AHouseBed();
	~AHouseBed();

	/** 객체 값 복사 방지 */
	AHouseBed(const AHouseBed& _Other) = delete;
	AHouseBed(AHouseBed&& _Other) noexcept = delete;
	AHouseBed& operator=(const AHouseBed& _Other) = delete;
	AHouseBed& operator=(AHouseBed&& _Other) noexcept = delete;

	/** 클래스 메소드 */

	/** 겟, 셋 메소드 */

protected:
	/** 액터 상속 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	USpriteRenderer* SpriteRenderer = nullptr;
};

