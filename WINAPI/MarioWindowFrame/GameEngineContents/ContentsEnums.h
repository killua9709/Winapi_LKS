#pragma once

enum class GameRenderOrder
{
	BackGround,
	Map,
	Player,
	Monster,
	Cursor
};

enum class GameCollisionOrder
{
	Player,
	Monster,
	Wall,
	Object,
	Bullet

};