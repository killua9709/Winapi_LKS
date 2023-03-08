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
	BodyCollision = CreateCollision(GameCollisionOrder::Wall);
}

void Wall::Render(float _Time)
{
	if (true == dcheck)
	{
		BodyCollision->DebugRender();
	}
}

