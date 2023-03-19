#include "Stage1_BossLevel.h"

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
#include "Stage1_BossMap.h"
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
#include "BossMonster.h"
#include "Thorn.h"


Stage1_BossLevel::Stage1_BossLevel()
{

}

Stage1_BossLevel::~Stage1_BossLevel()
{

}

void Stage1_BossLevel::SoundLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");

	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Wizard.mp3"));
}
void Stage1_BossLevel::ImageLoad()
{
	GameEngineWindow::SettingWindowSize({ 1280,960 });

	// 상대경로 탐색
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Play");

	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Stage1_BossMap.bmp"));
		Image->Cut(1, 1);
	}
	
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_Wizard.bmp"));
		Image->Cut(5, 2);
	}

	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Thorn.bmp"));
	}
	
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Death_Effect.bmp"));
		Image->Cut(5, 2);
	}
}



void Stage1_BossLevel::Loading()
{
	SoundLoad();
	ImageLoad();
	//마우스
	{
		Mouse = CreateActor<MouseObject>();
	}
	//맵
	{
		Stage1_BossMap* Actor = CreateActor<Stage1_BossMap>();
	}
	//플레이어
	{
		Mario = CreateActor<Player>(GameRenderOrder::Player);
		Mario->SetMove({ 391,238 });
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
		Obstacle->SetMove({ 442,289 });
		Obstacle->GetBodyCollision()->SetScale({ 272, 102 });

		Wall* Obstacle2 = CreateActor<Wall>(GameRenderOrder::Map);
		Obstacle2->SetMove({ 663,289 });
		Obstacle2->GetBodyCollision()->SetScale({ 34, 102 });

		Wall* Obstacle3 = CreateActor<Wall>(GameRenderOrder::Map);
		Obstacle3->SetMove({ 731,255 });
		Obstacle3->GetBodyCollision()->SetScale({ 34, 102 });

		Wall* Obstacle4 = CreateActor<Wall>(GameRenderOrder::Map);
		Obstacle4->SetMove({ 799,221 });
		Obstacle4->GetBodyCollision()->SetScale({ 34, 102 });

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
		door->SetMove({ 488,220 }); //544 //16
		door->SetLock(true);

		

		Thorn* thorn = CreateActor<Thorn>(GameRenderOrder::Cursor);
		thorn->SetMove({ 595,323 });

		Thorn* thorn2 = CreateActor<Thorn>(GameRenderOrder::Cursor);
		thorn2->SetMove({ 629,323 });

		Thorn* thorn3 = CreateActor<Thorn>(GameRenderOrder::Cursor);
		thorn3->SetMove({ 697,323 });

		Thorn* thorn4 = CreateActor<Thorn>(GameRenderOrder::Cursor);
		thorn4->SetMove({ 765,323 });

		Thorn* thorn5 = CreateActor<Thorn>(GameRenderOrder::Cursor);
		thorn5->SetMove({ 833,323 });

		Thorn* thorn6 = CreateActor<Thorn>(GameRenderOrder::Cursor);
		thorn6->SetMove({ 867,323 });

		Thorn* thorn7 = CreateActor<Thorn>(GameRenderOrder::Cursor);
		thorn7->SetMove({ 900,323 });

		Thorn* thorn8 = CreateActor<Thorn>(GameRenderOrder::Cursor);
		thorn8->SetMove({ 934,323 });

		Thorn* thorn9 = CreateActor<Thorn>(GameRenderOrder::Cursor);
		thorn9->SetMove({ 968,323 });
		
	}
	//몬스터
	{
		BossMonster* boss = CreateActor<BossMonster>(GameRenderOrder::Cursor);
		boss->SetMove({ 908,260 }); 
		boss->SetInfloat({ 391,238 });
		boss->SetInfloat2({ 908,260 });

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

void Stage1_BossLevel::Update(float _DeltaTime)
{
	Thorn::SetInfloat({ 391,238 });

	if (true == GetDoor)
	{
		SetGetDoor(false);
		SetGetKey(false);
		GameEngineCore::GetInst()->ChangeLevel("Stage2_1Level");
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
		float ddd = BotElse;
		SetCameraMove(-GetCameraScale());
		screenSizex = GameEngineWindow::GetScreenSize().x;
		screenSizey = GameEngineWindow::GetScreenSize().y;
		float a = screenWidth / 2 - 640.0f;
		float b = screenHeight / 2 - 360.0f;
		GameEngineWindow::SettingWindowPos({ a + GetCameraPos().x, b + GetCameraPos().y });
	}
}

void Stage1_BossLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	//BGMPlayer.Stop();
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Wizard.mp3");
	BGMPlayer.Volume(0.1f);
	GameEngineWindow::SettingWindowSize({ 260,260 });
	GameEngineWindow::SettingWindowPos({ 391,238 });
	screenSizey = GameEngineWindow::GetScreenSize().y;
	SetCameraPos({ Mario->GetPos().x,Mario->GetPos().y });
	SetCameraScale({ 130, 130 });
	SetCameraMove(-GetCameraScale());
	//모니터 크기 절반에 내 스크린 사이즈 절반 만큼 빼서 크기 조정
	GameEngineWindow::WindowExpand();
}

void Stage1_BossLevel::CameraRectUpdate(float _DeltaTime)
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