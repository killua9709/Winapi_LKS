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

	
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("stage1backgroundsound.mp3"));
	
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
		Player* Actor = CreateActor<Player>(GameRenderOrder::Player);
		Actor->SetMove({GameEngineWindow::GetScreenSize().x/2,GameEngineWindow::GetScreenSize().y / 2-400});
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
		Wall* Actor = CreateActor<Wall>(GameRenderOrder::Map);
		Actor->SetMove({ GameEngineWindow::GetScreenSize().x / 2 + 12,119 });
		Actor->GetBodyCollision()->SetScale({ 612, 34 });

		Wall* Actor2 = CreateActor<Wall>(GameRenderOrder::Map);
		Actor2->SetMove({ GameEngineWindow::GetScreenSize().x / 2 -45,GameEngineWindow::GetScreenSize().y / 2 - 224});
		Actor2->GetBodyCollision()->SetScale({ 34, 34 });

		Wall* Actor3 = CreateActor<Wall>(GameRenderOrder::Map);
		Actor3->SetMove({ GameEngineWindow::GetScreenSize().x / 2 - 181,GameEngineWindow::GetScreenSize().y / 2 - 240 });
		Actor3->GetBodyCollision()->SetScale({ 34, 70 });

		Wall* Actor4 = CreateActor<Wall>(GameRenderOrder::Map);
		Actor4->SetMove({ GameEngineWindow::GetScreenSize().x / 2 + 50,GameEngineWindow::GetScreenSize().y / 2 - 192 });
		Actor4->GetBodyCollision()->SetScale({ 1000, 35 });

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
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("stage1backgroundsound.mp3");
	BGMPlayer.Volume(0.1f);
	GameEngineWindow::SettingWindowSize({ 1280,720 });
	//GameEngineWindow::WindowExpand();
}