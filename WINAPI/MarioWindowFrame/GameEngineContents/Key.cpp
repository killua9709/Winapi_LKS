#include "Key.h"
#include "Player.h"
#include "STLevel.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>

Key::Key()
{
}

Key::~Key()
{
}

void Key::Start()
{
	BodyCollision = CreateCollision(GameCollisionOrder::Object);
	BodyCollision->SetScale({ 24, 17 });

	GameEngineRender* Render = CreateRender("Key.bmp", GameRenderOrder::Cursor);
	Render->SetScale({ 34, 34 });
}

void Key::Update(float _DeltaTime)
{
	if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
	{
		GetSoundPlayer = GameEngineResources::GetInst().SoundPlayToControl("getkey.wav");
		GetSoundPlayer.LoopCount(1);
		GetSoundPlayer.Volume(0.1f);
		STLevel::SetGetKey(true);
		this->Death();
	}
}

void Key::Render(float _DeltaTime)
{

}
