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

// 엔진이 실행되고 단 1번 실행된다.
void ZeldaContentsCore::BeginPlay()
{
	// UEngineDirectory Dir = "C:\\AAA";

	UEngineDirectory Dir;

	// 상대경로가 중요하다.
	// 상대 경로의 핵심은 이것이다.
	// 내가 어디서 실행됐는지는 중요하지 않아야 한다.
	// 선생님은 게임이 없기 때문이고.
	// 여려분들은 레벨에서 하는걸 권장합니다.
	// Global / 레벨에 관련된 

	// 상대경로 어디든 내 프로젝트의 폴더 안에 있는 Resources찾는 방식으로 처리했다.
	// 
	// if (false == Dir.MoveParentToDirectory("fasdjklfadsjklf"))
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

	// 일반 텍스처가 다 로딩되면
	// 자르는 작업을 아래서 해주는게 좋다.

	UImageManager::GetInst().CuttingSprite("Player_Right.png", { 128, 128 });

	//{
	//	UEngineDirectory BombDir;
	//	BombDir.MoveParentToDirectory("Resources");
	//	BombDir.Append("bomb");
	//	UImageManager::GetInst().LoadFolder(BombDir.GetPathToString());
	//}

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("EduWindow");

	// 이거 꼭 호출해줘야 합니다.
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 1280, 720 });

	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");
	//UEngineAPICore::GetCore()->CreateLevel("End");

	UEngineAPICore::GetCore()->OpenLevel("Title");

}

void ZeldaContentsCore::Tick()
{
}