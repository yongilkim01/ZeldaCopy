#pragma once
#include "EventActor.h"

/**
 *	설명
 */
class APot : public AEventActor
{
public:
	/** 생성자, 소멸자 */
	APot();
	~APot();

	/** 객체 값 복사 방지 */
	APot(const APot& _Other) = delete;
	APot(APot&& _Other) noexcept = delete;
	APot& operator=(const APot& _Other) = delete;
	APot& operator=(APot&& _Other) noexcept = delete;

	/** 액터 공통 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** 이벤트 액터 공통 메소드 */
	virtual void Interact(ABaseCharacter* Character) override;

protected:

private:

};

