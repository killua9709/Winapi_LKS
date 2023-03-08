#include "Tutorial2Level.h"

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
#include "Tutorial2Map.h"
#include "ContentsEnums.h"
#include "ContentsValue.h"
#include "MouseObject.h"
#include "Wall.h"
#include "Scroll.h"
#include "Door.h"


Tutorial2Level::Tutorial2Level()
{

}

Tutorial2Level::~Tutorial2Level()
{
}

void Tutorial2Level::SoundLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");

	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("stage2backgroundsound.mp3"));
}
void Tutorial2Level::ImageLoad()
{
	GameEngineWindow::SettingWindowSize({ 1280,960 });

	// 상대경로 탐색
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Play");

	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("시작맵2.BMP"));
		Image->Cut(1, 1);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("시작맵2_1.BMP"));
		Image->Cut(1, 1);
	}
}

void Tutorial2Level::Loading()
{
	SoundLoad();
	ImageLoad();

	//마우스
	{
		CreateActor<MouseObject>();
	}
	//맵
	{
		Tutorial2Map* Actor = CreateActor<Tutorial2Map>();
	}
	//플레이어
	{
		Mario = CreateActor<Player>(GameRenderOrder::Player);
		Mario->SetMove({ 206,680 });
	}
	//벽
	{
		//가로벽
		Wall* Wight4 = CreateActor<Wall>(GameRenderOrder::Map);
		Wight4->SetMove({ 612,697 });
		Wight4->GetBodyCollision()->SetScale({ 1200, 34 });


		//세로벽
		Wall* length = CreateActor<Wall>(GameRenderOrder::Map);
		length->SetMove({ 119, 350 });
		length->GetBodyCollision()->SetScale({ 34, 714 });

		Wall* length2 = CreateActor<Wall>(GameRenderOrder::Map);
		length2->SetMove({ 1139, 350 });
		length2->GetBodyCollision()->SetScale({ 34, 714 });




		//장애물
		Wall* Obstacle = CreateActor<Wall>(GameRenderOrder::Map);
		Obstacle->SetMove({ 629,646 });
		Obstacle->GetBodyCollision()->SetScale({ 170, 68 });

		Wall* Obstacle2 = CreateActor<Wall>(GameRenderOrder::Map);
		Obstacle2->SetMove({ 1037,663 });
		Obstacle2->GetBodyCollision()->SetScale({ 170,34 });


		//윈도우 틀
		Wall* Left = CreateActor<Wall>(GameRenderOrder::Map);
		Left->SetMove({ 0,360 });
		Left->GetBodyCollision()->SetScale({ 1, 720 });

		Wall* Right = CreateActor<Wall>(GameRenderOrder::Map);
		Right->SetMove({ 1280,360 });
		Right->GetBodyCollision()->SetScale({ 1, 720 });

		Wall* Top = CreateActor<Wall>(GameRenderOrder::Map);
		Top->SetMove({ 640,0 });
		Top->GetBodyCollision()->SetScale({ 1280, 10 });

		Wall* Bot = CreateActor<Wall>(GameRenderOrder::Map);
		Bot->SetMove({ 640,720 });
		Bot->GetBodyCollision()->SetScale({ 1280, 10 });

	}
	//오브젝트
	{
		scroll = CreateActor<Scroll>(GameRenderOrder::Cursor);
		scroll->SetMove({ 629,600 });

		door = CreateActor<Door>(GameRenderOrder::Cursor);
		door->SetMove({ 1037,628 });
	}


	if (false == GameEngineInput::IsKey("DebugRenderSwitch"))
	{
		GameEngineInput::CreateKey("DebugRenderSwitch", 'M');
	}


	if (false == GameEngineInput::IsKey("CameraLeftMove"))
	{
		// VK 알파뱃과 숫자를 제외한 키를 표현하는데 쓰고 있다. 
		GameEngineInput::CreateKey("CameraLeftMove", VK_LEFT);
		GameEngineInput::CreateKey("CameraRightMove", VK_RIGHT);
		GameEngineInput::CreateKey("CameraDownMove", VK_DOWN);
		GameEngineInput::CreateKey("CameraUpMove", VK_UP);
	}
}

void Tutorial2Level::Update(float _DeltaTime)
{
	if (true == GetDoor)
	{
		SetGetDoor(false);
		GameEngineCore::GetInst()->ChangeLevel("Stage1_1Level");
	}
	if (GameEngineInput::IsDown("DebugRenderSwitch"))
	{


		if (false == BGMPlayer.GetPause())
		{
			BGMPlayer.PauseOn();
		}
		else
		{
			BGMPlayer.PauseOff();
		}

		DebugRenderSwitch();
		// Player::MainPlayer->Death()p;
	}

	if (false == scroll->GetObjectisDeath())
	{

		SetCameraPos({ Mario->GetPos().x,Mario->GetPos().y });
		SetCameraMove(-GetCameraScale());
		/*IsScreenOut();*/
		screenSizex = GameEngineWindow::GetScreenSize().x;
		screenSizey = GameEngineWindow::GetScreenSize().y;
		float a = screenWidth / 2 - 640.0f;
		float b = screenHeight / 2 - 360.0f;
		GameEngineWindow::SettingWindowPos({ a + GetCameraPos().x, b + GetCameraPos().y });
	}
	else if (false == Fix)
	{
		GameEngineWindow::SettingWindowSize({ 1280,720 });
		GameEngineWindow::SettingWindowPos({ (float)screenWidth / 2 - 640, (float)screenHeight / 2 - 360 });
		SetCameraPos({ 0,0 });
		Fix = true;
		Tutorial2Map::MainMap->SetScroll(true);

	}


}

void Tutorial2Level::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	GameEngineWindow::SettingWindowSize({ 260,260 });
	screenSizex = GameEngineWindow::GetScreenSize().x;
	screenSizey = GameEngineWindow::GetScreenSize().y;
	SetCameraPos({ Mario->GetPos().x,Mario->GetPos().y });
	SetCameraScale({ 130, 130 });
	SetCameraMove(-GetCameraScale());
	//모니터 크기 절반에 내 스크린 사이즈 절반 만큼 빼서 크기 조정
	GameEngineWindow::SettingWindowPos({ screenWidth / 2 - (screenSizex / 2) ,screenHeight / 2 - (screenSizey / 2) });
	//GameEngineWindow::WindowExpand();
}