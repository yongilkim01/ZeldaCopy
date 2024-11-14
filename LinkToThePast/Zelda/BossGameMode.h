#pragma once
#include "ZeldaGameMode.h"

/**
 *	설명
 */
class ABossGameMode : public AZeldaGameMode
{
public:
	/** 생성자, 소멸자 */
	ABossGameMode();
	~ABossGameMode();

	/** 객체 값 복사 방지 */
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

