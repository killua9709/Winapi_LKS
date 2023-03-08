#include "Stage1_1Level.h"

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
#include "Stage1_1Map.h"
#include "ContentsEnums.h"
#include "ContentsValue.h"
#include "MouseObject.h"
#include "Wall.h"
#include "Bullet.h"
#include "Scroll.h"
#include "Bullet.h"


Stage1_1Level::Stage1_1Level()
{

}

Stage1_1Level::~Stage1_1Level()
{
	
}

void Stage1_1Level::SoundLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");

	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Fireball.mp3"));
}
void Stage1_1Level::ImageLoad()
{
	GameEngineWindow::SettingWindowSize({ 1280,960 });

	// 상대경로 탐색
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Play");

	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("stage1_1Map.bmp"));
		Image->Cut(1, 1);
	}
	
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Bullets.bmp"));
		Image->Cut(6, 1);
	}

}



void Stage1_1Level::Loading()
{
	ImageLoad();
	SoundLoad();

	//마우스
	{
		CreateActor<MouseObject>();
	}
	//맵
	{
		Stage1_1Map* Actor = CreateActor<Stage1_1Map>();
	}
	//플레이어
	{
		Mario = CreateActor<Player>(GameRenderOrder::Player);
		Mario->SetMove({ 372,544 });
	}
	//벽
	{
		//가로벽
		Wall* Wight4 = CreateActor<Wall>(GameRenderOrder::Map);
		Wight4->SetMove({ 612,697 });
		Wight4->GetBodyCollision()->SetScale({ 1200, 34 });


		//세로벽
		Wall* length = CreateActor<Wall>(GameRenderOrder::Map);
		length->SetMove({ 289, 350 });
		length->GetBodyCollision()->SetScale({ 34, 714 });

		Wall* length2 = CreateActor<Wall>(GameRenderOrder::Map);
		length2->SetMove({ 1003, 350 });
		length2->GetBodyCollision()->SetScale({ 34, 714 });




		//장애물
		Wall* Obstacle = CreateActor<Wall>(GameRenderOrder::Map);
		Obstacle->SetMove({ 374,612 });
		Obstacle->GetBodyCollision()->SetScale({ 136, 136 });

		Wall* Obstacle2 = CreateActor<Wall>(GameRenderOrder::Map);
		Obstacle2->SetMove({ 510,646 });
		Obstacle2->GetBodyCollision()->SetScale({ 136,68 });

		Wall* Obstacle3 = CreateActor<Wall>(GameRenderOrder::Map);
		Obstacle3->SetMove({ 918,612 });
		Obstacle3->GetBodyCollision()->SetScale({ 136,136 });


		//{{윈도우 틀
		Left = CreateActor<Wall>(GameRenderOrder::Map);
		Left->SetPos({ Mario->GetPos().x - GetCameraScale().x,Mario->GetPos().y + GetCameraScale().y });
		Left->GetBodyCollision()->SetScale({ 10, 2000 });

		Right = CreateActor<Wall>(GameRenderOrder::Map);
		Right->SetPos({ Mario->GetPos().x + GetCameraScale().x,Mario->GetPos().y + GetCameraScale().y });
		Right->GetBodyCollision()->SetScale({ 10, 2000 });

		Top = CreateActor<Wall>(GameRenderOrder::Map);
		Top->SetPos({ Mario->GetPos().x + GetCameraScale().x,Mario->GetPos().y - GetCameraScale().y });
		Top->GetBodyCollision()->SetScale({ 2000, 10 });

		Bot = CreateActor<Wall>(GameRenderOrder::Map);
		Bot->SetPos({ Mario->GetPos().x + GetCameraScale().x,Mario->GetPos().y + GetCameraScale().y });
		Bot->GetBodyCollision()->SetScale({ 2000, 10 });
		//}}
	}
	//오브젝트
	{
		/*scroll = CreateActor<Scroll>(GameRenderOrder::Cursor);
		scroll->SetMove({ 629,600 });*/
		
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

void Stage1_1Level::Update(float _DeltaTime)
{
	

	if (GameEngineInput::IsDown("DebugRenderSwitch"))
	{
		/*if (false == BGMPlayer.GetPause())
		{
			BGMPlayer.PauseOn();
		}
		else
		{
			BGMPlayer.PauseOff();
		}*/
		DebugRenderSwitch();
		// Player::MainPlayer->Death()p;
	}
	
	//{{카메라 렉트
	CameraRectUpdate();
	//}}

	if (true == Getisdebug())
	{
		SetCameraScale({ 640,360 });
		GameEngineWindow::SettingWindowSize({ 1280,720 });
		GameEngineWindow::SettingWindowPos({ (float)screenWidth / 2 - 640, (float)screenHeight / 2 - 360 });
		SetCameraPos({ 0,0 });
	}
	else
	{
		SetCameraScale({ 130,130 });
		float4 c = { Right->GetPos().x - Left->GetPos().x,  Bot->GetPos().y - Top->GetPos().y };
		GameEngineWindow::SettingWindowSize(c);
		SetCameraPos({ Left->GetPos().x + c.x/2 -LeftElse/2 -RightElse/2, Top->GetPos().y + c.y/2 -TopElse/2 -BotElse/2});
		float ddd = BotElse;
		SetCameraMove(-GetCameraScale());
		screenSizex = GameEngineWindow::GetScreenSize().x;
		screenSizey = GameEngineWindow::GetScreenSize().y;
		float a = screenWidth / 2 - 640.0f;
		float b = screenHeight / 2 - 360.0f;
		GameEngineWindow::SettingWindowPos({ a + GetCameraPos().x, b + GetCameraPos().y });
	}
}

void Stage1_1Level::LevelChangeStart(GameEngineLevel* _PrevLevel)
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

void Stage1_1Level::CameraRectUpdate()
{
	if (false == Left->GetBodyCollision()->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Bullet), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
	{
		Left->SetPos({ Mario->GetPos().x - GetCameraScale().x,Mario->GetPos().y + GetCameraScale().y});
		Left->GetBodyCollision()->SetScale({ 10, 2000 });
		LeftElse = 0;
		
	}
	else
	{
		float a = Mario->GetPos().x - Left->GetPos().x;
		if (a > 130)
		{
			LeftElse = a - 130;
		}
		else
		{
			LeftElse = -(130 - a);
		}
	}
	
	if (false == Right->GetBodyCollision()->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Bullet), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
	{
		Right->SetPos({ Mario->GetPos().x + GetCameraScale().x,Mario->GetPos().y + GetCameraScale().y });
		Right->GetBodyCollision()->SetScale({ 10, 2000 });
		RightElse = 0;
	}
	else
	{
		float a = Right->GetPos().x -Mario->GetPos().x ;
		if (a > 130)
		{
			RightElse = a - 130;
		}
		else
		{
			RightElse = -(130 - a);
		}
	}
	
	if (false == Top->GetBodyCollision()->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Bullet), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
	{
		Top->SetPos({ Mario->GetPos().x + GetCameraScale().x,Mario->GetPos().y - GetCameraScale().y});
		Top->GetBodyCollision()->SetScale({ 2000, 10 });
		TopElse = 0;
	}
	else
	{
		float a = Mario->GetPos().y - Top->GetPos().y ;
		if (a > 130)
		{
			TopElse = a - 130;
		}
		else
		{
			TopElse = -(130 - a);
		}
	}
	
	if (false == Bot->GetBodyCollision()->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Bullet), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
	{
		Bot->SetPos({ Mario->GetPos().x + GetCameraScale().x,Mario->GetPos().y + GetCameraScale().y });
		Bot->GetBodyCollision()->SetScale({ 2000, 10 });
		BotElse = 0;
	}
	else
	{
		float a = Bot->GetPos().y - Mario->GetPos().y;
		if (a > 130)
		{
			BotElse = a - 130;
		}
		else
		{
			BotElse = -(130 - a);
		}
	}
}