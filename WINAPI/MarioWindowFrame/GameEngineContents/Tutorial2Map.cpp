#include "Tutorial2Map.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"

Tutorial2Map* Tutorial2Map::MainMap = nullptr;

Tutorial2Map::Tutorial2Map()
{
	MainMap = this;
}

Tutorial2Map::~Tutorial2Map()
{
}


void Tutorial2Map::Start()
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
			TutorialMapRender = CreateRender(GameRenderOrder::Map);
			TutorialMapRender->SetImage("½ÃÀÛ¸Ê2.bmp");
			TutorialMapRender->SetPosition(TutorialMapRender->GetImage()->GetImageScale().half());
			TutorialMapRender->SetScaleToImage();
		}
	}

}


void Tutorial2Map::Update(float _DeltaTime)
{

	if (true == GetScroll && false == Fix)
	{
		TutorialMapRender = CreateRender(GameRenderOrder::Map);
		TutorialMapRender->SetImage("½ÃÀÛ¸Ê2_1.bmp");
		TutorialMapRender->SetPosition(TutorialMapRender->GetImage()->GetImageScale().half());
		TutorialMapRender->SetScaleToImage();
		Fix = true;
	}

	// IsStageClear = false;
}