#include "Stage2_BossLevel.h"

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
#include "BossMonster.h"


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

	// 상대경로 탐색
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
	//마우스
	{
		Mouse = CreateActor<MouseObject>();
	}
	//맵
	{
		Stage2_BossMap* Actor = CreateActor<Stage2_BossMap>();
	}
	//플레이어
	{
		Mario = CreateActor<Player>(GameRenderOrder::Player);
		Mario->SetMove({ 88,86 });
	}
	//벽
	{
		//가로벽
		Wall* Wight4 = CreateActor<Wall>(GameRenderOrder::Map);
		Wight4->SetMove({ 510,153 });
		Wight4->GetBodyCollision()->SetScale({ 952, 34 });

		Wall* Wight = CreateActor<Wall>(GameRenderOrder::Map);
		Wight->SetMove({ 459,119 });
		Wight->GetBodyCollision()->SetScale({ 850, 34 });

		Wall* Wight2 = CreateActor<Wall>(GameRenderOrder::Map);
		Wight2->SetMove({ 640,698 });
		Wight2->GetBodyCollision()->SetScale({ 1280, 34 });


		//세로벽
		Wall* length = CreateActor<Wall>(GameRenderOrder::Map);
		length->SetMove({ 17, 360 });
		length->GetBodyCollision()->SetScale({ 34, 720 });

		Wall* length2 = CreateActor<Wall>(GameRenderOrder::Map);
		length2->SetMove({ 1241, 360 });
		length2->GetBodyCollision()->SetScale({ 34, 720 });




		//장애물
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
			Obstacle->SetMove({ 850, 612 });
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


		////{{윈도우 틀

		Top = CreateActor<Wall>(GameRenderOrder::Map);
		Top->SetPos({ 690,0 });
		Top->GetBodyCollision()->SetScale({ 2000, 10 });
	}
	//오브젝트
	{



		Thorn* thorn = CreateActor<Thorn>(GameRenderOrder::Map);
		thorn->SetMove({ 357,119 });

		Thorn* thorn2 = CreateActor<Thorn>(GameRenderOrder::Map);
		thorn2->SetMove({ 323,119 });

		Thorn* thorn3 = CreateActor<Thorn>(GameRenderOrder::Map);
		thorn3->SetMove({ 527,119 });

		Thorn* thorn4 = CreateActor<Thorn>(GameRenderOrder::Map);
		thorn4->SetMove({ 561,119 });

		Thorn* thorn5 = CreateActor<Thorn>(GameRenderOrder::Map);
		thorn5->SetMove({ 731,119 });


		Cannon* cannon1 = CreateActor<Cannon>(GameRenderOrder::Monster);
		cannon1->SetMove({ 622,465 });
		cannon1->SetState(CannonState::Right3);


		Cannon* cannon2 = CreateActor<Cannon>(GameRenderOrder::Monster);
		cannon2->SetMove({ 49,560 });
		cannon2->SetState(CannonState::Left2);

	}
	//몬스터
	
		boss = CreateActor<BossMonster>(GameRenderOrder::Monster);
		boss->SetMove({ 1120, 620 });
		boss->SetInfloat({ 88,86 });
		boss->SetInfloat2({ 1120, 620 });

		monster = CreateActor<Monster>(GameRenderOrder::Monster);
		monster->SetMove({ 340 ,228 });
		monster->SetInfloat({ 88,86 });

		monster2 = CreateActor<Monster>(GameRenderOrder::Monster);
		monster2->SetMove({ 547, 228 });
		monster2->SetInfloat({ 88,86 });
	


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

void Stage2_BossLevel::Update(float _DeltaTime)
{

	if (true == GetKey)
	{
		SetGetDoor(false);
		SetGetKey(false);
		GameEngineCore::GetInst()->ChangeLevel("Last_danceLevel");
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
	
	float b = _DeltaTime * 10;
	Top->SetMove(float4::Down * _DeltaTime * 10);
	screeny -= b;
	GameEngineWindow::SettingWindowSize({ 1280,screeny });
	SetCameraPos({ 0,Top->GetBodyCollision()->GetCollisionData().Bot() });
	GameEngineWindow::SettingWindowPos({ screenWidth / 2 - (screenSizex / 2) ,screenHeight / 2 - (screenSizey / 2) + (720 - screeny)});
}

void Stage2_BossLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	CannonBullet::SetInfloat({ 88,86 });
	Thorn::SetInfloat({ 88,86 });
	BGMPlayer.Stop();
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Wizard.mp3");
	BGMPlayer.Volume(0.1f);
	GameEngineWindow::SettingWindowSize({ 1280,720 });
	GameEngineWindow::SettingWindowPos({ screenWidth / 2 - (screenSizex / 2) ,screenHeight / 2 - (screenSizey / 2) });
	//GameEngineWindow::WindowExpand();
}

void Stage2_BossLevel::Initialization()
{
	Mario->SetPos({ 88,86 });
	Top->SetPos({ 690,0 });
	boss->SetMove({ 1120, 620 });
	monster->SetMove({ 340 ,228 });
	monster2->SetMove({ 547, 228 });
}

