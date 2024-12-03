#pragma once
#include <EngineBase/EngineResources.h>
#include <map>

#include "ThirdParty/FMOD/inc/fmod.hpp"
#include "math.h"

class USoundPlayer
{
public:
	friend class UEngineSound;

	void On()
	{
		Control->setPaused(false);
	}

	void Off()
	{
		Control->setPaused(true);
	}

	void Stop()
	{
		Control->stop();
	}

	void SetVolume(float Volume)
	{
		Volume = UEngineMath::Clamp(Volume, 0.0f, 1.0f);

		Control->setVolume(Volume);
	}

	void OnOffSwtich()
	{
		bool Check = false;
		Control->getPaused(&Check);

		if (true == Check)
		{
			Control->setPaused(false);
		}
		else
		{
			Control->setPaused(true);
		}
	}

	void SetPosition(unsigned int Value)
	{
		Control->setPosition(Value, FMOD_TIMEUNIT_MS);
	}

	void Loop(int Count = -1)
	{
		Control->setLoopCount(Count);
	}

	void ReStart()
	{
		SetPosition(0);
	}

	unsigned int LengthMs()
	{
		unsigned int ResultLength = 0;
		SoundHandle->getLength(&ResultLength, FMOD_TIMEUNIT_MS);
		return ResultLength;
	}

private:
	FMOD::Channel* Control = nullptr;
	FMOD::Sound* SoundHandle = nullptr;;
};

class UEngineSound : public UEngineResources
{
public:
	/** 생성자, 소멸자 */
	UEngineSound();
	~UEngineSound();

	/** 객체 값 복사 방지 */
	UEngineSound(const UEngineSound& Other) = delete;
	UEngineSound(UEngineSound&& Other) noexcept = delete;
	UEngineSound& operator=(const UEngineSound& Other) = delete;
	UEngineSound& operator=(UEngineSound&& Other) noexcept = delete;

	static void Load(std::string_view Path);
	static void Load(std::string_view Name, std::string_view Path);
	static USoundPlayer Play(std::string_view Name);
	static UEngineSound* Find(std::string_view Name);

	static void Release();
	static void Update();

protected:

private:
	static std::map<std::string, UEngineSound*> Sounds;

	FMOD::Sound* SoundHandle;

	bool ResLoad(std::string_view Path);
};

