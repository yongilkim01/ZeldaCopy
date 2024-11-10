#pragma once


enum class ERenderOrder
{
	BACKGROUND = -1000,
	COLMAP = -999,
	PLAYER = 0,
	SECOND_FLOOR = 10,
	UI = 10000
};

enum class ECollisionGroup
{
	PlayerBody,
	MonsterBody,
};

