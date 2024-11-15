#include "PreCompile.h"
#include "EngineSound.h"

#include <EngineBase/EngineString.h>
#include <EngineBase/EngineDebug.h>

#ifdef _DEBUG
#pragma comment(lib, "fmodL_vc.lib")
#else
#pragma comment(lib, "fmod_vc.lib")
#endif

std::map<std::string, UEngineSound*> UEngineSound::Sounds;
// 사운드 관리 핸들
FMOD::System* SoundSystem = nullptr;

class SoundInit
{
public:
	SoundInit()
	{
		if (FMOD_RESULT::FMOD_OK != FMOD::System_Create(&SoundSystem))
		{
			MSGASSERT("FMOD 시스템 초기화에 실패했습니다.");
			return;
		}

		if (FMOD_RESULT::FMOD_OK != SoundSystem->init(32, FMOD_DEFAULT, nullptr))
		{
			MSGASSERT("FMOD 시스템 초기화에 실패했습니다.");
			return;
		}
	}
};

SoundInit SoundInitObject;

UEngineSound::UEngineSound()
{
}

UEngineSound::~UEngineSound()
{
}

bool UEngineSound::ResLoad(std::string_view Path)
{
	SoundSystem->createSound(Path.data(), FMOD_LOOP_NORMAL, nullptr, &SoundHandle);

	if (nullptr == SoundHandle)
	{
		MSGASSERT("사운드 로딩에 실패했습니다." + std::string(Path));
		return false;

	}

	return true;
}

void UEngineSound::Load(std::string_view Path)
{
	UEnginePath EnginePath = UEnginePath(Path);
	std::string FileName = EnginePath.GetFileName();

	UEngineSound::Load(FileName.data(), Path);
}

void UEngineSound::Load(std::string_view Name, std::string_view Path)
{
	// 이녀석은 UTF-8로 경로를 바꿔줘야 할수 있다.
	std::string UpperString = UEngineString::ToUpper(Name);

	UEngineSound* NewSound = new UEngineSound();


	if (false == NewSound->ResLoad(Path))
	{
		delete NewSound;
		MSGASSERT("사운드 로드에 실패했습니다" + UpperString);
		return;
	}
	;

	UEngineSound::Sounds.insert({ UpperString, NewSound });
	// Load(FileName, Path);
}

USoundPlayer UEngineSound::Play(std::string_view Name)
{
	std::string UpperName = UEngineString::ToUpper(Name);
	
	UEngineSound* FindSound = Find(Name);

	if (nullptr == FindSound)
	{
		MSGASSERT("로드하지 않은 사운드를 재생하려고 했습니다. " + UpperName);
	}

	FMOD::Channel* Ch = nullptr;

	SoundSystem->playSound(FindSound->SoundHandle, nullptr, false, &Ch);

	// 1번 재생
	Ch->setLoopCount(0);

	// 볼륨 1로
	Ch->setVolume(1.0f);

	USoundPlayer NewPlayer;
	NewPlayer.Control = Ch;
	return NewPlayer;
}

UEngineSound* UEngineSound::Find(std::string_view Name)
{
	std::string UpperString = UEngineString::ToUpper(Name);

	if (false == Sounds.contains(UpperString))
	{
		return nullptr;
	}

	return Sounds[UpperString];
}

void UEngineSound::Release()
{
	std::map<std::string, UEngineSound*>::iterator StartIter = Sounds.begin();
	std::map<std::string, UEngineSound*>::iterator EndIter = Sounds.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
			StartIter->second = nullptr;
		}
	}

	Sounds.clear();

	if (nullptr != SoundSystem)
	{
		SoundSystem->release();
		SoundSystem = nullptr;
	}
}


void UEngineSound::Update()
{
	if (nullptr == SoundSystem)
	{
		return;
	}

	if (FMOD_RESULT::FMOD_OK != SoundSystem->update())
	{
		MSGASSERT("FMOD 시스템 업데이트 오류.");
	}
}
