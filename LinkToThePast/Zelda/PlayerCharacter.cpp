#include "PreCompile.h"
#include "PlayerCharacter.h"
#include "Room.h"
#include "HylianKnights.h"
#include "Fade.h"
#include "Lantern.h"
#include "Bow.h"
#include "PlayerDataManager.h"
#include "EventManager.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/Collision2D.h>

APlayerCharacter::APlayerCharacter()
{
	Super::BeginPlay();

	{
		// 스프라이트 컴포넌트 생성
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("LinkMoveDown.png");
		SpriteRenderer->SetSpriteScale(3.0f);
		//SpriteRenderer->SetOrder(ERenderOrder::FIRST_FLOOR_OBJ);

		// 애니메이션 생성
		SpriteRenderer->CreateAnimation("Run_Right", "LinkMoveRight.png", 1, 8, 0.04f);
		SpriteRenderer->CreateAnimation("Run_Left", "LinkMoveLeft.png", 1, 8, 0.04f);
		SpriteRenderer->CreateAnimation("Run_Up", "LinkMoveUp.png", 1, 8, 0.04f);
		SpriteRenderer->CreateAnimation("Run_Down", "LinkMoveDown.png", 1, 8, 0.04f);

		SpriteRenderer->CreateAnimation("Idle_right", "LinkMoveRight.png", 0, 0, 0.1f);
		SpriteRenderer->CreateAnimation("Idle_Left", "LinkMoveLeft.png", 0, 0, 0.1f);
		SpriteRenderer->CreateAnimation("Idle_Up", "LinkMoveUp.png", 0, 0, 0.1f);
		SpriteRenderer->CreateAnimation("Idle_Down", "LinkMoveDown.png", 0, 0, 0.1f);

		SpriteRenderer->CreateAnimation("ShieldMoveRight", "LinkShieldMoveRight.png", 0, 8, 0.04f);
		SpriteRenderer->CreateAnimation("ShieldMoveLeft", "LinkShieldMoveLeft.png", 0, 8, 0.04f);
		SpriteRenderer->CreateAnimation("ShieldMoveUp", "LinkShieldMoveUp.png", 0, 8, 0.04f);
		SpriteRenderer->CreateAnimation("ShieldMoveDown", "LinkShieldMoveDown.png", 0, 8, 0.04f);

		SpriteRenderer->CreateAnimation("ShieldIdleRight", "LinkShieldMoveRight.png", 0, 0, 0.1f);
		SpriteRenderer->CreateAnimation("ShieldIdleLeft", "LinkShieldMoveLeft.png", 0, 0, 0.1f);
		SpriteRenderer->CreateAnimation("ShieldIdleUp", "LinkShieldMoveUp.png", 0, 0, 0.1f);
		SpriteRenderer->CreateAnimation("ShieldIdleDown", "LinkShieldMoveDown.png", 0, 0, 0.1f);

		SpriteRenderer->CreateAnimation("KnockBack_Right", "LinkKnockBackRight.png", 0, 7, 0.001f);
		SpriteRenderer->CreateAnimation("KnockBack_Left", "LinkKnockBackLeft.png", 0, 7, 0.001f);
		SpriteRenderer->CreateAnimation("KnockBack_Up", "LinkKnockBackUp.png", 0, 7, 0.001f);
		SpriteRenderer->CreateAnimation("KnockBack_Down", "LinkKnockBackDown.png", 0, 7, 0.001f);

		SpriteRenderer->CreateAnimation("Attack_Right", "LinkAttackRight.png", 0, 5, 0.04f, false);
		SpriteRenderer->CreateAnimation("Attack_Left", "LinkAttackLeft.png", 0, 5, 0.04f, false);
		SpriteRenderer->CreateAnimation("Attack_Up", "LinkAttackUp.png", 0, 4, 0.04f, false);
		SpriteRenderer->CreateAnimation("Attack_Down", "LinkAttackDown.png", 0, 5, 0.04f, false);

		SpriteRenderer->CreateAnimation("LiftRight", "LinkLiftRight.png", 0, 1, 0.1f, false);
		SpriteRenderer->CreateAnimation("LiftLeft", "LinkLiftLeft.png", 0, 1, 0.1f, false);
		SpriteRenderer->CreateAnimation("LiftUp", "LinkLiftUp.png", 0, 1, 0.1f, false);
		SpriteRenderer->CreateAnimation("LiftDown", "LinkLiftDown.png", 0, 1, 0.1f, false);

		SpriteRenderer->CreateAnimation("LiftIdleRight", "LinkLiftRight.png", 2, 2, 0.1f);
		SpriteRenderer->CreateAnimation("LiftIdleLeft", "LinkLiftLeft.png", 2, 2, 0.1f);
		SpriteRenderer->CreateAnimation("LiftIdleUp", "LinkLiftUp.png", 2, 2, 0.1f);
		SpriteRenderer->CreateAnimation("LiftIdleDown", "LinkLiftDown.png", 2, 2, 0.1f);

		SpriteRenderer->CreateAnimation("LiftRunRight", "LinkLiftRight.png", 2, 4, 0.04f);
		SpriteRenderer->CreateAnimation("LiftRunLeft", "LinkLiftLeft.png", 2, 4, 0.04f);
		SpriteRenderer->CreateAnimation("LiftRunUp", "LinkLiftUp.png", 2, 7, 0.04f);
		SpriteRenderer->CreateAnimation("LiftRunDown", "LinkLiftDown.png", 2, 7, 0.04f);

		SpriteRenderer->CreateAnimation("BowRight", "LinkBowRight.png", 0, 2, 0.1f, false);
		SpriteRenderer->CreateAnimation("BowLeft", "LinkBowLeft.png", 0, 2, 0.1f, false);
		SpriteRenderer->CreateAnimation("BowUp", "LinkBowUp.png", 0, 2, 0.1f, false);
		SpriteRenderer->CreateAnimation("BowDown", "LinkBowDown.png", 0, 2, 0.1f, false);

		SpriteRenderer->CreateAnimation("LinkSleep", "LinkSleep.png", 0, 0, 0.1f);
		SpriteRenderer->CreateAnimation("LinkWakeUp", "LinkSleep.png", 1, 1, 0.1f);
		SpriteRenderer->CreateAnimation("Fall", "LinkFall.png", 0, 6, 0.1f, false);
		SpriteRenderer->CreateAnimation("TurnFall", "LinkTurnFall.png", 0, 3, 0.08f);
		SpriteRenderer->CreateAnimation("SwordGet", "LinkSwordGet.png", 0, 0, 0.08f);

		// 애니메이션 이벤트 바인드
		SpriteRenderer->SetAnimationEvent("Attack_Right", 5, std::bind(&APlayerCharacter::EndAttack, this));
		SpriteRenderer->SetAnimationEvent("Attack_Left", 5, std::bind(&APlayerCharacter::EndAttack, this));
		SpriteRenderer->SetAnimationEvent("Attack_Up", 4, std::bind(&APlayerCharacter::EndAttack, this));
		SpriteRenderer->SetAnimationEvent("Attack_Down", 5, std::bind(&APlayerCharacter::EndAttack, this));

		SpriteRenderer->SetAnimationEvent("LiftRight", 1, std::bind(&APlayerCharacter::EndLift, this));
		SpriteRenderer->SetAnimationEvent("LiftLeft", 1, std::bind(&APlayerCharacter::EndLift, this));
		SpriteRenderer->SetAnimationEvent("LiftUp", 1, std::bind(&APlayerCharacter::EndLift, this));
		SpriteRenderer->SetAnimationEvent("LiftDown", 1, std::bind(&APlayerCharacter::EndLift, this));
		
		SpriteRenderer->SetAnimationEvent("BowRight", 2, std::bind(&APlayerCharacter::EndAttack, this));
		SpriteRenderer->SetAnimationEvent("BowLeft", 2, std::bind(&APlayerCharacter::EndAttack, this));
		SpriteRenderer->SetAnimationEvent("BowUp", 2, std::bind(&APlayerCharacter::EndAttack, this));
		SpriteRenderer->SetAnimationEvent("BowDown", 2, std::bind(&APlayerCharacter::EndAttack, this));
	}
	{
		// 충돌 컴포넌트 생성
		HitCollision = CreateDefaultSubObject<UCollision2D>();
		HitCollision->SetComponentLocation({ 0, 0 });
		HitCollision->SetComponentScale({ 50, 80 });
		HitCollision->SetCollisionGroup(ECollisionGroup::PlayerBody);
		HitCollision->SetActive(true);

		BodyCollision = CreateDefaultSubObject<UCollision2D>();
		BodyCollision->SetComponentLocation({ 0, 10 });
		BodyCollision->SetComponentScale({ 50,50 });
		BodyCollision->SetCollisionGroup(ECollisionGroup::MOVEABLE);
		BodyCollision->SetActive(true);

		// 공격 컴포넌트 생성
		AttackCollision = CreateDefaultSubObject<UCollision2D>();
		AttackCollision->SetComponentLocation({ 0, 0 });
		AttackCollision->SetComponentScale({ 100,100 });
		AttackCollision->SetCollisionGroup(ECollisionGroup::PlayerAttack);

		// 상호작용 컴포넌트 생성
		InteractCollision = CreateDefaultSubObject<UCollision2D>();
		InteractCollision->SetComponentLocation({ 0, 0 });
		InteractCollision->SetComponentScale({ 25,25 });
		InteractCollision->SetCollisionGroup(ECollisionGroup::EventStart);

	}
	{
		SetSpeed(250.0f);
		CollisionSize = { 10.0f, 30.0f };
	}
	//DebugOn();
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// 카메라 초기화 설정
	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	GetWorld()->SetCameraPivot(Size.Half() * -1);
	GetWorld()->SetCameraToMainPawn(false);

	{
		CreateItem();
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	ABaseCharacter::Tick(DeltaTime);

	PrintDebugInfo(DeltaTime);

	if (AZeldaGameMode::IsMapMoving == true) return;

	if (true == UEventManager::GetInstance().GetEventPause()) return;

	switch (CurPlayerState)
	{
	case EPlayerState::Idle:
		Idle(DeltaTime);
		break;
	case EPlayerState::Move:
		Move(DeltaTime);
		break;
	case EPlayerState::Attack:
		Attack(DeltaTime);
		break;
	case EPlayerState::Skill:
		Skill(DeltaTime);
		break;
	case EPlayerState::KnockBack:
		KnockBack(DeltaTime);
		break;
	case EPlayerState::Interact:
		Interact(DeltaTime);
		break;
	case EPlayerState::LiftIdle:
		LiftIdle(DeltaTime);
		break;
	case EPlayerState::LiftMove:
		LiftMove(DeltaTime);
		break;
	case EPlayerState::Sleep:
		Sleep(DeltaTime);
		break;
	case EPlayerState::WakeUp:
		WakeUp(DeltaTime);
		break;
	case EPlayerState::Fall:
		Fall(DeltaTime);
		break;
	case EPlayerState::TurnFall:
		TurnFall(DeltaTime);
		break;
	case EPlayerState::SwordGet:
		GetSword(DeltaTime);
		break;
	default:
		break;
	}
}

void APlayerCharacter::LevelChangeStart()
{
	Super::LevelChangeStart();

	std::string LevelName = GetWorld()->GetName();

	if ("LINKHOUSE" == LevelName)
	{
		SetActorLocation({ 216, 260 });
		SetCurDirection(FVector2D::RIGHT);
		ChangeState(EPlayerState::Sleep);

	}
	else if ("LIGHTWORLD" == LevelName)
	{
		SetActorLocation({ 1536 + 576, 3072 + 847 });
		SetCurDirection(FVector2D::DOWN);
		ChangeState(EPlayerState::Idle);

	}
	else if ("UNDERWATER" == LevelName)
	{
		SetActorLocation({ 1152, 0 });
		SetCurDirection(FVector2D::DOWN);
		ChangeState(EPlayerState::Idle);

	}
	else if ("HYRULECASTLE" == LevelName)
	{
		//SetActorLocation({ 1533, 2894 });
		SetActorLocation({ 1533, 2894 });
		SetCurDirection(FVector2D::UP);
		ChangeState(EPlayerState::Idle);

	}
	else if("CASTLEDUNGEON" == LevelName)
	{
		//SetActorLocation({ 2305, 165 });
		SetActorLocation({ 380, 1254 });
		SetCurDirection(FVector2D::DOWN);
		ChangeState(EPlayerState::Idle);
	}
	
}

void APlayerCharacter::LevelChangeEnd()
{
	Super::LevelChangeEnd();
}

void APlayerCharacter::CreateItem()
{
	Lantern = GetWorld()->SpawnActor<ALantern>();
	Lantern->SetActorLocation(GetActorLocation());
	Lantern->SetPlayer(this);
	WeaponItemes.push_back(Lantern);
	Lantern->SetActive(
		PlayerDataManager::GetInstance().GetWeaponActiveToIndex(static_cast<int>(WeaponItemes.size()) - 1) // 0
	);

	Bow = GetWorld()->SpawnActor<ABow>();
	Bow->SetActorLocation(GetActorLocation());
	Bow->SetPlayer(this);
	WeaponItemes.push_back(Bow);
	Bow->SetActive(
		PlayerDataManager::GetInstance().GetWeaponActiveToIndex(static_cast<int>(WeaponItemes.size()) - 1) // 1
	);
}
