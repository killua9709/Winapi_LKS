#include "Map.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"

Map* Map::MainMap = nullptr;

Map::Map() 
{
	MainMap = this;
}

Map::~Map() 
{
}


void Map::Start()
{
	{
		// float4 Scree = GameEngineWindow::GetScreenSize();

		{
			BackGroundRender = CreateRender(BubbleRenderOrder::BackGround);
			BackGroundRender->SetPosition(GameEngineWindow::GetScreenSize().half());
			BackGroundRender->SetScale(GameEngineWindow::GetScreenSize());
			BackGroundRender->SetImage("¹è°æ.Bmp");
		}

		{
			MapRender0 = CreateRender(BubbleRenderOrder::Map);
			MapRender0->SetImage("½ÃÀÛ¸Ê.Bmp");
			MapRender0->SetPosition(MapRender0->GetImage()->GetImageScale().half());
			MapRender0->SetScaleToImage();
		}

		{
			MapRender1 = CreateRender(BubbleRenderOrder::Map);
			MapRender1->SetImage("½ÃÀÛ¸Ê.Bmp");

			float4 StartPos = MapRender0->GetImage()->GetImageScale().half();
			StartPos.x += GameEngineWindow::GetScreenSize().x;
			MapRender1->SetPosition(StartPos);
			MapRender1->SetScaleToImage();
		}

		/*AnimationRender->SetImage("Map_Spaceport.Bmp");
		AnimationRender->SetPosition(AnimationRender->GetImage()->GetImageScale().half());
		AnimationRender->SetScaleToImage();*/
		// AnimationRender->ChangeAnimation("Loop");
	}

}


void Map::Update(float _DeltaTime)
{
	if (false == IsStageClear)
	{
		return;
	}

	MapRender0->SetMove(float4::Left * 200.0f * _DeltaTime);
	MapRender1->SetMove(float4::Left * 200.0f * _DeltaTime);

	// IsStageClear = false;
}