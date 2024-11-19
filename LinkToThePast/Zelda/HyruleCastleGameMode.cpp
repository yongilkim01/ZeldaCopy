#include "PreCompile.h"
#include "HyruleCastleGameMode.h"
#include "PlayerCharacter.h"
#include "EnemyCharacter.h"
#include "HylianKnights.h"
#include "Room.h"
#include "LevelMove.h"
#include "Fade.h"
#include "StatueFire.h"
#include "StatueStone.h"


AHyruleCastleGameMode::AHyruleCastleGameMode()
{
}

AHyruleCastleGameMode::~AHyruleCastleGameMode()
{
}

void AHyruleCastleGameMode::BeginPlay()
{
	AZeldaGameMode::BeginPlay();

	// �� ��ü�� UI��� �ʱ�ȭ
	RoomBeginPlay();
	UIBeginPlay();

	ALevelMove* LevelMove1 = GetWorld()->SpawnActor<ALevelMove>();
	LevelMove1->SetActorLocation({ 1532, 273 });

	AFade* FadeActor = GetWorld()->SpawnActor<AFade>();
	FadeActor->SetActorLocation({ 0, 0 });

	BeginPlayEnvActor();

	// �÷��̾��� ��ġ�� �����ϴ� �� ��ü�� �÷��̾��� ��������� ����

	// ���ʹ� ��ü ����
	{
		//AHylianKnight* EnemyCharacter = GetWorld()->SpawnActor<AHylianKnight>();
		//EnemyCharacter->SetActorLocation({ 2332, 1724 });
		//EnemyCharacter->SetSpeed(150.0f);
		//EnemyCharacter->AddTurningLocation(FVector2D(2332, 1974));
		//EnemyCharacter->AddTurningLocation(FVector2D(2332, 1724));

		//CheckCharacterInRoom(EnemyCharacter);

	}
}

void AHyruleCastleGameMode::Tick(float DeltaTime)
{
	AZeldaGameMode::Tick(DeltaTime);

	CheckCollisionRoom();
}

void AHyruleCastleGameMode::RoomBeginPlay()
{
	Roomes.reserve(10);
	RoomDataes.reserve(10);

	RoomDataes.push_back({ { 0, 0 } ,{ 765, 1554 } });				// Castle1	
	RoomDataes.push_back({ { 765, 0 } ,{ 1536, 804 } });			// Castle2
	RoomDataes.push_back({ { 2301, 0 } ,{ 1152, 1554 } });			// Castle3
	RoomDataes.push_back({ { 2301, 1554 } ,{ 1152, 1536 } });		// Castle4
	RoomDataes.push_back({ { 765, 1554 } ,{ 1536, 1536 } });		// Castle5
	RoomDataes.push_back({ { 0, 1554 } ,{ 765, 1536 } });			// Castle6

	CreateRoomActor("Castle", 0);

	this->Roomes[2]->SetIsSecondFloor(true);
	this->Roomes[2]->GetColSpriteRenderer2F()->SetOrder(ERenderOrder::COLMAP);
	this->Roomes[2]->GetColSpriteRenderer2F()->SetSprite("Castle3Collision2F.png");
	FVector2D ColMap1Scale = this->Roomes[2]->GetColSpriteRenderer2F()->SetSpriteScale(1.0f);
	this->Roomes[2]->GetColSpriteRenderer2F()->SetComponentLocation(ColMap1Scale.Half());

	this->Roomes[3]->SetIsSecondFloor(true);
	this->Roomes[3]->GetColSpriteRenderer2F()->SetOrder(ERenderOrder::COLMAP);
	this->Roomes[3]->GetColSpriteRenderer2F()->SetSprite("Castle4Collision2F.png");
	FVector2D ColMap2Scale = this->Roomes[3]->GetColSpriteRenderer2F()->SetSpriteScale(1.0f);
	this->Roomes[3]->GetColSpriteRenderer2F()->SetComponentLocation(ColMap2Scale.Half());
	this->Roomes[3]->CreateEnvSprite("Castle4Bridge.png", FVector2D(528, 384), FVector2D(192, 552));

	this->Roomes[4]->SetIsSecondFloor(true);
	this->Roomes[4]->GetColSpriteRenderer2F()->SetOrder(ERenderOrder::COLMAP);
	this->Roomes[4]->GetColSpriteRenderer2F()->SetSprite("Castle5Collision2F.png");
	FVector2D ColMap3Scale = this->Roomes[4]->GetColSpriteRenderer2F()->SetSpriteScale(1.0f);
	this->Roomes[4]->GetColSpriteRenderer2F()->SetComponentLocation(ColMap3Scale.Half());
	this->Roomes[4]->CreateEnvSprite("Castle5Door1.png", FVector2D(0, 645), FVector2D(141, 243));

	this->Roomes[5]->SetIsSecondFloor(true);
	this->Roomes[5]->GetColSpriteRenderer2F()->SetOrder(ERenderOrder::COLMAP);
	this->Roomes[5]->GetColSpriteRenderer2F()->SetSprite("Castle6Collision2F.png");
	FVector2D ColMap4Scale = this->Roomes[5]->GetColSpriteRenderer2F()->SetSpriteScale(1.0f);
	this->Roomes[5]->GetColSpriteRenderer2F()->SetComponentLocation(ColMap4Scale.Half());
	this->Roomes[5]->CreateEnvSprite("Castle6Bridge.png", FVector2D(261, 336), FVector2D(243, 192));
}

void AHyruleCastleGameMode::BeginPlayEnvActor()
{
	{
		AStatueFire* StatueFire = GetWorld()->SpawnActor<AStatueFire>();
		StatueFire->SetActorLocation({ 765 + 672, 1554 + 744 });
		StatueFire->SetCurRoom(Roomes[4]);

		AStatueFire* StatueFire2 = GetWorld()->SpawnActor<AStatueFire>();
		StatueFire2->SetActorLocation({ 765 + 816, 1554 + 744 });
		StatueFire2->SetCurRoom(Roomes[4]);

		AStatueStone* StatueStone1 = GetWorld()->SpawnActor<AStatueStone>();
		StatueStone1->SetActorLocation({ 765 + 288, 1554 + 648 });
		StatueStone1->SetCurRoom(Roomes[4]);

		AStatueStone* StatueStone2 = GetWorld()->SpawnActor<AStatueStone>();
		StatueStone2->SetActorLocation({ 765 + 384, 1554 + 648 });
		StatueStone2->SetCurRoom(Roomes[4]);

		AStatueStone* StatueStone3 = GetWorld()->SpawnActor<AStatueStone>();
		StatueStone3->SetActorLocation({ 765 + 480, 1554 + 648 });
		StatueStone3->SetCurRoom(Roomes[4]);

		AStatueStone* StatueStone4 = GetWorld()->SpawnActor<AStatueStone>();
		StatueStone4->SetActorLocation({ 765 + 1008, 1554 + 648 });
		StatueStone4->SetCurRoom(Roomes[4]);

		AStatueStone* StatueStone5 = GetWorld()->SpawnActor<AStatueStone>();
		StatueStone5->SetActorLocation({ 765 + 1104, 1554 + 648 });
		StatueStone5->SetCurRoom(Roomes[4]);

		AStatueStone* StatueStone6 = GetWorld()->SpawnActor<AStatueStone>();
		StatueStone6->SetActorLocation({ 765 + 1200, 1554 + 648 });
		StatueStone6->SetCurRoom(Roomes[4]);
	}
}
