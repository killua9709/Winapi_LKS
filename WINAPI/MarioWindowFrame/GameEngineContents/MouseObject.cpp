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
	MouseRender = CreateRender("Ŀ��.bmp", BubbleRenderOrder::Cursor);
	MouseRender->SetScaleToImage();
	MouseCollision = CreateCollision();

	if (nullptr == MouseRender)
	{
		MsgAssert("�������� ��������� �ʾҽ��ϴ�.");
	}

	if (nullptr == MouseCollision)
	{
		MsgAssert("�ݸ����� ��������� �ʾҽ��ϴ�.");
	}
}

void MouseObject::Update(float _DeltaTime) 
{
	SetPos(GetLevel()->GetMousePosToCamera());
}