#include "PreCompile.h"
#include "SoundManager.h"


void USoundManager::PlayBGMSound(std::string SoundName)
{
	///SoundName += ".wav";
	BackgroundSoundPlayer.Stop();
	BackgroundSoundPlayer = UEngineSound::Play(SoundName);
	BackgroundSoundPlayer.Loop();
}

void USoundManager::PlayEffectSound(std::string SoundName)
{
	EffectSoundPlayer = UEngineSound::Play(SoundName);
}

void USoundManager::PlayEnvSound(std::string SoundName)
{
	EnvSoundPlayer = UEngineSound::Play(SoundName);
	EnvSoundPlayer.Loop();
}

void USoundManager::StopBGMSound()
{
	BackgroundSoundPlayer.Stop();
}

void USoundManager::StopEffectSound()
{
	EffectSoundPlayer.Stop();
}

void USoundManager::StopEnvSound()
{
	EnvSoundPlayer.Stop();
}

USoundManager::USoundManager()
{
}


USoundManager::~USoundManager()
{
}