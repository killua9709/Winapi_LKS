#include "BossMonster.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <cmath>
#include "Player.h"

BossMonster::BossMonster()
{
}

BossMonster::~BossMonster()
{

}


void BossMonster::Start()
{
	AnimationRender = CreateRender(GameCollisionOrder::Monster);
	AnimationRender->SetScale({ 100, 100 });

	AnimationRender->CreateAnimation({ .AnimationName = "Left_Idle",  .ImageName = "Left_Wizard.bmp", .Start = 0, .End = 1, .InterTime = 0.4f });
	AnimationRender->CreateAnimation({ .AnimationName = "Left_Move",  .ImageName = "Left_Wizard.bmp", .Start = 0, .End = 3 });
	AnimationRender->CreateAnimation({ .AnimationName = "Left_Death",  .ImageName = "Death_Effect.bmp", .Start = 0, .End = 7 ,.Loop = false });
	AnimationRender->ChangeAnimation("Left_Idle");

	{
		BodyCollision = CreateCollision(GameCollisionOrder::Cursor);
		BodyCollision->SetScale({ 20, 25 });
		BodyCollision->SetMove({ 0,-17 });
	}
}


void BossMonster::Update(float _DeltaTime)
{
	if (true == isdeath)
	{
		AnimationRender->ChangeAnimation("Left_Death");

		if (AnimationRender->IsAnimationEnd())
		{
			this->Death();
		}
	}
	else
	{
		float distance = 100;
		float a = abs(GetPos().x - Player::MainPlayer->GetPos().x);
		float b = abs(GetPos().y - Player::MainPlayer->GetPos().y);

		if ((distance > a) &&
			(distance > b))
		{
			float4 Dir = Player::MainPlayer->GetPos() - GetPos();
			// Dir.y = 0.0f;
			Dir.Normalize();
			SetMove(Dir * 100.0f * _DeltaTime);

			AnimationRender->ChangeAnimation("Left_Move");
		}
		else
		{
			AnimationRender->ChangeAnimation("Left_Idle");

		}


		std::vector<GameEngineCollision*> Collision;
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
		{
			for (size_t i = 0; i < Collision.size(); i++)
			{
				GameEngineActor* ColActor = Collision[i]->GetActor();
				ColActor->SetPos(Infloat);
			}

			SetPos(Infloat2);
		}

		std::vector<GameEngineCollision*> Collision2;
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Bullet), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision2))
		{
			for (size_t i = 0; i < Collision2.size(); i++)
			{
				GameEngineActor* ColActor = Collision2[i]->GetActor();
				ColActor->Off();
				isdeath = true;
				GetSoundPlayer = GameEngineResources::GetInst().SoundPlayToControl("enemydeath.wav");
				GetSoundPlayer.LoopCount(1);
				GetSoundPlayer.Volume(0.1f);
				break;
			}
		}
	}
	

}