#include "Stage1_BossMap.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"

Stage1_BossMap* Stage1_BossMap::MainMap = nullptr;

Stage1_BossMap::Stage1_BossMap()
{
	MainMap = this;
}

Stage1_BossMap::~Stage1_BossMap()
{
}


void Stage1_BossMap::Start()
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
			MapRender->SetImage("Stage1_BossMap.bmp");
			MapRender->SetPosition(MapRender->GetImage()->GetImageScale().half());
			MapRender->SetScaleToImage();
		}
	}

}


void Stage1_BossMap::Update(float _DeltaTime)
{


}