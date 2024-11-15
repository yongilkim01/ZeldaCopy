#pragma once
#include <EngineBase/EngineResources.h>
#include <map>

#include "ThirdParty/FMOD/inc/fmod.hpp"

/**
 *	사운드 플레이어 클래스
 *	재생하는 사운드에 대한 볼륨 및 정보
 */
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
		Control->setPaused(false);
	}
	void OnOffSiwtch()
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

	void Loop(int Count = -1)
	{
		Control->setLoopCount(Count);
	}

private:
	FMOD::Channel* Control = nullptr;
};

/**
 *	설명
 */
class UEngineSound : public UEngineResources
{
public:
	/** 생성자, 소멸자 */
	UEngineSound();
	~UEngineSound();

	/** 객체 값 복사 방지 */
	UEngineSound(const UEngineSound& _Other) = delete;
	UEngineSound(UEngineSound&& _Other) noexcept = delete;
	UEngineSound& operator=(const UEngineSound& _Other) = delete;
	UEngineSound& operator=(UEngineSound&& _Other) noexcept = delete;

	static void Load(std::string_view Path);
	static void Load(std::string_view Name, std::string_view Path);
	static USoundPlayer Play(std::string_view Name);
	static UEngineSound* Find(std::string_view Name);

	static void Release();
	static void Update();

protected:

private:
	static std::map<std::string, UEngineSound*> Sounds;

	bool ResLoad(std::string_view Path);

	FMOD::Sound* SoundHandle;

};

