#include "PreCompile.h"
#include "ZeldaContentsCore.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/ImageManager.h>

#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineFile.h>

#include "TitleGameMode.h"
#include "PlayGameMode.h"
#include "Player.h"
#include "RoomManageMode.h"

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
	if (false == Dir.MoveParentToDirectory("Resources"))
	{
		MSGASSERT("리소스 폴더를 찾지 못했습니다.");
		return;
	}

	// 모든 파일 다 얻어낸다음
	std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();

	for (size_t i = 0; i < ImageFiles.size(); i++)
	{
		std::string FilePath = ImageFiles[i].GetPathToString();
		UImageManager::GetInst().Load(FilePath);
	}

	UImageManager::GetInst().CuttingSprite("LinkMoveDown.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkMoveRight.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkMoveUp.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkMoveLeft.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkAttackRight.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkAttackLeft.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkAttackUp.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkAttackDown.png", { 64, 64 });


	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("A link to the past");

	// 이거 꼭 호출해줘야 합니다.
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 768, 672 });

	UEngineAPICore::GetCore()->CreateLevel<ARoomManageMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");

	UEngineAPICore::GetCore()->OpenLevel("Title");

}

void ZeldaContentsCore::Tick()
{
}