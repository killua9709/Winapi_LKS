#include "Stage1_2Map.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"

Stage1_2Map* Stage1_2Map::MainMap = nullptr;

Stage1_2Map::Stage1_2Map()
{
	MainMap = this;
}

Stage1_2Map::~Stage1_2Map()
{
}


void Stage1_2Map::Start()
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
			MapRender = CreateRender(GameRenderOrder::Map);
			MapRender->SetImage("Stage1_2Map.bmp");
			MapRender->SetPosition(MapRender->GetImage()->GetImageScale().half());
			MapRender->SetScaleToImage();
		}
	}

}


void Stage1_2Map::Update(float _DeltaTime)
{


}