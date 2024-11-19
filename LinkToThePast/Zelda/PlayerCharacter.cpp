#include "PreCompile.h"
#include "PlayerCharacter.h"
#include "Room.h"
#include "HylianKnights.h"
#include "Fade.h"

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
		SpriteRenderer->CreateAnimation("Idle_Right", "LinkMoveRight.png", 0, 0, 0.1f);
		SpriteRenderer->CreateAnimation("Idle_Left", "LinkMoveLeft.png", 0, 0, 0.1f);
		SpriteRenderer->CreateAnimation("Idle_Up", "LinkMoveUp.png", 0, 0, 0.1f);
		SpriteRenderer->CreateAnimation("Idle_Down", "LinkMoveDown.png", 0, 0, 0.1f);

		SpriteRenderer->CreateAnimation("KnockBack_Right", "LinkKnockBackRight.png", 0, 7, 0.001f);
		SpriteRenderer->CreateAnimation("KnockBack_Left", "LinkKnockBackLeft.png", 0, 7, 0.001f);
		SpriteRenderer->CreateAnimation("KnockBack_Up", "LinkKnockBackUp.png", 0, 7, 0.001f);
		SpriteRenderer->CreateAnimation("KnockBack_Down", "LinkKnockBackDown.png", 0, 7, 0.001f);

		SpriteRenderer->CreateAnimation("Attack_Right", "LinkAttackRight.png", 0, 5, 0.04f, false);
		SpriteRenderer->CreateAnimation("Attack_Left", "LinkAttackLeft.png", 0, 5, 0.04f, false);
		SpriteRenderer->CreateAnimation("Attack_Up", "LinkAttackUp.png", 0, 4, 0.04f, false);
		SpriteRenderer->CreateAnimation("Attack_Down", "LinkAttackDown.png", 0, 5, 0.04f, false);

		// 애니메이션 이벤트 바인드
		SpriteRenderer->SetAnimationEvent("Attack_Right", 5, std::bind(&APlayerCharacter::EndAttack, this));
		SpriteRenderer->SetAnimationEvent("Attack_Left", 5, std::bind(&APlayerCharacter::EndAttack, this));
		SpriteRenderer->SetAnimationEvent("Attack_Up", 4, std::bind(&APlayerCharacter::EndAttack, this));
		SpriteRenderer->SetAnimationEvent("Attack_Down", 5, std::bind(&APlayerCharacter::EndAttack, this));
	}
	{
		// 충돌 컴포넌트 생성
		HitCollision = CreateDefaultSubObject<UCollision2D>();
		HitCollision->SetComponentLocation({ 0, 0 });
		HitCollision->SetComponentScale({ 50, 80 });
		HitCollision->SetCollisionGroup(ECollisionGroup::PlayerBody);
		HitCollision->SetActive(true);

	}
	{
		// 공격 충돌 컴포넌트 생성
		AttackCollisions.reserve(4);

		UCollision2D* RightAttackCollision = CreateDefaultSubObject<UCollision2D>();
		RightAttackCollision->SetComponentLocation({ 50, 0 });
		RightAttackCollision->SetComponentScale({ 70, 100 });
		RightAttackCollision->SetCollisionGroup(ECollisionGroup::PlayerAttack);
		AttackCollisions.push_back(RightAttackCollision);

		UCollision2D* LeftAttackCollision = CreateDefaultSubObject<UCollision2D>();
		LeftAttackCollision->SetComponentLocation({ -50, 0 });
		LeftAttackCollision->SetComponentScale({ 70,100 });
		LeftAttackCollision->SetCollisionGroup(ECollisionGroup::PlayerAttack);
		AttackCollisions.push_back(LeftAttackCollision);

		UCollision2D* DownAttackCollision = CreateDefaultSubObject<UCollision2D>();
		DownAttackCollision->SetComponentLocation({ 0, 50 });
		DownAttackCollision->SetComponentScale({ 100, 70 });
		DownAttackCollision->SetCollisionGroup(ECollisionGroup::PlayerAttack);
		AttackCollisions.push_back(DownAttackCollision);

		UCollision2D* UpAttackCollision = CreateDefaultSubObject<UCollision2D>();
		UpAttackCollision->SetComponentLocation({ 0, -50 });
		UpAttackCollision->SetComponentScale({ 100, 70 });
		UpAttackCollision->SetCollisionGroup(ECollisionGroup::PlayerAttack);
		AttackCollisions.push_back(UpAttackCollision);

	}
	{
		SetSpeed(500.0f);
		CollisionSize = { 10.0f, 30.0f };
	}
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// 카메라 초기화 설정
	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	GetWorld()->SetCameraPivot(Size.Half() * -1);
	GetWorld()->SetCameraToMainPawn(false);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	ABaseCharacter::Tick(DeltaTime);

	if (AZeldaGameMode::IsMapMoving == true) return;

	PrintDebugInfo(DeltaTime);

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
	case EPlayerState::KnockBack:
		KnockBack(DeltaTime);
		break;
	default:
		break;
	}
}

void APlayerCharacter::LevelChangeStart()
{
	Super::LevelChangeStart();

	std::string LevelName = GetWorld()->GetName();

	if (LevelName == "HYRULECASTLE")
	{
		SetActorLocation({ 1533, 2894 });
		SetCurDirection(FVector2D::UP);
		//ChangeState(EPlayerState::Idle);

	}
	else
	{
		SetActorLocation({ 2080, 1544 });
	}
	
}

void APlayerCharacter::LevelChangeEnd()
{
	Super::LevelChangeEnd();
}