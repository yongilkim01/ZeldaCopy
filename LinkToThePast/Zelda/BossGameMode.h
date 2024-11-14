#pragma once
#include "ZeldaGameMode.h"

/**
 *	����
 */
class ABossGameMode : public AZeldaGameMode
{
public:
	/** ������, �Ҹ��� */
	ABossGameMode();
	~ABossGameMode();

	/** ��ü �� ���� ���� */
	ABossGameMode(const ABossGameMode& _Other) = delete;
	ABossGameMode(ABossGameMode&& _Other) noexcept = delete;
	ABossGameMode& operator=(const ABossGameMode& _Other) = delete;
	ABossGameMode& operator=(ABossGameMode&& _Other) noexcept = delete;

public:
	void RoomBeginPlay();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

};

