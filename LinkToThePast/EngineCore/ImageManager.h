#pragma once
#include <list>
#include <vector>
#include <map>
#include <string>

#include <EnginePlatform/EngineWinImage.h>
#include "EngineSprite.h"

// ���� :
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

	void LoadFolder(std::string_view Path);
	void LoadFolder(std::string_view KeyName, std::string_view Path);

	void CuttingSprite(std::string_view _KeyName, int _X, int _Y);
	void CuttingSprite(std::string_view KeyName, FVector2D CuttingSize);
	void CuttingSprite(std::string_view NewSpriteName,
		std::string_view ImageName,
		FVector2D CuttingSize);
	void CreateCutSprite(std::string_view _SearchKeyName,
		std::string_view _NewSpriteKeyName,
		FVector2D _StartPos,
		FVector2D _CuttingSize,
		FVector2D _XYOffSet,
		UINT _Xcount,
		UINT _ImageCount);

	bool IsLoadSprite(std::string_view KeyName);
	UEngineSprite* FindSprite(std::string_view KeyName);
	UEngineWinImage* FindImage(std::string_view KeyName);

protected:

private:
	UImageManager();

	std::map<std::string, UEngineWinImage*> Images;
	std::map<std::string, UEngineSprite*> Sprites;
};

