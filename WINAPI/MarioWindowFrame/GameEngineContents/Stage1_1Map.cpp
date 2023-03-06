#include "Stage1_1Map.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"

Stage1_1Map* Stage1_1Map::MainMap = nullptr;

Stage1_1Map::Stage1_1Map()
{
	MainMap = this;
}

Stage1_1Map::~Stage1_1Map()
{
}


void Stage1_1Map::Start()
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
			MapRender->SetImage("stage1_1Map.bmp");
			MapRender->SetPosition(MapRender->GetImage()->GetImageScale().half());
			MapRender->SetScaleToImage();
		}
	}

}


void Stage1_1Map::Update(float _DeltaTime)
{


}