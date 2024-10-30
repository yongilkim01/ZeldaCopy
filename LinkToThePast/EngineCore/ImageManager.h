#pragma once
#include <list>
#include <vector>
#include <map>
#include <string>

#include <EnginePlatform/EngineWinImage.h>
#include "EngineSprite.h"

// Ό³Έν :
class UImageManager
{
public:
	// constrcuter destructer
	~UImageManager();

	// delete Function
	UImageManager(const UImageManager& _Other) = delete;
	UImageManager(UImageManager&& _Other) noexcept = delete;
	UImageManager& operator=(const UImageManager& _Other) = delete;
	UImageManager& operator=(UImageManager&& _Other) noexcept = delete;

	static UImageManager& GetInst()
	{
		static UImageManager Inst;
		return Inst;
	}

	void Load(std::string_view Path);
	void Load(std::string_view KeyName, std::string_view Path);

	void CuttingSprite(std::string_view KeyName, FVector2D CuttingSize);

	bool IsLoadSprite(std::string_view KeyName);
	UEngineSprite* FindSprite(std::string_view KeyName);

protected:

private:
	UImageManager();

	std::map<std::string, UEngineWinImage*> Images;
	std::map<std::string, UEngineSprite*> Sprites;
};

