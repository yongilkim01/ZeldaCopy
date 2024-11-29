#include "PreCompile.h"
#include "SoundManager.h"


void USoundManager::PlayBGM(std::string SoundName)
{
	///SoundName += ".wav";
	//BackgroundSoundPlayer.Stop();
	BackgroundSoundPlayer = UEngineSound::Play(SoundName);
	BackgroundSoundPlayer.Loop();
}

USoundManager::USoundManager()
{
}


USoundManager::~USoundManager()
{
}