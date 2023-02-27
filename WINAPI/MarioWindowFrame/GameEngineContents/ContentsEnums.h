#pragma once

enum class BubbleRenderOrder
{
	BackGround,
	Map,
	Player,
	Monster,
	Cursor
};

enum class BubbleCollisionOrder
{
	Player,
	Monster,
	Wall

};