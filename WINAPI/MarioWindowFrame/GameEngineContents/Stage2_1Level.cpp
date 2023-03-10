#include "Stage2_1Level.h"

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
#include "Stage2_1Map.h"
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
#include "Thorn.h"
#include "Wall2.h"


Stage2_1Level::Stage2_1Level()
{

}

Stage2_1Level::~Stage2_1Level()
{

}

void Stage2_1Level::SoundLoad()
{
	
}
void Stage2_1Level::ImageLoad()
{
	GameEngineWindow::SettingWindowSize({ 1280,960 });

	// 상대경로 탐색
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Play");

	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Stage2_1Map.bmp"));
		Image->Cut(1, 1);
	}
	
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Wall2.bmp"));
		Image->Cut(1, 1);
	}
	
}



void Stage2_1Level::Loading()
{
	ImageLoad();
	SoundLoad();

	//마우스
	{
		Mouse = CreateActor<MouseObject>();
	}
	//맵
	{
		Stage2_1Map* Actor = CreateActor<Stage2_1Map>();
	}
	//플레이어
	{
		Mario = CreateActor<Player>(GameRenderOrder::Player);
		Mario->SetMove({ 448,572 });
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
		length2->SetMove({ 391, 214 });
		length2->GetBodyCollision()->SetScale({ 34, 476 });

		Wall* length3 = CreateActor<Wall>(GameRenderOrder::Map);
		length3->SetMove({ 1003, 350 });
		length3->GetBodyCollision()->SetScale({ 34, 714 });


		//장애물
		Wall* Obstacle2 = CreateActor<Wall>(GameRenderOrder::Map);
		Obstacle2->SetMove({ 357,544 });
		Obstacle2->GetBodyCollision()->SetScale({ 102, 68 });

		Wall* Obstacle3 = CreateActor<Wall>(GameRenderOrder::Map);
		Obstacle3->SetMove({ 459,612 });
		Obstacle3->GetBodyCollision()->SetScale({ 102, 68 });

		Wall* Obstacle4 = CreateActor<Wall>(GameRenderOrder::Map);
		Obstacle4->SetMove({ 527,629 });
		Obstacle4->GetBodyCollision()->SetScale({ 34, 34 });

		Wall* Obstacle = CreateActor<Wall>(GameRenderOrder::Map);
		Obstacle->SetMove({ 680,595 });
		Obstacle->GetBodyCollision()->SetScale({ 272, 34 });

		Wall* Obstacle5 = CreateActor<Wall>(GameRenderOrder::Map);
		Obstacle5->SetMove({ 714,663 });
		Obstacle5->GetBodyCollision()->SetScale({ 272, 34 });

		Wall* Obstacle6 = CreateActor<Wall>(GameRenderOrder::Cursor);
		Obstacle6->SetMove({ 833,629 });
		Obstacle6->GetBodyCollision()->SetScale({ 34, 34 });

		Wall* Obstacle7 = CreateActor<Wall>(GameRenderOrder::Cursor);
		Obstacle7->SetMove({ 918,612 });
		Obstacle7->GetBodyCollision()->SetScale({ 136, 68 });

		Wall* Obstacle8 = CreateActor<Wall>(GameRenderOrder::Cursor);
		Obstacle8->SetMove({ 935,544 });
		Obstacle8->GetBodyCollision()->SetScale({ 102, 68 });


		Wall2* wall = CreateActor<Wall2>(GameRenderOrder::Map);
		wall->SetMove({ 391,493 });

		Wall2* wall2 = CreateActor<Wall2>(GameRenderOrder::Map);
		wall2->SetMove({ 595,629 });

		Wall2* wall3 = CreateActor<Wall2>(GameRenderOrder::Map);
		wall3->SetMove({ 629,629 });

		Wall2* wall4 = CreateActor<Wall2>(GameRenderOrder::Map);
		wall4->SetMove({ 663,629 });

		Wall2* wall5 = CreateActor<Wall2>(GameRenderOrder::Map);
		wall5->SetMove({ 697,629 });

		Wall2* wall6 = CreateActor<Wall2>(GameRenderOrder::Map);
		wall6->SetMove({ 731,629 });

		Wall2* wall7 = CreateActor<Wall2>(GameRenderOrder::Map);
		wall7->SetMove({ 765,629 });

		Wall2* wall8 = CreateActor<Wall2>(GameRenderOrder::Map);
		wall8->SetMove({ 799,629 });


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
		door->SetMove({ 341,494 }); //544 //16

		Thorn::SetInfloat({ 448,572 });

		Thorn* thorn = CreateActor<Thorn>(GameRenderOrder::Cursor);
		thorn->SetMove({ 527,595 });

		Thorn* thorn2 = CreateActor<Thorn>(GameRenderOrder::Cursor);
		thorn2->SetMove({ 833,595 });
	}
	//몬스터
	{
		Cannon* cannon1 = CreateActor<Cannon>(GameRenderOrder::Monster);
		cannon1->SetMove({ 561,663 });
		cannon1->SetState(CannonState::Left2);

		Cannon* cannon2 = CreateActor<Cannon>(GameRenderOrder::Monster);
		cannon2->SetMove({ 561,629 });
		cannon2->SetState(CannonState::Left2);

		Cannon* cannon3 = CreateActor<Cannon>(GameRenderOrder::Monster);
		cannon3->SetMove({ 950,495 });
		cannon3->SetState(CannonState::Right3);
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

void Stage2_1Level::Update(float _DeltaTime)
{

	if (true == GetDoor)
	{
		SetGetDoor(false);
		GameEngineCore::GetInst()->ChangeLevel("Stage2_2Level");
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

void Stage2_1Level::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Thorn::SetInfloat({ 448,572 });
	CannonBullet::SetInfloat({ 372,544 });
	BGMPlayer.Stop();
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("stage2backgroundsound.mp3");
	BGMPlayer.Volume(0.1f);
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

void Stage2_1Level::CameraRectUpdate(float _DeltaTime)
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