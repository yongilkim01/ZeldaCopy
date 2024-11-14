#include "PreCompile.h"
#include "ArmosKngiht_Control.h"
#include "ArmosKnight.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineMath.h>

AArmosKngiht_Control::AArmosKngiht_Control()
{
	
}

AArmosKngiht_Control::~AArmosKngiht_Control()
{
}

void AArmosKngiht_Control::BeginPlay()
{
	ABossCharacter::BeginPlay();

	BossForces.reserve(10);

	BossForces.push_back({ 235, 231 });
	BossForces.push_back({ 380, 231 });
	BossForces.push_back({ 525, 231 });
	BossForces.push_back({ 235, 340 });
	BossForces.push_back({ 380, 340 });
	BossForces.push_back({ 525, 340 });

	FVector2D WindowHalfSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half();

	for (int i = 0; i < 6; i++)
	{
		AArmosKnight* ArmosKnight = GetWorld()->SpawnActor<AArmosKnight>();
		ArmosKnight->SetActorLocation(WindowHalfSize);
		ArmosKnight->SetActorLocation(BossForces[i]);
		BossEnemies.push_back(ArmosKnight);

	}

	for (int i = 0; i < 6; i++)
	{
		BossEnemies[i]->SetActorLocation(RotateToDegree(
			CurrentDegree,
			WindowHalfSize,
			150.0f));

		//BossEnemies[i]->AddActorLocation(WindowHalfSize);
		CurrentDegree += 60;

		if (CurrentDegree >= 360)
		{
			CurrentDegree = 0;
		}
	}
}

void AArmosKngiht_Control::Tick(float DeltaTime)
{
	ABossCharacter::Tick(DeltaTime);

	FVector2D WindowHalfSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half();

	for (int i = 0; i < 6; i++)
	{
		BossEnemies[i]->SetActorLocation(RotateToDegree(
			CurrentDegree,
			WindowHalfSize,
			150.0f));

		//BossEnemies[i]->AddActorLocation(WindowHalfSize);
		CurrentDegree += 30;

		if (CurrentDegree >= 360)
		{
			CurrentDegree = 0;
		}
	}

}

FVector2D AArmosKngiht_Control::RotateToDegree(float Degree, FVector2D Location, float H)
{
	FVector2D Result = FVector2D::ZERO;

	Result.X = H * std::cos(RADIAN(Degree));
	Result.Y = H * std::sin(RADIAN(Degree));

	return Result + Location;
}