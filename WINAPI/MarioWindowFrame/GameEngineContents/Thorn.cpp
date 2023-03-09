#include "Thorn.h"
#include "Player.h"
#include "STLevel.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>

Thorn::Thorn()
{
}

Thorn::~Thorn()
{
}

void Thorn::Start()
{
	BodyCollision = CreateCollision(GameCollisionOrder::Object);
	BodyCollision->SetScale({ 34, 34 });

	GameEngineRender* Render = CreateRender("Thorn.bmp", GameRenderOrder::Cursor);
	Render->SetScale({ 34, 34 });
}

void Thorn::Update(float _DeltaTime)
{
	std::vector<GameEngineCollision*> Collision;
	if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
	{
		for (size_t i = 0; i < Collision.size(); i++)
		{
			GameEngineActor* ColActor = Collision[i]->GetActor();
			ColActor->SetPos(Infloat);
		}
	}
}

void Thorn::Render(float _DeltaTime)
{

}
