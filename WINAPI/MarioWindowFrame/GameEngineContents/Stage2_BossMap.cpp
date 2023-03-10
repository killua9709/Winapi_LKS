#include "Stage2_BossMap.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"

Stage2_BossMap* Stage2_BossMap::MainMap = nullptr;

Stage2_BossMap::Stage2_BossMap()
{
	MainMap = this;
}

Stage2_BossMap::~Stage2_BossMap()
{
}


void Stage2_BossMap::Start()
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
			MapRender->SetImage("Stage2_BossMap.bmp");
			MapRender->SetPosition(MapRender->GetImage()->GetImageScale().half());
			MapRender->SetScaleToImage();
		}
	}

}


void Stage2_BossMap::Update(float _DeltaTime)
{


}