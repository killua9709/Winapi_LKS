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

	{
		//GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("BGMTest.mp3"));
	}

	// GameEngineResources::GetInst().SoundPlay("Appear.wav");

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
		GameEngineImage* Image2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("���.BMP"));
		GameEngineImage* Image3 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ColMap.BMP"));
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
		Player* Actor = CreateActor<Player>(BubbleRenderOrder::Player);
		Actor->SetMove({GameEngineWindow::GetScreenSize().x/2,GameEngineWindow::GetScreenSize().y / 2-190});
		Actor->SetCollimage( GameEngineResources::GetInst().ImageFind("ColMap.BMP"));	//�浹 �̹��� ����

	}
	//����
	{
		srand(static_cast<unsigned int>(time(nullptr)));
		for (size_t i = 0; i < 0; i++)
		{
			Monster* Actor = CreateActor<Monster>(BubbleRenderOrder::Monster);
			Actor->SetMove(
				float4(static_cast<float>(rand() % GameEngineWindow::GetScreenSize().ix()), static_cast<float>(rand() % GameEngineWindow::GetScreenSize().iy()))
			);
		}
	}
	//��
	{
		Wall* Actor = CreateActor<Wall>(BubbleRenderOrder::Map);
		Actor->SetMove({ GameEngineWindow::GetScreenSize().x / 2 + 50,GameEngineWindow::GetScreenSize().y / 2 - 192 });
		Actor->GetBodyCollision()->SetScale({ 25, 35 });
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
		// BGMPlayer.Stop();

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
}

void TutorialLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	//BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("BGMTest.mp3");
	//BGMPlayer.LoopCount(100);
	//// BGMPlayer.Volume(0.2f);
	GameEngineWindow::SettingWindowSize({ 1280,720 });
	GameEngineWindow::WindowExpand();
}