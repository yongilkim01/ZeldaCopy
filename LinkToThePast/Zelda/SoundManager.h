#pragma once
#include <EnginePlatform/EngineSound.h>

enum class ESoundFileType
{
	WAV,
	MP3,
};


/**
 *	����
 */
class USoundManager
{
public:
	static USoundManager& GetInstance()
	{
		static USoundManager Inst = USoundManager();
		return Inst;
	}

	/** ������, �Ҹ��� */
	~USoundManager();

	/** ��ü �� ���� ���� */
	USoundManager(const USoundManager& Other) = delete;
	USoundManager(USoundManager&& Other) noexcept = delete;
	USoundManager& operator=(const USoundManager& Other) = delete;
	USoundManager& operator=(USoundManager&& Other) noexcept = delete;

	/** ��, �� �޼ҵ� */
	void PlayBGM(std::string SoundName);
protected:

private:
	USoundManager();

	USoundPlayer BackgroundSoundPlayer;
};