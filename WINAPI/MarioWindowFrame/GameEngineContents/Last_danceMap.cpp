#include "Last_danceMap.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"

Last_danceMap* Last_danceMap::MainMap = nullptr;

Last_danceMap::Last_danceMap()
{
	MainMap = this;
}

Last_danceMap::~Last_danceMap()
{
}


void Last_danceMap::Start()
{
	{
		// float4 Scree = GameEngineWindow::GetScreenSize();

		{
			BackGroundRender = CreateRender(GameRenderOrder::BackGround);
			BackGroundRender->SetPosition(GameEngineWindow::GetScreenSize().half());
			BackGroundRender->SetScale(GameEngineWindow::GetScreenSize());
			BackGroundRender->SetImage("¹è°æ.Bmp");
		}

		{
			Last_danceMapRender0 = CreateRender(GameRenderOrder::Map);
			Last_danceMapRender0->SetImage("Last_danceMap.bmp");
			Last_danceMapRender0->SetPosition(Last_danceMapRender0->GetImage()->GetImageScale().half());
			Last_danceMapRender0->SetScaleToImage();
		}
	}

}


void Last_danceMap::Update(float _DeltaTime)
{
	if (false == IsStageClear)
	{
		return;
	}


	// IsStageClear = false;
}