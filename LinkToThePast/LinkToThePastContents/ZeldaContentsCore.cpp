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

ZeldaContentsCore::ZeldaContentsCore()
{
}

ZeldaContentsCore::~ZeldaContentsCore()
{
}

// ������ ����ǰ� �� 1�� ����ȴ�.
void ZeldaContentsCore::BeginPlay()
{
	// UEngineDirectory Dir = "C:\\AAA";

	UEngineDirectory Dir;

	// ����ΰ� �߿��ϴ�.
	// ��� ����� �ٽ��� �̰��̴�.
	// ���� ��� ����ƴ����� �߿����� �ʾƾ� �Ѵ�.
	// �������� ������ ���� �����̰�.
	// �����е��� �������� �ϴ°� �����մϴ�.
	// Global / ������ ���õ� 

	// ����� ���� �� ������Ʈ�� ���� �ȿ� �ִ� Resourcesã�� ������� ó���ߴ�.
	// 
	// if (false == Dir.MoveParentToDirectory("fasdjklfadsjklf"))
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

	// �Ϲ� �ؽ�ó�� �� �ε��Ǹ�
	// �ڸ��� �۾��� �Ʒ��� ���ִ°� ����.

	UImageManager::GetInst().CuttingSprite("Player_Right.png", { 128, 128 });

	//{
	//	UEngineDirectory BombDir;
	//	BombDir.MoveParentToDirectory("Resources");
	//	BombDir.Append("bomb");
	//	UImageManager::GetInst().LoadFolder(BombDir.GetPathToString());
	//}

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("EduWindow");

	// �̰� �� ȣ������� �մϴ�.
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 1280, 720 });

	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");
	//UEngineAPICore::GetCore()->CreateLevel("End");

	UEngineAPICore::GetCore()->OpenLevel("Title");

}

void ZeldaContentsCore::Tick()
{
}