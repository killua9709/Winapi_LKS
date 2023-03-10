#include "Stage2_2Level.h"

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
#include "Stage2_2Map.h"
#include "ContentsEnums.h"
#include "ContentsValue.h"
#include "MouseObject.h"
#include "Wall.h"
#include "Bullet.h"
#include "Scroll.h"
#include "Bullet.h"
#include "MouseObject.h"
#include "Door.h"
#include "Cannon.h"
#include "Key.h"
#include "Monster.h"
#include "Thorn.h"


Stage2_2Level::Stage2_2Level()
{

}

Stage2_2Level::~Stage2_2Level()
{

}

void Stage2_2Level::SoundLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");

}
void Stage2_2Level::ImageLoad()
{
	GameEngineWindow::SettingWindowSize({ 1280,960 });

	// 상대경로 탐색
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Play");

	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Stage2_2Map.bmp"));
		Image->Cut(1, 1);
	}
}



void Stage2_2Level::Loading()
{
	ImageLoad();
	//마우스
	{
		Mouse = CreateActor<MouseObject>();
	}
	//맵
	{
		Stage2_2Map* Actor = CreateActor<Stage2_2Map>();
	}
	//플레이어
	{
		Mario = CreateActor<Player>(GameRenderOrder::Player);
		Mario->SetMove({ 372,198 });
	}
	//벽
	{
		//가로벽
		Wall* Wight4 = CreateActor<Wall>(GameRenderOrder::Map);
		Wight4->SetMove({ 612,357 });
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
		Obstacle->SetMove({ 374,272 });
		Obstacle->GetBodyCollision()->SetScale({ 136, 136 });

		Wall* Obstacle2 = CreateActor<Wall>(GameRenderOrder::Map);
		Obstacle2->SetMove({ 918,272 });
		Obstacle2->GetBodyCollision()->SetScale({ 136, 136 });


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
		door = CreateActor<Door>(GameRenderOrder::Cursor);
		door->SetMove({ 932,187 }); //544 //16

		Thorn* thorn = CreateActor<Thorn>(GameRenderOrder::Map);
		thorn->SetMove({ 527,355 });
		thorn->SetInfloat({ 372,198 });

		Thorn* thorn2 = CreateActor<Thorn>(GameRenderOrder::Map);
		thorn2->SetMove({ 561,355 });

		Thorn* thorn3 = CreateActor<Thorn>(GameRenderOrder::Map);
		thorn3->SetMove({ 731,355 });

		Thorn* thorn4 = CreateActor<Thorn>(GameRenderOrder::Map);
		thorn4->SetMove({ 765,355 });
	}
	//몬스터
	{
		Monster* monster = CreateActor<Monster>(GameRenderOrder::Monster);
		monster->SetMove({ 546,198 });
		monster->SetInfloat({ 372,198 });

		Monster* monster2 = CreateActor<Monster>(GameRenderOrder::Monster);
		monster2->SetMove({ 591,198 });

		Monster* monster3 = CreateActor<Monster>(GameRenderOrder::Monster);
		monster3->SetMove({ 636,198 });

		Monster* monster4 = CreateActor<Monster>(GameRenderOrder::Monster);
		monster4->SetMove({ 681,198 });

		Monster* monster5 = CreateActor<Monster>(GameRenderOrder::Monster);
		monster5->SetMove({ 726,198 });
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

void Stage2_2Level::Update(float _DeltaTime)
{

	if (true == GetDoor)
	{
		SetGetDoor(false);
		SetGetKey(false);
		GameEngineCore::GetInst()->ChangeLevel("Stage1_BossLevel");
	}

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
	CameraRectUpdate(_DeltaTime);
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
		SetCameraPos({ Left->GetPos().x + c.x / 2 - LeftElse / 2 - RightElse / 2, Top->GetPos().y + c.y / 2 - TopElse / 2 - BotElse / 2 });
		SetCameraMove(-GetCameraScale());
		screenSizex = GameEngineWindow::GetScreenSize().x;
		screenSizey = GameEngineWindow::GetScreenSize().y;
		float a = screenWidth / 2 - 640.0f;
		float b = screenHeight / 2 - 360.0f;
		GameEngineWindow::SettingWindowPos({ a + GetCameraPos().x, b + GetCameraPos().y });
	}
}

void Stage2_2Level::LevelChangeStart(GameEngineLevel* _PrevLevel)
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

void Stage2_2Level::CameraRectUpdate(float _DeltaTime)
{
	std::vector<GameEngineCollision*> Collision;
	if (false == Left->GetBodyCollision()->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Bullet), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
	{
		Left->Settingdcheck(false);
		Left->SetPos({ Mario->GetPos().x - GetCameraScale().x,Mario->GetPos().y + GetCameraScale().y });
		LeftElse = 0;

	}
	else
	{

		for (size_t i = 0; i < Collision.size(); i++)
		{
			if (GameEngineCollision::CollisionRectToRect(Collision[i]->GetCollisionData(), Mouse->GetBodyCollision()->GetCollisionData()))
			{
				aa = true;
			}
		}

		if (aa)
		{
			for (size_t i = 0; i < Collision.size(); i++)
			{

				Collision[i]->GetActor()->SetMove({ 100 * _DeltaTime });

			}

			Left->SetMove({ 100 * _DeltaTime });
			aa = false;
		}

		/*if (GameEngineInput::IsDown("CameraRightMove"))
		{
			Left->SetMove({ 1 });
		}*/
		Left->Settingdcheck(true);
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

	std::vector<GameEngineCollision*> Collision2;
	if (false == Right->GetBodyCollision()->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Bullet), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision2))
	{
		Right->Settingdcheck(false);
		Right->SetPos({ Mario->GetPos().x + GetCameraScale().x,Mario->GetPos().y + GetCameraScale().y });
		RightElse = 0;
	}
	else
	{
		for (size_t i = 0; i < Collision2.size(); i++)
		{
			if (GameEngineCollision::CollisionRectToRect(Collision2[i]->GetCollisionData(), Mouse->GetBodyCollision()->GetCollisionData()))
			{
				bb = true;
			}
		}

		if (bb)
		{
			for (size_t i = 0; i < Collision2.size(); i++)
			{

				Collision2[i]->GetActor()->SetMove({ -100 * _DeltaTime });

			}

			Right->SetMove({ -100 * _DeltaTime });
			bb = false;
		}
		Right->Settingdcheck(true);
		float a = Right->GetPos().x - Mario->GetPos().x;
		if (a > 130)
		{
			RightElse = a - 130;
		}
		else
		{
			RightElse = -(130 - a);
		}
	}

	std::vector<GameEngineCollision*> Collision3;
	if (false == Top->GetBodyCollision()->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Bullet), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision3))
	{
		Top->Settingdcheck(false);
		Top->SetPos({ Mario->GetPos().x + GetCameraScale().x,Mario->GetPos().y - GetCameraScale().y });
		TopElse = 0;
	}
	else
	{
		for (size_t i = 0; i < Collision3.size(); i++)
		{
			if (GameEngineCollision::CollisionRectToRect(Collision3[i]->GetCollisionData(), Mouse->GetBodyCollision()->GetCollisionData()))
			{
				cc = true;
			}
		}

		if (cc)
		{
			for (size_t i = 0; i < Collision3.size(); i++)
			{

				Collision3[i]->GetActor()->SetMove({ 0,100 * _DeltaTime });

			}

			Top->SetMove({ 0,100 * _DeltaTime });
			cc = false;
		}
		Top->Settingdcheck(true);
		float a = Mario->GetPos().y - Top->GetPos().y;
		if (a > 130)
		{
			TopElse = a - 130;
		}
		else
		{
			TopElse = -(130 - a);
		}
	}

	std::vector<GameEngineCollision*> Collision4;
	if (false == Bot->GetBodyCollision()->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Bullet), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision4))
	{
		Bot->Settingdcheck(false);
		Bot->SetPos({ Mario->GetPos().x + GetCameraScale().x,Mario->GetPos().y + GetCameraScale().y });
		BotElse = 0;
	}
	else
	{
		for (size_t i = 0; i < Collision4.size(); i++)
		{
			if (GameEngineCollision::CollisionRectToRect(Collision4[i]->GetCollisionData(), Mouse->GetBodyCollision()->GetCollisionData()))
			{
				dd = true;
			}
		}

		if (dd)
		{
			for (size_t i = 0; i < Collision4.size(); i++)
			{

				Collision4[i]->GetActor()->SetMove({ 0,-100 * _DeltaTime });

			}

			Bot->SetMove({ 0,-100 * _DeltaTime });
			dd = false;
		}
		Bot->Settingdcheck(true);
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