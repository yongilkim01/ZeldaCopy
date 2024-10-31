#include "PreCompile.h"
#include "ZeldaContentsCore.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/ImageManager.h>

#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineFile.h>

#include "PlayGameMode.h"
#include "Player.h"

ZeldaContentsCore::ZeldaContentsCore()
{
}

ZeldaContentsCore::~ZeldaContentsCore()
{
}

// 엔진이 실행되고 단 1번 실행된다.
void ZeldaContentsCore::BeginPlay()
{
	UEngineDirectory Dir;

	// 현재 디렉토리 Resources 디렉토리
	if (Dir.MoveParentToDirectory("Resources") == false)
	{
		MSGASSERT("리소스 폴더를 찾지 못했습니다.");
		return;
	}


	std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();

	for (size_t i = 0; i < ImageFiles.size(); i++)
	{
		std::string FilePath = ImageFiles[i].GetPathToString();
		UImageManager::GetInst().Load(FilePath);
	}

	UImageManager::GetInst().CuttingSprite("PlayerRunDown.png", { 64, 64 });

	//if(false == Dir.MoveParent)

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("A Link to the past");

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 1280, 720 });

	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");

	UEngineAPICore::GetCore()->OpenLevel("Play");
	// CreateLevel();

}

void ZeldaContentsCore::Tick()
{
}