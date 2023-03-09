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
	BodyCollision = CreateCollision(GameCollisionOrder::Wall2);
	BodyCollision->SetScale({ 34, 34 });

	GameEngineRender* Render = CreateRender("Wall2.bmp", GameRenderOrder::Cursor);
	Render->SetScale({ 34, 34 });
}

void Wall2::Update(float _DeltaTime)
{
	std::vector<GameEngineCollision*> Collision;
	if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::MonsterBullet), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
	{
		for (size_t i = 0; i < Collision.size(); i++)
		{
			GameEngineActor* ColActor = Collision[i]->GetActor();
			ColActor->Off();

			this->Death();
		}
	}
}

void Wall2::Render(float _DeltaTime)
{

}
