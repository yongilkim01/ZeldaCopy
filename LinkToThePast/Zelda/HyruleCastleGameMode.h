#pragma once
#include "ZeldaGameMode.h"

/**
 *	설명
 */
class AHyruleCastleGameMode : public AZeldaGameMode
{
public:
	/** 생성자, 소멸자 */
	AHyruleCastleGameMode();
	~AHyruleCastleGameMode();

	/** 객체 값 복사 방지 */
	AHyruleCastleGameMode(const AHyruleCastleGameMode& _Other) = delete;
	AHyruleCastleGameMode(AHyruleCastleGameMode&& _Other) noexcept = delete;
	AHyruleCastleGameMode& operator=(const AHyruleCastleGameMode& _Other) = delete;
	AHyruleCastleGameMode& operator=(AHyruleCastleGameMode&& _Other) noexcept = delete;

	/** 액터 상속 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** 젤다 게임모드 상속 메소드 */
	void RoomBeginPlay();

protected:

private:

};

