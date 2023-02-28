#include "TutorialMap.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"

TutorialMap* TutorialMap::MainMap = nullptr;

TutorialMap::TutorialMap() 
{
	MainMap = this;
}

TutorialMap::~TutorialMap() 
{
}


void TutorialMap::Start()
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
			TutorialMapRender0 = CreateRender(GameRenderOrder::Map);
			TutorialMapRender0->SetImage("½ÃÀÛ¸Ê.Bmp");
			TutorialMapRender0->SetPosition(TutorialMapRender0->GetImage()->GetImageScale().half());
			TutorialMapRender0->SetScaleToImage();
		}
	}

}


void TutorialMap::Update(float _DeltaTime)
{
	if (false == IsStageClear)
	{
		return;
	}

	TutorialMapRender0->SetMove(float4::Left * 200.0f * _DeltaTime);
	TutorialMapRender1->SetMove(float4::Left * 200.0f * _DeltaTime);

	// IsStageClear = false;
}