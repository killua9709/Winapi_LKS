#include "TitleBack.h"
#include "ContentsEnums.h"
#include <Windows.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>



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
		GameEngineWindow::SettingWindowPos({ (float)GetSystemMetrics(SM_CXSCREEN)/2 -103, (float)GetSystemMetrics(SM_CYSCREEN)/2 -103});
		GameEngineRender* Render = CreateRender("·Î°í.bmp", GameRenderOrder::BackGround);
		Render->SetPosition(GameEngineWindow::GetScreenSize().half());
		Render->SetScale(GameEngineWindow::GetScreenSize());
	}
}

bool page2 = false;
bool page3 = false;

void TitleBack::Update(float _DeltaTime)
{
	if ((GameEngineInput::IsPress("EnginemouseLeft")) &&
		(0 < GetLevel()->GetMousePosToCamera().x)&&
		(GameEngineWindow::GetMousePosition().x < GameEngineWindow::GetScreenSize().x)&&
		(0 < GetLevel()->GetMousePosToCamera().y)&&
		GameEngineWindow::GetMousePosition().y < GameEngineWindow::GetScreenSize().y)
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
		GameEngineWindow::SettingWindowPos({ (float)GetSystemMetrics(SM_CXSCREEN) / 2 - 131, (float)GetSystemMetrics(SM_CYSCREEN) / 2 - 35 });
		GameEngineWindow::WindowExpand();
		GameEngineRender* Render = CreateRender("title.bmp", GameRenderOrder::BackGround);
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
		GameEngineWindow::SettingWindowPos({ (float)GetSystemMetrics(SM_CXSCREEN) / 2 - 195, (float)GetSystemMetrics(SM_CYSCREEN) / 2 - 195 });
		GameEngineWindow::WindowExpand();
		GameEngineRender* Render = CreateRender("Å°ÁÂÆÇ.bmp", GameRenderOrder::BackGround);
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