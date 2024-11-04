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

// ������ ����ǰ� �� 1�� ����ȴ�.
void ZeldaContentsCore::BeginPlay()
{

	UEngineDirectory Dir;
	if (false == Dir.MoveParentToDirectory("Resources"))
	{
		MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
		return;
	}

	// ��� ���� �� ������
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

	// �̰� �� ȣ������� �մϴ�.
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 768, 672 });

	UEngineAPICore::GetCore()->CreateLevel<ARoomManageMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");

	UEngineAPICore::GetCore()->OpenLevel("Title");

}

void ZeldaContentsCore::Tick()
{
}