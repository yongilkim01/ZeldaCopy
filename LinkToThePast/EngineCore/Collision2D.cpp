#include "PreCompile.h"
#include "Collision2D.h"


UCollision2D::UCollision2D()
{
}

UCollision2D::~UCollision2D()
{
}

void UCollision2D::BeginPlay()
{
	Super::BeginPlay();
	// 스프라이트 랜더러가 
	AActor* Actor = GetActor();
	ULevel* Level = Actor->GetWorld();
	Level->PushCollision(this);
}
void UCollision2D::ComponentTick(float _DeltaTime)
{
	Super::ComponentTick(_DeltaTime);
	// 디버그 모드가 on
	int a = 0;
}