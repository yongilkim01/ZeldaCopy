#pragma once
#include "WeaponItem.h"
#include <EnginePlatform/EngineSound.h>

/**
 *	����
 */
class ALantern : public AWeaponItem
{
public:
	/** ������, �Ҹ��� */
	ALantern();
	~ALantern();

	/** ��ü �� ���� ���� */
	ALantern(const ALantern& _Other) = delete;
	ALantern(ALantern&& _Other) noexcept = delete;
	ALantern& operator=(const ALantern& _Other) = delete;
	ALantern& operator=(ALantern&& _Other) noexcept = delete;

	/** ���� ��� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	/** ���� ���� ��� �޼ҵ� */
	virtual void Action(float Tick) override;

protected:

private:
	USoundPlayer SoundPlayer;

};

