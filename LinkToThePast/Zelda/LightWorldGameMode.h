#pragma once
#include "ZeldaGameMode.h"

class ARoom;
class AFade;
class APlayerCharacter;
class USpriteRenderer;

/**
 *	설명
 */
class ALightWorldGameMode : public AZeldaGameMode
{
public:
	/** 생성자, 소멸자 */
	ALightWorldGameMode();
	~ALightWorldGameMode();

	/** 객체 값 복사 방지 */
	ALightWorldGameMode(const ALightWorldGameMode& _Other) = delete;
	ALightWorldGameMode(ALightWorldGameMode&& _Other) noexcept = delete;
	ALightWorldGameMode& operator=(const ALightWorldGameMode& _Other) = delete;
	ALightWorldGameMode& operator=(ALightWorldGameMode&& _Other) noexcept = delete;

	/** 겟, 셋 메소드 */

protected:
	/** 액터 상속 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void LevelChangeStart() override;
	virtual void LevelChangeEnd() override;

	/** 룸 상속 메소드 */
	virtual void BeginPlayRoomActor() override;
	virtual void BeginPlayEnvActor() override;
	virtual void BeginPlayEnemyActor() override;

private:
	APlayerCharacter* Player = nullptr;
	AFade* Fade = nullptr;
	
	USpriteRenderer* WeatherRenderer = nullptr;
	USpriteRenderer* FadeRenderer = nullptr;
};

