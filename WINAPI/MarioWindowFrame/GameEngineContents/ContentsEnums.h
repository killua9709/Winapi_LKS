#pragma once

enum class BubbleRenderOrder
{
	BackGround,
	Map,
	Player,
	Monster,
};

enum class BubbleCollisionOrder
{
	Player,
	Monster,
	PlayerAttack,
	MonsterAttack,
};