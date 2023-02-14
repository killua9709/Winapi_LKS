#include "TitleBack.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

TitleBack::TitleBack()
{
}

TitleBack::~TitleBack()
{
}


void TitleBack::Start()
{
	{
		GameEngineWindow::SettingWindowSize({ 205,205 });
		GameEngineRender* Render = CreateRender("·Î°í.bmp", BubbleRenderOrder::BackGround);
		Render->SetPosition(GameEngineWindow::GetScreenSize().half());
		Render->SetScale(GameEngineWindow::GetScreenSize());
	}

	
}

void TitleBack::Update(float _DeltaTime)
{
	if (false == GameEngineInput::IsKey("Click"))
	{
		GameEngineInput::CreateKey("Click", 'a');
	}

	if(1 == ScreenNumber)
	{
		GameEngineWindow::SettingWindowSize({ 391,391 });
		GameEngineRender* Render = CreateRender("Å°ÁÂÆÇ.bmp", BubbleRenderOrder::BackGround);
		Render->SetPosition(GameEngineWindow::GetScreenSize().half());
		Render->SetScale(GameEngineWindow::GetScreenSize());
	}


}