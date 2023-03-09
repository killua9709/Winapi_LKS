#include "Cannon.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineResources.h>
#include "CannonBullet.h"
#include <GameEngineCore/GameEngineLevel.h>




Cannon::Cannon() 
{
}

Cannon::~Cannon() 
{
}

void Cannon::Start()
{
	BodyCollision = CreateCollision(GameCollisionOrder::Object);
	BodyCollision->SetScale({ 28, 35 });

	render = CreateRender("Cannon.bmp", GameRenderOrder::Monster);
	render->SetScale({ 102, 102 });
	render->CreateAnimation({ .AnimationName = "Cannon_Idle",  .ImageName = "Cannon.bmp", .Start = 0, .End = 0 });
	render->CreateAnimation({ .AnimationName = "Cannon_Fire",  .ImageName = "Cannon.bmp", .Start = 1, .End = 5 ,.InterTime = 0.12 });
	render->CreateAnimation({ .AnimationName = "Right_Cannon_Fire",  .ImageName = "Right_Cannon.bmp", .Start = 1, .End = 5 ,.InterTime = 0.15 });
	render->CreateAnimation({ .AnimationName = "Left_Cannon_Fire",  .ImageName = "Left_Cannon.bmp", .Start = 1, .End = 5 ,.InterTime = 0.15 });
	render->ChangeAnimation("Cannon_Fire");

	CannonBullet* bullet = GetLevel()->CreateActor<CannonBullet>(GameRenderOrder::Cursor);
	bullet->SetMove({ GetPos().x,GetPos().y - 15 });

	for (size_t i = 0; i < 6; i++)
	{
		Bullets.push_back(bullet);
		Bullets[i]->Off();
	}
}

void Cannon::Update(float _DeltaTime)
{
	firetime += _DeltaTime;

	switch (CurrentState)
	{
	case Normal1:render->ChangeAnimation("Cannon_Fire");
		for (size_t i = 0; i < Bullets.size(); i++)
		{
			Bullets[i]->SetState(BulletState::Normal);
		}
		break;
	case Left2:render->ChangeAnimation("Left_Cannon_Fire");
		for (size_t i = 0; i < Bullets.size(); i++)
		{
			Bullets[i]->SetState(BulletState::Right);
		}
		break;
	case Right3:render->ChangeAnimation("Right_Cannon_Fire");
		for (size_t i = 0; i < Bullets.size(); i++)
		{
			Bullets[i]->SetState(BulletState::Left);
		}
		break;
	default:
		break;
	}

	if (1.5 < firetime)
	{
		firetime = 0;
		for (size_t i = 0; i < 6; i++)
		{
			if (false == Bullets[i]->isOn())
			{
				Bullets[i]->SetPos({ GetPos().x+10,GetPos().y +16 });
				Bullets[i]->On();
				GetSoundPlayer = GameEngineResources::GetInst().SoundPlayToControl("cannon.wav");
				GetSoundPlayer.LoopCount(1);
				GetSoundPlayer.Volume(0.1f);
				break;
			}
		}
	}
}

void Cannon::Render(float _DeltaTime)
{

}

