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
	Wall2,
	Object,
	Bullet,
	MonsterBullet,
	Cursor

};