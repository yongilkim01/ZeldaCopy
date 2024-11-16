#include "PreCompile.h"
#include "ZeldaCore.h"

#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineFile.h>

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/ImageManager.h>

#include "PlayerCharacter.h"
#include "TitleGameMode.h"
#include "ZeldaGameMode.h"
#include "DungeonGameMode.h"
#include "BossGameMode.h"

UZeldaCore::UZeldaCore()
{
}

UZeldaCore::~UZeldaCore()
{
}

void UZeldaCore::BeginPlay()
{
	// �̹����ε�
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
			return;
		}
		Dir.Append("Image");
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UImageManager::GetInst().Load(FilePath);
		}
	}

	// ���� �ε�
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
			return;
		}
		Dir.Append("Sound");
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineSound::Load(FilePath);
		}
	}

	UImageManager::GetInst().CuttingSprite("LinkMoveDown.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkMoveRight.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkMoveUp.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkMoveLeft.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkAttackRight.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkAttackLeft.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkAttackUp.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkAttackDown.png", { 64, 64 });

	UImageManager::GetInst().CuttingSprite("LinkKnockBackRight.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkKnockBackLeft.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkKnockBackUp.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkKnockBackDown.png", { 64, 64 });

	UImageManager::GetInst().CuttingSprite("HylianKnightMoveRight.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("HylianKnightMoveLeft.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("HylianKnightMoveUp.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("HylianKnightMoveDown.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("HylianKnightHit.png", { 64, 64 });

	UImageManager::GetInst().CuttingSprite("ArmosKnightHit.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("ArmosKnightDeath.png", { 64, 64 });

	UImageManager::GetInst().CuttingSprite("EnemyDeathEffect.png", { 64, 64 });


	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("A link to the past");

	// �̰� �� ȣ������� �մϴ�.
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 768, 672 });

	UEngineAPICore::GetCore()->CreateLevel<ACastleDungeonGameMode, APlayerCharacter>("CastleDungeon");
	UEngineAPICore::GetCore()->CreateLevel<ABossGameMode, APlayerCharacter>("Boss");
	//UEngineAPICore::GetCore()->CreateLevel<ARoomManageMode, APlayer>("Play");
	//UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");

	UEngineAPICore::GetCore()->OpenLevel("Boss");
}

void UZeldaCore::Tick()
{
}

