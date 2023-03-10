#include "Stage2_BossLevel.h"

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
#include "Stage2_BossMap.h"
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
#include "Wall2.h"


Stage2_BossLevel::Stage2_BossLevel()
{

}

Stage2_BossLevel::~Stage2_BossLevel()
{

}

void Stage2_BossLevel::SoundLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");

}
void Stage2_BossLevel::ImageLoad()
{
	GameEngineWindow::SettingWindowSize({ 1280,960 });

	// ����� Ž��
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Play");

	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Stage2_BossMap.bmp"));
		Image->Cut(1, 1);
	}
}



void Stage2_BossLevel::Loading()
{
	ImageLoad();
	//���콺
	{
		Mouse = CreateActor<MouseObject>();
	}
	//��
	{
		Stage2_BossMap* Actor = CreateActor<Stage2_BossMap>();
	}
	//�÷��̾�
	{
		Mario = CreateActor<Player>(GameRenderOrder::Player);
		Mario->SetMove({ 88,86 });
	}
	//��
	{
		//���κ�
		Wall* Wight4 = CreateActor<Wall>(GameRenderOrder::Map);
		Wight4->SetMove({ 510,153 });
		Wight4->GetBodyCollision()->SetScale({ 952, 34 });

		Wall* Wight = CreateActor<Wall>(GameRenderOrder::Map);
		Wight->SetMove({ 459,119 });
		Wight->GetBodyCollision()->SetScale({ 850, 34 });

		Wall* Wight2 = CreateActor<Wall>(GameRenderOrder::Map);
		Wight2->SetMove({ 640,698 });
		Wight2->GetBodyCollision()->SetScale({ 1280, 34 });


		//���κ�
		Wall* length = CreateActor<Wall>(GameRenderOrder::Map);
		length->SetMove({ 17, 360 });
		length->GetBodyCollision()->SetScale({ 34, 720 });

		Wall* length2 = CreateActor<Wall>(GameRenderOrder::Map);
		length2->SetMove({ 1241, 360 });
		length2->GetBodyCollision()->SetScale({ 34, 720 });




		//��ֹ�
		{
			Wall* Obstacle = CreateActor<Wall>(GameRenderOrder::Map);
			Obstacle->SetMove({ 646,204 });
			Obstacle->GetBodyCollision()->SetScale({ 68, 68 });
		}

		{
			Wall* Obstacle = CreateActor<Wall>(GameRenderOrder::Map);
			Obstacle->SetMove({ 442,204 });
			Obstacle->GetBodyCollision()->SetScale({ 68, 68 });
		}

		{
			Wall* Obstacle = CreateActor<Wall>(GameRenderOrder::Map);
			Obstacle->SetMove({ 544,272 });
			Obstacle->GetBodyCollision()->SetScale({ 68, 68 });
		}

		{
			Wall* Obstacle = CreateActor<Wall>(GameRenderOrder::Map);
			Obstacle->SetMove({ 340,272 });
			Obstacle->GetBodyCollision()->SetScale({ 68, 68 });
		}

		{
			Wall* Obstacle = CreateActor<Wall>(GameRenderOrder::Map);
			Obstacle->SetMove({ 442,340 });
			Obstacle->GetBodyCollision()->SetScale({ 612, 68 });
		}

		{
			Wall* Obstacle = CreateActor<Wall>(GameRenderOrder::Map);
			Obstacle->SetMove({ 697,459 });
			Obstacle->GetBodyCollision()->SetScale({ 102, 306 });
		}

		{
			Wall* Obstacle = CreateActor<Wall>(GameRenderOrder::Map);
			Obstacle->SetMove({ 952,442 });
			Obstacle->GetBodyCollision()->SetScale({ 612, 68 });
		}

		{
			Wall* Obstacle = CreateActor<Wall>(GameRenderOrder::Map);
			Obstacle->SetMove({ 850,289 });
			Obstacle->GetBodyCollision()->SetScale({ 68, 34 });
		}

		{
			Wall* Obstacle = CreateActor<Wall>(GameRenderOrder::Map);
			Obstacle->SetMove({ 1020,289 });
			Obstacle->GetBodyCollision()->SetScale({ 68, 34 });
		}

		{
			Wall* Obstacle = CreateActor<Wall>(GameRenderOrder::Map);
			Obstacle->SetMove({ 1190,289 });
			Obstacle->GetBodyCollision()->SetScale({ 68, 34 });
		}

		{
			Wall* Obstacle = CreateActor<Wall>(GameRenderOrder::Map);
			Obstacle->SetMove({ 850, 612});
			Obstacle->GetBodyCollision()->SetScale({ 68, 136 });
		}

		{
			Wall* Obstacle = CreateActor<Wall>(GameRenderOrder::Map);
			Obstacle->SetMove({ 238,493 });
			Obstacle->GetBodyCollision()->SetScale({ 408, 34 });
		}

		{
			Wall* Obstacle = CreateActor<Wall>(GameRenderOrder::Map);
			Obstacle->SetMove({ 510,595 });
			Obstacle->GetBodyCollision()->SetScale({ 272, 34 });
		}
				

		////{{������ Ʋ
		//Left = CreateActor<Wall>(GameRenderOrder::Map);
		//Left->SetPos({ Mario->GetPos().x - GetCameraScale().x,Mario->GetPos().y + GetCameraScale().y });
		//Left->GetBodyCollision()->SetScale({ 10, 2000 });

		//Right = CreateActor<Wall>(GameRenderOrder::Map);
		//Right->SetPos({ Mario->GetPos().x + GetCameraScale().x,Mario->GetPos().y + GetCameraScale().y });
		//Right->GetBodyCollision()->SetScale({ 10, 2000 });

		//Top = CreateActor<Wall>(GameRenderOrder::Map);
		//Top->SetPos({ Mario->GetPos().x + GetCameraScale().x,Mario->GetPos().y - GetCameraScale().y });
		//Top->GetBodyCollision()->SetScale({ 2000, 10 });

		//Bot = CreateActor<Wall>(GameRenderOrder::Map);
		//Bot->SetPos({ Mario->GetPos().x + GetCameraScale().x,Mario->GetPos().y + GetCameraScale().y });
		//Bot->GetBodyCollision()->SetScale({ 2000, 10 });
		////}}
	}
	//������Ʈ
	{

		CannonBullet::SetInfloat({ 932,187 });

		/*Cannon* cannon1 = CreateActor<Cannon>(GameRenderOrder::Monster);
		cannon1->SetMove({ 799,125 });
		cannon1->SetDelayTime(0.8);*/

	}
	//����
	{

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

void Stage2_BossLevel::Update(float _DeltaTime)
{

	if (true == GetDoor)
	{
		SetGetDoor(false);
		SetGetKey(false);
		GameEngineCore::GetInst()->ChangeLevel("Stage2_BossLevel");
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


	/*if (true == Getisdebug())
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
	}*/
}

void Stage2_BossLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	/*BGMPlayer.Stop();
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Wizard.mp3");
	BGMPlayer.Volume(0.1f);*/
	GameEngineWindow::SettingWindowSize({ 1280,720 });
	/*screenSizex = GameEngineWindow::GetScreenSize().x;
	screenSizey = GameEngineWindow::GetScreenSize().y;
	SetCameraPos({ Mario->GetPos().x,Mario->GetPos().y });
	SetCameraScale({ 130, 130 });
	SetCameraMove(-GetCameraScale());*/
	//����� ũ�� ���ݿ� �� ��ũ�� ������ ���� ��ŭ ���� ũ�� ����
	GameEngineWindow::SettingWindowPos({ screenWidth / 2 - (screenSizex / 2) ,screenHeight / 2 - (screenSizey / 2) });
	//GameEngineWindow::WindowExpand();
}

