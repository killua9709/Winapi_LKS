#include "Monster.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Player.h"

Monster::Monster() 
{
}

Monster::~Monster() 
{
}


void Monster::Start() 
{
	AnimationRender = CreateRender(BubbleRenderOrder::Monster);
	AnimationRender->SetScale({ 200, 200 });

	AnimationRender->CreateAnimation({ .AnimationName = "Right_Idle",  .ImageName = "Right_Player.bmp", .Start = 0, .End = 2, .InterTime = 0.3f });
	AnimationRender->CreateAnimation({ .AnimationName = "Right_Move",  .ImageName = "Right_Player.bmp", .Start = 3, .End = 7 });

	AnimationRender->CreateAnimation({ .AnimationName = "Left_Idle",  .ImageName = "Left_Player.bmp", .Start = 0, .End = 2, .InterTime = 0.3f });
	AnimationRender->CreateAnimation({ .AnimationName = "Left_Move",  .ImageName = "Left_Player.bmp", .Start = 3, .End = 7 });
	AnimationRender->ChangeAnimation("Right_Idle");

	{
		BodyCollision = CreateCollision(BubbleCollisionOrder::Monster);
		BodyCollision->SetScale({ 50, 50 });
		BodyCollision->Off();
	}
}


void Monster::Update(float _DeltaTime) 
{
	float4 Dir = Player::MainPlayer->GetPos() - GetPos();
	// Dir.y = 0.0f;
	Dir.Normalize();
	SetMove(Dir * 200.0f * _DeltaTime);

	//if (true == BodyCollision->Collision({.TargetGroup = static_cast<int>(BubbleCollisionOrder::Player)}))
	//{
	//	int a = 0;
	//}

	//std::vector<GameEngineCollision*> Collision;
	//if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(BubbleCollisionOrder::Player) }, Collision))
	//{
	//	for (size_t i = 0; i < Collision.size(); i++)
	//	{
	//		// Monster* FindMonster = Collision[i]->GetOwner<Monster>();

	//		GameEngineActor* ColActor = Collision[i]->GetActor();


	//		int a = 0;
	//	}
	//}

	//std::vector<GameEngineActor*> Actors = GetLevel()->GetActors(BubbleRenderOrder::Player);

	//for (size_t i = 0; i < Actors.size(); i++)
	//{
	//	float4 Dir = Actors[i]->GetPos() - GetPos();
	//	if (Dir.Size() <= 100.0f)
	//	{
	//		int a = 0;
	//	}
	//}
	
}