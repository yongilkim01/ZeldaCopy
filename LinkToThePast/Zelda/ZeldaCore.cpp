#include "PreCompile.h"
#include "ZeldaCore.h"

#include "PlayerCharacter.h"
#include "ZeldaGameMode.h"
#include "TitleGameMode.h"
#include "DungeonGameMode.h"
#include "HyruleCastleGameMode.h"
#include "BossGameMode.h"

#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineFile.h>

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/ImageManager.h>

UZeldaCore::UZeldaCore()
{
}

UZeldaCore::~UZeldaCore()
{
	UEngineSound::Release();
}

void UZeldaCore::BeginPlay()
{
	// 이미지로드
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
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

	// 사운드 로드
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
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

	UImageManager::GetInst().CuttingSprite("LinkShieldMoveDown.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkShieldMoveRight.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkShieldMoveUp.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkShieldMoveLeft.png", { 64, 64 });

	UImageManager::GetInst().CuttingSprite("LinkAttackRight.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkAttackLeft.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkAttackUp.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkAttackDown.png", { 64, 64 });

	UImageManager::GetInst().CuttingSprite("LinkKnockBackRight.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkKnockBackLeft.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkKnockBackUp.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkKnockBackDown.png", { 64, 64 });

	UImageManager::GetInst().CuttingSprite("LinkLiftRight.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkLiftLeft.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkLiftUp.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkLiftDown.png", { 64, 64 });

	UImageManager::GetInst().CuttingSprite("LinkBowRight.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkBowLeft.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkBowUp.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("LinkBowDown.png", { 64, 64 });

	UImageManager::GetInst().CuttingSprite("HylianKnightMoveRight.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("HylianKnightMoveLeft.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("HylianKnightMoveUp.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("HylianKnightMoveDown.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("HylianKnightHit.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("HylianKnightFall.png", { 64, 64 });

	UImageManager::GetInst().CuttingSprite("CastleKnightMoveRight.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("CastleKnightMoveLeft.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("CastleKnightMoveUp.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("CastleKnightMoveDown.png", { 64, 64 });

	UImageManager::GetInst().CuttingSprite("ArmosKnightHit.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("ArmosKnightDeath.png", { 64, 64 });

	UImageManager::GetInst().CuttingSprite("PotBreak.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("Arrow.png", { 64, 64 });

	UImageManager::GetInst().CuttingSprite("Chest.png", { 48, 48 });
	UImageManager::GetInst().CuttingSprite("DoorDown.png", { 96, 48 });
	UImageManager::GetInst().CuttingSprite("DoorDownUp.png", { 96, 48 });
	UImageManager::GetInst().CuttingSprite("DoorDownUp2.png", { 96, 48 });
	UImageManager::GetInst().CuttingSprite("DoorRightLeft2.png", { 48, 96 });

	UImageManager::GetInst().CuttingSprite("EnemyDeathEffect.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("FireEffect.png", { 64, 64 });
	UImageManager::GetInst().CuttingSprite("FadeIn.png", { 800, 700 });
	UImageManager::GetInst().CuttingSprite("FadeOut.png", { 800, 700 });
	UImageManager::GetInst().CuttingSprite("TitleTriforce.png", { 200, 200 });
	UImageManager::GetInst().CuttingSprite("TitleTriforceReverse.png", { 200, 200 });

	UImageManager::GetInst().CuttingSprite("Heart.png", { 21, 21 });
	UImageManager::GetInst().CuttingSprite("DropHeart.png", { 24, 78 });
	UImageManager::GetInst().CuttingSprite("HUDText.png", { 21, 21 });

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("A link to the past");

	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);

	// 이거 꼭 호출해줘야 합니다.
	FVector2D WindowResolution = FVector2D(width, height);
	FVector2D InitWindowScale = FVector2D( 760, 672 );

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale(WindowResolution.Half() - InitWindowScale.Half(), InitWindowScale);

	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");
	UEngineAPICore::GetCore()->CreateLevel<AHyruleCastleGameMode, APlayerCharacter>("HyruleCastle");
	UEngineAPICore::GetCore()->CreateLevel<ACastleDungeonGameMode, APlayerCharacter>("CastleDungeon");
	UEngineAPICore::GetCore()->CreateLevel<ABossGameMode, APlayerCharacter>("Boss");

	UEngineAPICore::GetCore()->OpenLevel("Title");
}

void UZeldaCore::Tick()
{
}

