#include "Wall2.h"
#include "Player.h"
#include "STLevel.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>

Wall2::Wall2()
{
}

Wall2::~Wall2()
{
}

void Wall2::Start()
{
	BodyCollision = CreateCollision(GameCollisionOrder::Object);
	BodyCollision->SetScale({ 24, 17 });

	GameEngineRender* Render = CreateRender("Wall2.bmp", GameRenderOrder::Cursor);
	Render->SetScale({ 34, 34 });
}

void Wall2::Update(float _DeltaTime)
{
	if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Bullet), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
	{
		
	}
}

void Wall2::Render(float _DeltaTime)
{

}
