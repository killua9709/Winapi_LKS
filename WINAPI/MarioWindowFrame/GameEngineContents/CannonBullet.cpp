#include "CannonBullet.h"
#include "Player.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

CannonBullet::CannonBullet() 
{
}

CannonBullet::~CannonBullet() 
{
}
float4 CannonBullet::Infloat = float4::Zero;

void CannonBullet::Start()
{
	BodyCollision = CreateCollision(GameCollisionOrder::Monster);
	BodyCollision->SetScale({ 16, 16 });
	BodyCollision->SetPosition({ 0, -8 });

	AnimationRender = CreateRender("CannonBullet.bmp", GameRenderOrder::Cursor);
	AnimationRender->SetScale({ 102, 102 });

	AnimationRender->CreateAnimation({ .AnimationName = "Fire",  .ImageName = "CannonBullet.bmp", .Start = 0, .End = 10, .InterTime = 0.1f });

	AnimationRender->ChangeAnimation("Fire");
}

void CannonBullet::Update(float _DeltaTime)
{
	if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Wall), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
	{
		this->Off();
	}
	else
	{
		SetMove(float4::Down * _DeltaTime * 200);
	}

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

void CannonBullet::Render(float _DeltaTime)
{

}
