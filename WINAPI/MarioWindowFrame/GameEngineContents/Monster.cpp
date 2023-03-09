#include "Monster.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <cmath>
#include "Player.h"

Monster::Monster() 
{
}

Monster::~Monster() 
{
	GetSoundPlayer = GameEngineResources::GetInst().SoundPlayToControl("enemydeath.wav");
	GetSoundPlayer.LoopCount(1);
	GetSoundPlayer.Volume(0.1f);
}


void Monster::Start() 
{
	AnimationRender = CreateRender(GameCollisionOrder::Monster);
	AnimationRender->SetScale({ 100, 100 });

	AnimationRender->CreateAnimation({ .AnimationName = "Right_Idle",  .ImageName = "Monster_Right.bmp", .Start = 0, .End = 7, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Right_Move",  .ImageName = "Monster_Right.bmp", .Start = 8, .End = 11 });
	AnimationRender->CreateAnimation({ .AnimationName = "Right_Death",  .ImageName = "Monster_Right.bmp", .Start = 12, .End = 12 });

	AnimationRender->CreateAnimation({ .AnimationName = "Left_Idle",  .ImageName = "Monster_Left.bmp", .Start = 0, .End = 2, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Left_Move",  .ImageName = "Monster_Left.bmp", .Start = 8, .End = 11 });
	AnimationRender->CreateAnimation({ .AnimationName = "Left_Death",  .ImageName = "Monster_Left.bmp", .Start = 12, .End = 12 });
	AnimationRender->ChangeAnimation("Left_Idle");

	{
		BodyCollision = CreateCollision(GameCollisionOrder::Monster);
		BodyCollision->SetScale({ 20, 25 });
		BodyCollision->SetMove({ 0,-17 });
	}
}


void Monster::Update(float _DeltaTime) 
{
	float distance = 100;
	float a = abs(GetPos().x - Player::MainPlayer->GetPos().x);
	float b = abs(GetPos().y - Player::MainPlayer->GetPos().y);



	if ((distance > a)&&
		(distance > b))
	{
		float4 Dir = Player::MainPlayer->GetPos() - GetPos();
		// Dir.y = 0.0f;
		Dir.Normalize();
		SetMove(Dir * 100.0f * _DeltaTime);

		if (GetPos().x < Player::MainPlayer->GetPos().x)
		{
			AnimationRender->ChangeAnimation("Right_Move");
		}
		else
		{
			AnimationRender->ChangeAnimation("Left_Move");
		}
	}
	else if (GetPos().x < Player::MainPlayer->GetPos().x)
	{
		AnimationRender->ChangeAnimation("Right_Idle");
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
			ColActor->SetPos({ 372,100 });
		}

		SetPos({ 614,130 });
	}
	
}