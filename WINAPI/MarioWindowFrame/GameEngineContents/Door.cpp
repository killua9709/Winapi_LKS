#include "Door.h"
#include "Player.h"
#include "ContentsEnums.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include "STLevel.h"


Door::Door()
{
}

Door::~Door()
{
}

void Door::Start()
{
	BodyCollision = CreateCollision(GameCollisionOrder::Object);
	BodyCollision->SetScale({ 28, 40 });

	render = CreateRender("¹®.bmp", GameRenderOrder::Map);
	render->SetScale({ 34, 40 });
	render->CreateAnimation({ .AnimationName = "door1",  .ImageName = "¹®.bmp", .Start = 0, .End = 0 });
	render->CreateAnimation({ .AnimationName = "door2",  .ImageName = "¹®.bmp", .Start = 1, .End = 1 });
	render->ChangeAnimation("door1");
}

void Door::Update(float _DeltaTime)
{
	if (true == Lock)
	{
		render->ChangeAnimation("door2");

		if (true == STLevel::GetGetKey() && true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			GetSoundPlayer = GameEngineResources::GetInst().SoundPlayToControl("door_open.wav");
			GetSoundPlayer.LoopCount(1);
			GetSoundPlayer.Volume(0.1f);
			STLevel::SetGetDoor(true);
			this->Death();
		}
	}
	else
	{
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
		{
			GetSoundPlayer = GameEngineResources::GetInst().SoundPlayToControl("door_open.wav");
			GetSoundPlayer.LoopCount(1);
			GetSoundPlayer.Volume(0.1f);
			STLevel::SetGetDoor(true);
			this->Death();
		}
	}
	
}

void Door::Render(float _DeltaTime)
{

}
