#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class UCollision2D;
class ABaseCharacter;

/**
 *	설명
 */
class AEventActor : public AActor
{
public:
	/** 생성자, 소멸자 */
	AEventActor();
	~AEventActor();

	/** 객체 값 복사 방지 */
	AEventActor(const AEventActor& _Other) = delete;
	AEventActor(AEventActor&& _Other) noexcept = delete;
	AEventActor& operator=(const AEventActor& _Other) = delete;
	AEventActor& operator=(AEventActor&& _Other) noexcept = delete;

	/** 액터 공통 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DetlaTime) override;

	/** 이벤트 액터 공통 메소드 */
	virtual void Interact(ABaseCharacter* Character) {}

protected:
	USpriteRenderer* SpriteRenderer = nullptr;
	UCollision2D* Collision = nullptr;

private:

};

