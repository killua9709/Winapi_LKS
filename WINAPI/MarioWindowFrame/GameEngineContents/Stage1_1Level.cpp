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
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("fireball.bmp"));
		Image->Cut(5, 2);
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
		CreateActor<MouseObject>();
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


		//������ Ʋ
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
	//������Ʈ
	{
		/*scroll = CreateActor<Scroll>(GameRenderOrder::Cursor);
		scroll->SetMove({ 629,600 });*/

		Bullet* bullet1 = CreateActor<Bullet>(GameRenderOrder::Cursor);
		bullet1->SetMove({ 629,600 });

		for (size_t i = 0; i < 6; i++)
		{
			Bullet* bullet = CreateActor<Bullet>(GameRenderOrder::Cursor);
			bullet->SetMove({Mario->GetPos().x,Mario->GetPos().y-15});
			Bullets.push_back(bullet);
			Bullets[i]->Off();
		}
	}


	if (false == GameEngineInput::IsKey("DebugRenderSwitch"))
	{
		GameEngineInput::CreateKey("DebugRenderSwitch", 'R');
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
	//�Ѿ� Ŭ���ϸ� �������ϱ�
	if ((GameEngineInput::IsDown("EnginemouseLeft")) &&
		(0 < GetMousePosToCamera().x) &&
		(GameEngineWindow::GetMousePosition().x < GameEngineWindow::GetScreenSize().x) &&
		(0 < GetMousePosToCamera().y) &&
		GameEngineWindow::GetMousePosition().y < GameEngineWindow::GetScreenSize().y)
	{
		Bullets[1]->SetPos({ Mario->GetPos().x,Mario->GetPos().y - 16 });
		Bullets[1]->On();
	}

	if ((GameEngineInput::IsPress("EnginemouseRight")) &&
		(0 < GetMousePosToCamera().x) &&
		(GameEngineWindow::GetMousePosition().x < GameEngineWindow::GetScreenSize().x) &&
		(0 < GetMousePosToCamera().y) &&
		GameEngineWindow::GetMousePosition().y < GameEngineWindow::GetScreenSize().y)
	{
		Bullets[1]->Off();
		Bullets[1]->SetFisrt(false);
		Bullets[1]->GetAnimationRender()->ChangeAnimation("Running");
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

	if (true == Getisdebug())
	{
		GameEngineWindow::SettingWindowSize({ 1280,720 });
		GameEngineWindow::SettingWindowPos({ (float)screenWidth / 2 - 640, (float)screenHeight / 2 - 360 });
		SetCameraPos({ 0,0 });
	}
	else
	{
		GameEngineWindow::SettingWindowSize({ 260,260 });
		SetCameraPos({ Mario->GetPos().x,Mario->GetPos().y });
		SetCameraMove(-GetCameraScale());
		IsScreenOut();
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
	//����� ũ�� ���ݿ� �� ��ũ�� ������ ���� ��ŭ ���� ũ�� ����
	GameEngineWindow::SettingWindowPos({ screenWidth / 2 - (screenSizex / 2) ,screenHeight / 2 - (screenSizey / 2) });
	//GameEngineWindow::WindowExpand();
}