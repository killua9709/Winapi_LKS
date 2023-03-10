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
	BodyCollision = CreateCollision(GameCollisionOrder::MonsterBullet);
	BodyCollision->SetScale({ 16, 16 });
	BodyCollision->SetPosition({ -8, -8 });

	AnimationRender = CreateRender("CannonBullet.bmp", GameRenderOrder::Cursor);
	AnimationRender->SetScale({ 102, 102 });

	AnimationRender->CreateAnimation({ .AnimationName = "Fire",  .ImageName = "CannonBullet.bmp", .Start = 0, .End = 10, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire",  .ImageName = "Left_CannonBullet.bmp", .Start = 0, .End = 10, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire",  .ImageName = "Right_CannonBullet.bmp", .Start = 0, .End = 10, .InterTime = 0.1f });

	AnimationRender->ChangeAnimation("Fire");
}

void CannonBullet::Update(float _DeltaTime)
{
	switch (CurrentState)
	{
	case Normal:AnimationRender->ChangeAnimation("Fire");
		break;
	case Left:AnimationRender->ChangeAnimation("Left_Fire");
		AnimationRender->SetPosition({ 0, -27 });
		BodyCollision->SetPosition({ 6, -18 });
		break;
	case Right:AnimationRender->ChangeAnimation("Right_Fire");
		AnimationRender->SetPosition({ 0, -27 });
		BodyCollision->SetPosition({ -6, -18 });
		break;
	default:
		break;
	}


	if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Wall), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
	{
		this->Off();
	}
	else
	{
		switch (CurrentState)
		{
		case Normal:SetMove(float4::Down * _DeltaTime * 100);
			break;
		case Left:SetMove(float4::Left * _DeltaTime * 100);
			break;
		case Right:SetMove(float4::Right * _DeltaTime * 100);
			break;
		default:
			break;
		}
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
