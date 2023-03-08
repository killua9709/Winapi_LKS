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

	GameEngineRender* Render = CreateRender("Cannon.bmp", GameRenderOrder::Monster);
	Render->SetScale({ 102, 102 });
	Render->CreateAnimation({ .AnimationName = "Cannon_Idle",  .ImageName = "Cannon.bmp", .Start = 0, .End = 0 });
	Render->CreateAnimation({ .AnimationName = "Cannon_Fire",  .ImageName = "Cannon.bmp", .Start = 1, .End = 5 ,.InterTime = 0.12 });

	Render->ChangeAnimation("Cannon_Fire");

	for (size_t i = 0; i < 6; i++)
	{
		
		CannonBullet* bullet = GetLevel()->CreateActor<CannonBullet>(GameRenderOrder::Cursor);
		bullet->SetMove({ GetPos().x,GetPos().y - 15 });
		Bullets.push_back(bullet);
		Bullets[i]->Off();
	}
}

void Cannon::Update(float _DeltaTime)
{
	firetime += _DeltaTime;

	if (1.5 < firetime)
	{
		GetSoundPlayer = GameEngineResources::GetInst().SoundPlayToControl("cannon.wav");
		GetSoundPlayer.LoopCount(1);
		GetSoundPlayer.Volume(0.005f);

		for (size_t i = 0; i < 6; i++)
		{
			if (false == Bullets[i]->isOn())
			{
				Bullets[i]->SetPos({ GetPos().x+10,GetPos().y +16 });
				Bullets[i]->On();
				break;
			}
		}
	}
}

void Cannon::Render(float _DeltaTime)
{

}

