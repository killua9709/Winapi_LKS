#include "Last_danceLevel.h"

#include "Structs.h"

// 프로젝트 순서에 따라서 정렬
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCore.h>



// 나랑 같은 등급의 헤더들
#include "Player.h"
#include "Monster.h"
#include "Last_danceMap.h"
#include "ContentsEnums.h"
#include "ContentsValue.h"
#include "MouseObject.h"
#include "Wall.h"
#include "Scroll.h"
#include "Door.h"


Last_danceLevel::Last_danceLevel()
{

}

Last_danceLevel::~Last_danceLevel()
{

}

void Last_danceLevel::SoundLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");

	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Lastdance.mp3"));
	

}
void Last_danceLevel::ImageLoad()
{
	GameEngineWindow::SettingWindowSize({ 1280,960 });
	GameEngineWindow::SettingWindowPos({ (float)screenWidth / 2 - 640,(float)screenHeight / 2 - 480 });
	// 상대경로 탐색
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Play");

	// 이미지 로드
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Last_danceMap.bmp"));
	}
	
}

void Last_danceLevel::Loading()
{
	SoundLoad();
	ImageLoad();
	Last_danceMap* Actor = CreateActor<Last_danceMap>();
}

void Last_danceLevel::Update(float _DeltaTime)
{

	
}

void Last_danceLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	BGMPlayer.Stop();
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Lastdance.mp3");
	BGMPlayer.Volume(0.1f);
	GameEngineWindow::SettingWindowSize({ 1280,720 });
	GameEngineWindow::SettingWindowPos({ (float)screenWidth / 2 - 640, (float)screenHeight / 2 - 360 });
	SetCameraPos({ 0,0 });
	//모니터 크기 절반에 내 스크린 사이즈 절반 만큼 빼서 크기 조정
	GameEngineWindow::SettingWindowPos({ screenWidth / 2 - (screenSizex / 2) ,screenHeight / 2 - (screenSizey / 2) });
	//GameEngineWindow::WindowExpand();
}