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
	// ��������Ʈ �������� 
	AActor* Actor = GetActor();
	ULevel* Level = Actor->GetWorld();
	Level->PushCollision(this);
}
void UCollision2D::ComponentTick(float _DeltaTime)
{
	Super::ComponentTick(_DeltaTime);
	// ����� ��尡 on
	int a = 0;
}