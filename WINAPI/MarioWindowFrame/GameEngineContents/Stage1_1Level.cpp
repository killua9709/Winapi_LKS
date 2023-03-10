#include "Stage1_1Level.h"

#include "Structs.h"

// ������Ʈ ������ ���� ����
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCore.h>



// ���� ���� ����� �����
#include "Player.h"
#include "Stage1_1Map.h"
#include "ContentsEnums.h"
#include "ContentsValue.h"
#include "MouseObject.h"
#include "Wall.h"
#include "Bullet.h"
#include "Scroll.h"
#include "Bullet.h"
#include "MouseObject.h"
#include "Door.h"


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

	// ����� Ž��
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

	//���콺
	{
		Mouse = CreateActor<MouseObject>();
	}
	//��
	{
		Stage1_1Map* Actor = CreateActor<Stage1_1Map>();
	}
	//�÷��̾�
	{
		Mario = CreateActor<Player>(GameRenderOrder::Player);
		Mario->SetMove({ 372,544 });
	}
	//��
	{
		//���κ�
		Wall* Wight4 = CreateActor<Wall>(GameRenderOrder::Map);
		Wight4->SetMove({ 612,697 });
		Wight4->GetBodyCollision()->SetScale({ 1200, 34 });


		//���κ�
		Wall* length = CreateActor<Wall>(GameRenderOrder::Map);
		length->SetMove({ 289, 350 });
		length->GetBodyCollision()->SetScale({ 34, 714 });

		Wall* length2 = CreateActor<Wall>(GameRenderOrder::Map);
		length2->SetMove({ 1003, 350 });
		length2->GetBodyCollision()->SetScale({ 34, 714 });




		//��ֹ�
		Wall* Obstacle = CreateActor<Wall>(GameRenderOrder::Map);
		Obstacle->SetMove({ 374,612 });
		Obstacle->GetBodyCollision()->SetScale({ 136, 136 });

		Wall* Obstacle2 = CreateActor<Wall>(GameRenderOrder::Map);
		Obstacle2->SetMove({ 510,646 });
		Obstacle2->GetBodyCollision()->SetScale({ 136,68 });

		Wall* Obstacle3 = CreateActor<Wall>(GameRenderOrder::Map);
		Obstacle3->SetMove({ 918,612 });
		Obstacle3->GetBodyCollision()->SetScale({ 136,136 });


		//{{������ Ʋ
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
	//������Ʈ
	{
		door = CreateActor<Door>(GameRenderOrder::Cursor);
		door->SetMove({ 941,528 }); //544 //16
		
	}


	if (false == GameEngineInput::IsKey("DebugRenderSwitch"))
	{
		GameEngineInput::CreateKey("DebugRenderSwitch", 'M');
	}


	if (false == GameEngineInput::IsKey("CameraLeftMove"))
	{
		// VK ���Ĺ�� ���ڸ� ������ Ű�� ǥ���ϴµ� ���� �ִ�. 
		GameEngineInput::CreateKey("CameraLeftMove", VK_LEFT);
		GameEngineInput::CreateKey("CameraRightMove", VK_RIGHT);
		GameEngineInput::CreateKey("CameraDownMove", VK_DOWN);
		GameEngineInput::CreateKey("CameraUpMove", VK_UP);
	}
}

void Stage1_1Level::Update(float _DeltaTime)
{
	if (true == GetDoor)
	{
		SetGetDoor(false);
		GameEngineCore::GetInst()->ChangeLevel("Stage1_2Level");
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
	
	//{{ī�޶� ��Ʈ
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
	GameEngineWindow::SettingWindowPos({ 502,674 });
	screenSizex = GameEngineWindow::GetScreenSize().x;
	screenSizey = GameEngineWindow::GetScreenSize().y;
	SetCameraPos({ Mario->GetPos().x,Mario->GetPos().y });
	SetCameraScale({ 130, 130 });
	SetCameraMove(-GetCameraScale());
	//����� ũ�� ���ݿ� �� ��ũ�� ������ ���� ��ŭ ���� ũ�� ����
	GameEngineWindow::WindowExpand();
}


void Stage1_1Level::CameraRectUpdate(float _DeltaTime)
{
	std::vector<GameEngineCollision*> Collision;
	if (false == Left->GetBodyCollision()->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Bullet), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
	{
		Left->Settingdcheck(false);
		Left->SetPos({ Mario->GetPos().x - GetCameraScale().x,Mario->GetPos().y + GetCameraScale().y});
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
	
	std::vector<GameEngineCollision*> Collision3;
	if (false == Top->GetBodyCollision()->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Bullet), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision3))
	{
		Top->Settingdcheck(false);
		Top->SetPos({ Mario->GetPos().x + GetCameraScale().x,Mario->GetPos().y - GetCameraScale().y});
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

			Top->SetMove({ 0,100*_DeltaTime });
			cc = false;
		}
		Top->Settingdcheck(true);
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