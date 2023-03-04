#include "TutorialLevel.h"

#include "Structs.h"

// ������Ʈ ������ ���� ����
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindow.h>


// ���� ���� ����� �����
#include "Player.h"
#include "Monster.h"
#include "TutorialMap.h"
#include "ContentsEnums.h"
#include "ContentsValue.h"
#include "MouseObject.h"
#include "Wall.h"
#include "Scroll.h"


TutorialLevel::TutorialLevel()
{
	
}

TutorialLevel::~TutorialLevel()
{
}

void TutorialLevel::SoundLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");

	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("stage1backgroundsound.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("getkey.wav"));
	
}
void TutorialLevel::ImageLoad()
{
	GameEngineWindow::SettingWindowSize({ 1280,960 });
	// ����� Ž��
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Play");

	// �̹��� �ε�
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_Mario.BMP"));
		Image->Cut(5, 4);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_Mario.BMP"));
		Image->Cut(5, 4);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("���۸�.BMP"));
		Image->Cut(1, 1);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("���.BMP"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("scroll.bmp"));
	}
}

void TutorialLevel::Loading()
{
	SoundLoad();
	ImageLoad();

	SetCameraScale({1000, 100});

	//���콺
	{
		CreateActor<MouseObject>();
	}
	//��
	{
		TutorialMap* Actor = CreateActor<TutorialMap>();
	}
	//�÷��̾�
	{
		Mario = CreateActor<Player>(GameRenderOrder::Player);
		Mario->SetMove({GameEngineWindow::GetScreenSize().x/2,GameEngineWindow::GetScreenSize().y / 2-400});
	}
	//����
	{
		srand(static_cast<unsigned int>(time(nullptr)));
		for (size_t i = 0; i < 0; i++)
		{
			Monster* Actor = CreateActor<Monster>(GameRenderOrder::Monster);
			Actor->SetMove(
				float4(static_cast<float>(rand() % GameEngineWindow::GetScreenSize().ix()), static_cast<float>(rand() % GameEngineWindow::GetScreenSize().iy()))
			);
		}
	}
	//��
	{
		//���κ�
		Wall* Wight = CreateActor<Wall>(GameRenderOrder::Map);
		Wight->SetMove({ 646,119 });
		Wight->GetBodyCollision()->SetScale({ 612, 34 });

		Wall* Wight2 = CreateActor<Wall>(GameRenderOrder::Map);
		Wight2->SetMove({ 578,289 });
		Wight2->GetBodyCollision()->SetScale({ 612, 34 });

		Wall* Wight3 = CreateActor<Wall>(GameRenderOrder::Map);
		Wight3->SetMove({ 646,527 });
		Wight3->GetBodyCollision()->SetScale({ 612, 34 });

		Wall* Wight4 = CreateActor<Wall>(GameRenderOrder::Map);
		Wight4->SetMove({ 612,697 });
		Wight4->GetBodyCollision()->SetScale({ 680, 34 });
		

		//���κ�
		Wall* length = CreateActor<Wall>(GameRenderOrder::Map);
		length->SetMove({ 255, 350 });
		length->GetBodyCollision()->SetScale({ 34, 714 });

		Wall* length2 = CreateActor<Wall>(GameRenderOrder::Map);
		length2->SetMove({ 969, 350 });
		length2->GetBodyCollision()->SetScale({ 34, 714 });

		
		

		//��ֹ�
		Wall* Obstacle = CreateActor<Wall>(GameRenderOrder::Map);
		Obstacle->SetMove({ GameEngineWindow::GetScreenSize().x / 2 - 181,GameEngineWindow::GetScreenSize().y / 2 - 240 });
		Obstacle->GetBodyCollision()->SetScale({ 34, 70 });

		Wall* Obstacle2 = CreateActor<Wall>(GameRenderOrder::Map);
		Obstacle2->SetMove({ GameEngineWindow::GetScreenSize().x / 2 - 45,GameEngineWindow::GetScreenSize().y / 2 - 224 });
		Obstacle2->GetBodyCollision()->SetScale({ 34, 34 });

		Wall* Obstacle3 = CreateActor<Wall>(GameRenderOrder::Map);
		Obstacle3->SetMove({ 731,238 });
		Obstacle3->GetBodyCollision()->SetScale({ 34, 68 });

		Wall* Obstacle4 = CreateActor<Wall>(GameRenderOrder::Map);
		Obstacle4->SetMove({ 867,442 });
		Obstacle4->GetBodyCollision()->SetScale({ 34, 136 });

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

		//���� �� Ÿ�� ����
		/*Wall* Actor7 = CreateActor<Wall>(GameRenderOrder::Map);
		Actor7->SetMove({ 600, 350 });
		Actor7->GetBodyCollision()->SetScale({ 34, 714 });

		Wall* Actor8 = CreateActor<Wall>(GameRenderOrder::Map);
		Actor8->SetMove({ 700, 350 });
		Actor8->GetBodyCollision()->SetScale({ 34, 714 });*/

	}
	//������Ʈ
	{
		scroll = CreateActor<Scroll>(GameRenderOrder::Cursor);
		scroll->SetMove({ GameEngineWindow::GetScreenSize().x / 2 - 45,655 });
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

void TutorialLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("DebugRenderSwitch"))
	{
		 BGMPlayer.Stop();

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
		IsScreenOut();
		screenSizex = GameEngineWindow::GetScreenSize().x;
		screenSizey = GameEngineWindow::GetScreenSize().y;
		float a = screenWidth / 2 - 640.0f;
		float b = screenHeight / 2 - 360.0f;
		GameEngineWindow::SettingWindowPos({ a + GetCameraPos().x, b + GetCameraPos().y });
	}
	else
	{
		GameEngineWindow::SettingWindowSize({ 1280,720 });
		GameEngineWindow::SettingWindowPos({(float)screenWidth/2 - 640, (float)screenHeight/2-360 });
		SetCameraPos({ 0,0 });
	}
	

}

void TutorialLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("stage1backgroundsound.mp3");
	BGMPlayer.Volume(0.1f);
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