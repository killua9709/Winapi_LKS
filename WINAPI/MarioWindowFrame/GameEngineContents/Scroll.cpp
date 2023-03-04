#include "Scroll.h"
#include "Player.h"
#include "ContentsEnums.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>




Scroll::Scroll() 
{
}

Scroll::~Scroll() 
{
}

void Scroll::Start()
{
	BodyCollision = CreateCollision(GameCollisionOrder::Object);
	BodyCollision->SetScale({ 24, 17 });

	GameEngineRender* Render = CreateRender("scroll.bmp", GameRenderOrder::Cursor);
	Render->SetScale({34, 34});
}

void Scroll::Update(float _DeltaTime)
{
	if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
	{
		this->Death();
	}
}

void Scroll::Render(float _DeltaTime)
{

}
