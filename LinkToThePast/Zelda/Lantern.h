#pragma once
#include "WeaponItem.h"
#include <EnginePlatform/EngineSound.h>

/**
 *	설명
 */
class ALantern : public AWeaponItem
{
public:
	/** 생성자, 소멸자 */
	ALantern();
	~ALantern();

	/** 객체 값 복사 방지 */
	ALantern(const ALantern& _Other) = delete;
	ALantern(ALantern&& _Other) noexcept = delete;
	ALantern& operator=(const ALantern& _Other) = delete;
	ALantern& operator=(ALantern&& _Other) noexcept = delete;

	/** 액터 상속 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	/** 웨폰 액터 상속 메소드 */
	virtual void Action(float Tick) override;

protected:

private:
	USoundPlayer SoundPlayer;

};

