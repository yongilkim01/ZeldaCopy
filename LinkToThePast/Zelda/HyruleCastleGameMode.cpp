#include "PreCompile.h"
#include "HyruleCastleGameMode.h"
#include "PlayerCharacter.h"
#include "EnemyCharacter.h"
#include "HylianKnights.h"
#include "Room.h"
#include "LevelMove.h"
#include "Fade.h"


AHyruleCastleGameMode::AHyruleCastleGameMode()
{
}

AHyruleCastleGameMode::~AHyruleCastleGameMode()
{
}

void AHyruleCastleGameMode::BeginPlay()
{
	AZeldaGameMode::BeginPlay();

	// 룸 객체와 UI들들 초기화
	RoomBeginPlay();
	UIBeginPlay();

	ALevelMove* LevelMove1 = GetWorld()->SpawnActor<ALevelMove>();
	LevelMove1->SetActorLocation({ 1532, 273 });

	AFade* FadeActor = GetWorld()->SpawnActor<AFade>();
	FadeActor->SetActorLocation({ 0, 0 });

	// 플레이어의 위치에 존재하는 룸 객체를 플레이어의 현재룸으로 설정

	// 에너미 객체 생성
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

	this->Roomes[5]->SetIsSecondFloor(true);
	this->Roomes[5]->GetColSpriteRenderer2F()->SetOrder(ERenderOrder::COLMAP);
	this->Roomes[5]->GetColSpriteRenderer2F()->SetSprite("Castle6Collision2F.png");
	FVector2D ColMap4Scale = this->Roomes[5]->GetColSpriteRenderer2F()->SetSpriteScale(1.0f);
	this->Roomes[5]->GetColSpriteRenderer2F()->SetComponentLocation(ColMap4Scale.Half());
	this->Roomes[5]->CreateEnvSprite("Castle6Bridge.png", FVector2D(261, 336), FVector2D(243, 192));


	//this->Roomes[0]->SetIsSecondFloor(true);
	//this->Roomes[0]->GetColSpriteRenderer2F()->SetSprite("CastleDungeon1Collision2F.png");


	//this->Roomes[1]->SetIsSecondFloor(true);
	//this->Roomes[1]->GetColSpriteRenderer2F()->SetOrder(ERenderOrder::COLMAP);
	//this->Roomes[1]->GetColSpriteRenderer2F()->SetSprite("CastleDungeon2Collision2F.png");
	//FVector2D ColMap2Scale = this->Roomes[1]->GetColSpriteRenderer2F()->SetSpriteScale(1.0f);
	//this->Roomes[1]->GetColSpriteRenderer2F()->SetComponentLocation(ColMap2Scale.Half());


	//this->Roomes[7]->SetIsSecondFloor(true);
	//this->Roomes[7]->GetColSpriteRenderer2F()->SetOrder(ERenderOrder::COLMAP);
	//this->Roomes[7]->GetColSpriteRenderer2F()->SetSprite("CastleDungeon8Collision2F.png");
	//FVector2D ColMap8Scale = this->Roomes[7]->GetColSpriteRenderer2F()->SetSpriteScale(1.0f);
	//this->Roomes[7]->GetColSpriteRenderer2F()->SetComponentLocation(ColMap8Scale.Half());
	//this->Roomes[7]->CreateEnvSprite("CastleDungeon8Bridge.png");
}
