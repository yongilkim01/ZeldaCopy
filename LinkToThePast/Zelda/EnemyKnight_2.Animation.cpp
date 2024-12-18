#include "PreCompile.h"
#include "EnemyKnight.h"

#include <EngineCore/SpriteRenderer.h>


void AEnemyKnight::ChangeMoveAnimation(FVector2D Direction)
{
	if (Direction == FVector2D::RIGHT)
	{
		this->SpriteRenderer->ChangeAnimation("Move_Right");
	}
	else if (Direction == FVector2D::LEFT)
	{
		this->SpriteRenderer->ChangeAnimation("Move_Left");
	}
	else if (Direction == FVector2D::UP)
	{
		this->SpriteRenderer->ChangeAnimation("Move_Up");
	}
	else if (Direction == FVector2D::DOWN)
	{
		this->SpriteRenderer->ChangeAnimation("Move_Down");
	}
}

void AEnemyKnight::ChangeHitAnimation(FVector2D Direction)
{
	if (Direction == FVector2D::RIGHT)
	{
		this->SpriteRenderer->ChangeAnimation("Hit_Right");
	}
	else if (Direction == FVector2D::LEFT)
	{
		this->SpriteRenderer->ChangeAnimation("Hit_Left");
	}
	else if (Direction == FVector2D::UP)
	{
		this->SpriteRenderer->ChangeAnimation("Hit_Up");
	}
	else if (Direction == FVector2D::DOWN)
	{
		this->SpriteRenderer->ChangeAnimation("Hit_Down");
	}
}

void AEnemyKnight::EndFallAnimation()
{
	Destroy();
}
