#include "TitleLevel.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/Button.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "TitleBack.h"
#include "MouseObject.h"
#include "ContentsValue.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Loading()
{

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Image");
		Dir.Move("Cursor");

		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("커서.BMP"));

	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Sound");
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("blockhit.wav"));
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Coin.wav"));
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Image");
		Dir.Move("Title");

		// 이미지 로드
		{
			GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("로고.BMP"));
		}

		{
			GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("키좌판.BMP"));
		}

		{
			GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("title.BMP"));
		}
	}

	CreateActor<TitleBack>();
	CreateActor<MouseObject>();
}

bool ScrollStart = false;
float4 DownPosTitle = float4::Zero;

void TitleLevel::Update(float _DeltaTime)
{
	if ((true == TitleBack::GetSceneClear()) && WM_LBUTTONDOWN)
	{
		GameEngineWindow::WindowContract();
		GameEngineCore::GetInst()->ChangeLevel("TutorialLevel");
	}
}


void TitleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	float screenWidth = GetSystemMetrics(SM_CXSCREEN);
	float screenHeight = GetSystemMetrics(SM_CYSCREEN);
	GameEngineWindow::SettingWindowSize({ 205,205 });
	screenSizex = GameEngineWindow::GetScreenSize().x;
	screenSizey = GameEngineWindow::GetScreenSize().y;
	GameEngineWindow::SettingWindowPos({ screenWidth/2 - (screenSizex/2) ,screenHeight/2 - (screenSizey /2)});
	GameEngineWindow::WindowExpand();

}