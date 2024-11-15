#pragma once
#include <EngineBase/EngineResources.h>
#include <map>

#include "ThirdParty/FMOD/inc/fmod.hpp"

/**
 *	���� �÷��̾� Ŭ����
 *	����ϴ� ���忡 ���� ���� �� ����
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
 *	����
 */
class UEngineSound : public UEngineResources
{
public:
	/** ������, �Ҹ��� */
	UEngineSound();
	~UEngineSound();

	/** ��ü �� ���� ���� */
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

