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
 *	����
 */
class ATitleManager : public AActor

{
public:
	/** ������, �Ҹ��� */
	ATitleManager();
	~ATitleManager();

	/** ��ü �� ���� ���� */
	ATitleManager(const ATitleManager& _Other) = delete;
	ATitleManager(ATitleManager&& _Other) noexcept = delete;
	ATitleManager& operator=(const ATitleManager& _Other) = delete;
	ATitleManager& operator=(ATitleManager&& _Other) noexcept = delete;

	/** ���� ��� �޼ҵ� */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** Ÿ��Ʋ ���� ���� */
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

	// 379, 0
	// 379 256

	std::vector<USpriteRenderer*> Triforces;
	std::vector<FVector2D> TriforceLocations;
	std::vector<FVector2D> TriforceFinalLocations;

	ETitleState TitleState = ETitleState::NONE;

	USoundPlayer EffectSoundPlayer;
	USoundPlayer BackgroundSoundPlayer;

	float CurTime = 0.0f;

	float LogoTime = 0.0f;
	float FadeValue = 0.0f;
	float TriforceDistance = 400.0f;
	float TriforceSpeed = 47.0f;
};

