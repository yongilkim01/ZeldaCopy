#pragma once
#include "WeaponItem.h"

/**
 *	설명
 */
class ABow : public AWeaponItem
{
public:
	/** 생성자, 소멸자 */
	ABow();
	~ABow();

	/** 객체 값 복사 방지 */
	ABow(const ABow& _Other) = delete;
	ABow(ABow&& _Other) noexcept = delete;
	ABow& operator=(const ABow& _Other) = delete;
	ABow& operator=(ABow&& _Other) noexcept = delete;

	/** 액터 상속 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** 웨폰 액터 상속 메소드 */
	virtual void Action(float DeltaTime) override;

protected:

private:

};

