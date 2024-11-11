#pragma once


enum class ERenderOrder
{
	BACKGROUND = -1000,
	COLMAP = -999,
	PLAYER = 0,
	SECOND_FLOOR = 50,
	UI = 10000
};

enum class ECollisionGroup
{
	PlayerBody,
	PlayerAttack,
	EnemyBody,
};

enum class ERoomFloor
{
	FLOOR_1F,
	FLOOR_2F,
};