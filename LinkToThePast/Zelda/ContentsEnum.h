#pragma once


enum class ERenderOrder
{
	BACKGROUND = -1000,
	COLMAP = -999,
	FIRST_FLOOR = 1000,
	FIRST_FLOOR_OBJ = 2000,
	SECOND_FLOOR = 5000,
	SECOND_FLOOR_OBJ = 6000,
	UI = 10000,
	FADE = 30000,
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