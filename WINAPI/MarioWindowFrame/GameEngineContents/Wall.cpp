#include "Wall.h"
#include <GameEngineCore/GameEngineCollision.h>


#include "ContentsEnums.h"



Wall::Wall() 
{
}

Wall::~Wall() 
{

}


void Wall::Start()
{
	BodyCollision = CreateCollision(BubbleCollisionOrder::Wall);
}

void Wall::Render(float _Time)
{
	BodyCollision->DebugRender();
}

