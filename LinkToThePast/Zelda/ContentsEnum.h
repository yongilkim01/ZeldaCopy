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
	UI_GAGE = 10010,
	UI_FRAME = 10020,
	FADE = 30000,
};

enum class ECollisionGroup
{
	PlayerBody,
	PlayerAttack,
	EnemyBody,
	EnemyAttack,
	Potal,
	EventTarget,
	EventStart,
	MOVEABLE,
	NOTMOVEABLE,
	GIMMICK,
};

enum class ERoomFloor
{
	FLOOR_1F,
	FLOOR_2F,
};

enum class EDropItemType
{
	NONE,
	KEY,
	LANTERN,
	HEART,
	BOW
};

enum class EDropItemState
{
	NONE,
	DROP,
	PICKUP,
};

enum class ETextIndex
{
	A = 0, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z,
	ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
	EXCLAMATION,
	QUESTION,
	LEFT_ARROW,
	RIGHT_ARROW,
	LEFT_PARENT,
	RIGHT_PARENT,
	UNDERBAR,
	DOT,
	COMMA,
	MAX,
};