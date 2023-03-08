#include "MouseObject.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnums.h"


MouseObject::MouseObject() 
{
}

MouseObject::~MouseObject() 
{
}

void MouseObject::Start() 
{
	MouseRender = CreateRender(GameRenderOrder::Cursor);
	MouseRender->SetScale({ 24, 24 });
	MouseRender->CreateAnimation({ .AnimationName = "cursor1",  .ImageName = "커서.bmp", .Start = 0, .End = 0 });
	MouseRender->CreateAnimation({ .AnimationName = "cursor2",  .ImageName = "커서.bmp", .Start = 1, .End = 1 });
	MouseRender->ChangeAnimation("cursor1");

	BodyCollision = CreateCollision(GameCollisionOrder::Cursor);
	BodyCollision->SetScale({ 10,10 });

	if (nullptr == MouseRender)
	{
		MsgAssert("랜더러가 만들어지지 않았습니다.");
	}

}

void MouseObject::Update(float _DeltaTime) 
{
	SetPos(GetLevel()->GetMousePosToCamera());

	if (BodyCollision->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Bullet), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
	{
		MouseRender->ChangeAnimation("cursor2");
	}
	else
	{
		MouseRender->ChangeAnimation("cursor1");
	}
}