#include "Bullet.h"
#include "Player.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>


Bullet::Bullet() 
{

}

Bullet::~Bullet() 
{

}

void Bullet::Start()
{
	BodyCollision = CreateCollision(GameCollisionOrder::Object);
	BodyCollision->SetScale({ 16, 16 });
	BodyCollision->SetPosition({ 0, -8 });

	AnimationRender = CreateRender("fireball.bmp", GameRenderOrder::Cursor);
	AnimationRender->SetScale({ 51, 51 });

	AnimationRender->CreateAnimation({ .AnimationName = "Running",  .ImageName = "fireball.bmp", .Start = 0, .End = 3, .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "Fix",  .ImageName = "fireball.bmp", .Start = 4, .End = 6 ,.Loop=false});

	AnimationRender->ChangeAnimation("Running");
}

void Bullet::Update(float _DeltaTime)
{
	if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
	{
		AnimationRender->ChangeAnimation("Fix");
	}
}

void Bullet::Render(float _DeltaTime)
{

}
