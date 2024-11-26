#pragma once
#include <EngineCore/Actor.h>
#include <EnginePlatform/EngineSound.h>

enum class ETitleState
{
	NONE,
	LOGO,
	TRIFORCE,
	TITLELOGO,
	SWORDLOGO,
	TITLE
};

class USpriteRenderer;

/**
 *	설명
 */
class ATitleManager : public AActor

{
public:
	/** 생성자, 소멸자 */
	ATitleManager();
	~ATitleManager();

	/** 객체 값 복사 방지 */
	ATitleManager(const ATitleManager& _Other) = delete;
	ATitleManager(ATitleManager&& _Other) noexcept = delete;
	ATitleManager& operator=(const ATitleManager& _Other) = delete;
	ATitleManager& operator=(ATitleManager&& _Other) noexcept = delete;

	/** 액터 상속 메소드 */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** 타이틀 메인 상태 */
	void StartLogo();
	void StartTriforce();
	void StartTitleLogo();
	void StartSwordLogo();
	void StartTitle();

	void Logo(float DeltaTime);
	void Triforce(float DeltaTime);
	void TitleLogo(float DeltaTime);
	void SwordLogo(float DeltaTime);
	void Title(float DeltaTime);

	void ChangeState(ETitleState State);

protected:

private:
	USpriteRenderer* BackgroundRenderer = nullptr;
	USpriteRenderer* LogoRenderer = nullptr;
	USpriteRenderer* FadeRenderer = nullptr;
	USpriteRenderer* TitleRenderer = nullptr;
	USpriteRenderer* TitleZRenderer = nullptr;
	USpriteRenderer* SwordRenderer = nullptr;
	USpriteRenderer* EnvRenderer = nullptr;

	// 379, 0
	// 379 256

	std::vector<USpriteRenderer*> Triforces;
	std::vector<FVector2D> TriforceLocations;
	std::vector<FVector2D> TriforceFinalLocations;

	FVector2D SwordInitLocation = FVector2D(211, -306);
	FVector2D SwordFinalLocation = FVector2D(211, 306);
	FVector2D EnvInitLocation = FVector2D::ZERO;

	FVector2D TitleZLocation = FVector2D(229 - 31, 60 - 72);

	ETitleState TitleState = ETitleState::NONE;

	USoundPlayer EffectSoundPlayer;
	USoundPlayer BackgroundSoundPlayer;

	float CurTime = 0.0f;

	float LogoTime = 0.0f;
	float FadeValue = 0.0f;
	float TriforceDistance = 400.0f;
	float TriforceSpeed = 47.0f;
	float TitleAlpha = 0.0f;
};

