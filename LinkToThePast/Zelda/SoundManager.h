#pragma once
#include <EnginePlatform/EngineSound.h>

enum class ESoundFileType
{
	WAV,
	MP3,
};


/**
 *	설명
 */
class USoundManager
{
public:
	static USoundManager& GetInstance()
	{
		static USoundManager Inst = USoundManager();
		return Inst;
	}

	/** 생성자, 소멸자 */
	~USoundManager();

	/** 객체 값 복사 방지 */
	USoundManager(const USoundManager& Other) = delete;
	USoundManager(USoundManager&& Other) noexcept = delete;
	USoundManager& operator=(const USoundManager& Other) = delete;
	USoundManager& operator=(USoundManager&& Other) noexcept = delete;

	/** 겟, 셋 메소드 */
	void PlayBGMSound(std::string SoundName);
	void PlayEffectSound(std::string SoundName);
	void PlayEnvSound(std::string SoundName);

	void StopBGMSound();
	void StopEffectSound();
	void StopEnvSound();
protected:

private:
	USoundManager();

	USoundPlayer BackgroundSoundPlayer;
	USoundPlayer EffectSoundPlayer;
	USoundPlayer EnvSoundPlayer;
};