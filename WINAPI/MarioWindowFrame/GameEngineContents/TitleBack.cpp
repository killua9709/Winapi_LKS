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

bool TitleBack::SceneClear = false;

void TitleBack::Start()
{
	
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("blockhit.wav");
	BGMPlayer.LoopCount(3);
	BGMPlayer.Volume(0.2f);

	{
		GameEngineWindow::SettingWindowSize({ 205,205 });
		GameEngineRender* Render = CreateRender("·Î°í.bmp", BubbleRenderOrder::BackGround);
		Render->SetPosition(GameEngineWindow::GetScreenSize().half());
		Render->SetScale(GameEngineWindow::GetScreenSize());
	}

	if (false == GameEngineInput::IsKey("EnginemouseLeft"))
	{
		GameEngineInput::CreateKey("EnginemouseLeft", VK_LBUTTON);
	}

}

bool page2 = false;
bool page3 = false;

void TitleBack::Update(float _DeltaTime)
{
	if (GameEngineInput::IsPress("EnginemouseLeft"))
	{
		ScreenNumber += 1;
	}

	if ((1 == ScreenNumber) && (page2 == false))
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Coin.wav");
		BGMPlayer.LoopCount(1);
		BGMPlayer.Volume(0.2f);
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("blockhit.wav");
		BGMPlayer.LoopCount(2);
		BGMPlayer.Volume(0.2f);
		GameEngineWindow::WindowContract();
		GameEngineWindow::SettingWindowSize({ 262,70 });
		GameEngineWindow::WindowExpand();
		GameEngineRender* Render = CreateRender("title.bmp", BubbleRenderOrder::BackGround);
		Render->SetPosition(GameEngineWindow::GetScreenSize().half());
		Render->SetScale(GameEngineWindow::GetScreenSize());
		page2 = true;
		ScreenNumber = 0;
	}

	if ((1 == ScreenNumber) && (page2 == true) && (page3 == false))
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("blockhit.wav");
		BGMPlayer.LoopCount(1);
		BGMPlayer.Volume(0.2f);
		GameEngineWindow::WindowContract();
		GameEngineWindow::SettingWindowSize({ 391,391 });
		GameEngineWindow::WindowExpand();
		GameEngineRender* Render = CreateRender("Å°ÁÂÆÇ.bmp", BubbleRenderOrder::BackGround);
		Render->SetPosition(GameEngineWindow::GetScreenSize().half());
		Render->SetScale(GameEngineWindow::GetScreenSize());
		page3 = true;
		ScreenNumber = 0;
	}

	if ((1 == ScreenNumber) && (true == page3) && WM_LBUTTONDOWN)
	{
		SceneClear = true;
	}
}