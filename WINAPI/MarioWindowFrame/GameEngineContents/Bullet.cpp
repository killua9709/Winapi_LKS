#include "Bullet.h"
#include "Player.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>




Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}

void Bullet::Fire()
{
	GetSoundPlayer = GameEngineResources::GetInst().SoundPlayToControl("Fireball.mp3");
	GetSoundPlayer.LoopCount(1);
	GetSoundPlayer.Volume(0.1f);
}

void Bullet::Start()
{
	BodyCollision = CreateCollision(GameCollisionOrder::Object);
	BodyCollision->SetScale({ 16, 16 });
	BodyCollision->SetPosition({ 0, -8 });

	AnimationRender = CreateRender("fireball.bmp", GameRenderOrder::Cursor);
	AnimationRender->SetScale({ 51, 51 });

	AnimationRender->CreateAnimation({ .AnimationName = "Running",  .ImageName = "fireball.bmp", .Start = 0, .End = 3, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Fix",  .ImageName = "fireball.bmp", .Start = 3, .End = 4 ,.Loop = false });

	AnimationRender->ChangeAnimation("Running");
}

void Bullet::Update(float _DeltaTime)
{
	
	if (false == first)
	{
		targetpos = GetLevel()->GetMousePosToCamera();
		Move = (targetpos - GetPos()).NormalizeReturn();
		Fire();
		first = true;
	}

	if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Wall), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
	{
		AnimationRender->ChangeAnimation("Fix");

	}
	else
	{
		SetMove(Move * _DeltaTime * 600);
	}
}

void Bullet::Render(float _DeltaTime)
{

}
