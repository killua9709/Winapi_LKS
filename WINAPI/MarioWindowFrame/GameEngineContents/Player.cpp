#include "Player.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineCore/GameEngineLevel.h>



#include "ContentsEnums.h"
#include "ContentsValue.h"

#include "TutorialMap.h"
#include "STLevel.h"
#include "Bullet.h"

Player* Player::MainPlayer;

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	//플레이어 키 입력
	if (false == GameEngineInput::IsKey("LeftMove"))
	{
		GameEngineInput::CreateKey("LeftMove", 'A');
		GameEngineInput::CreateKey("RightMove", 'D');
		GameEngineInput::CreateKey("DownMove", 'S');
		GameEngineInput::CreateKey("UpMove", 'W');
		GameEngineInput::CreateKey("Reload", 'R');

		GameEngineInput::CreateKey("FreeMoveSwitch", '1');
		GameEngineInput::CreateKey("StageClear", '2');
	}

	//플레이어 랜더 애니메이션
	{
		AnimationRender = CreateRender(GameRenderOrder::Player);
		AnimationRender->SetScale({ 80, 80 });

		AnimationRender->CreateAnimation({ .AnimationName = "Right_Idle",  .ImageName = "Right_Mario.bmp", .Start = 0, .End = 0 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Move",  .ImageName = "Right_Mario.bmp", .Start = 1, .End = 3, .InterTime = 0.06f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Jump",  .ImageName = "Right_Mario.bmp", .Start = 4, .End = 4 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_WallJump",  .ImageName = "Right_Mario.bmp", .Start = 17, .End = 17 });


		AnimationRender->CreateAnimation({ .AnimationName = "Left_Idle",  .ImageName = "Left_Mario.bmp", .Start = 0, .End = 0 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Move",  .ImageName = "Left_Mario.bmp", .Start = 1, .End = 3 , .InterTime = 0.06f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Jump",  .ImageName = "Left_Mario.bmp", .Start = 4, .End = 4 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_WallJump",  .ImageName = "Left_Mario.bmp", .Start = 17, .End = 17 });
	}

	//플레이어 충돌체 생성
	{
		BodyCollision = CreateCollision(GameCollisionOrder::Player);
		BodyCollision->SetScale({ 25, 35 });
		BodyCollision->SetPosition({ 0,-17 });

		LeftCollision = CreateCollision(GameCollisionOrder::Player);
		LeftCollision->SetScale({ 2, 30 });
		LeftCollision->SetPosition({ -12,-17 });

		RightCollision = CreateCollision(GameCollisionOrder::Player);
		RightCollision->SetScale({ 2, 30 });
		RightCollision->SetPosition({ 12,-17 });

		UpCollision = CreateCollision(GameCollisionOrder::Player);
		UpCollision->SetScale({ 1, 1 });
		UpCollision->SetPosition({ 0, -36 });

		DownCollision = CreateCollision(GameCollisionOrder::Player);
		DownCollision->SetScale({ 1, 1 });
		DownCollision->SetPosition({ 0, 0 });
	}

	for (size_t i = 0; i < 6; i++)
	{
		Bullet* bullet = GetLevel()->CreateActor<Bullet>(GameRenderOrder::Cursor);
		bullet->SetMove({ GetPos().x,GetPos().y - 15 });
		Bullets.push_back(bullet);
		Bullets[i]->Off();
	}
	
	ChangeState(PlayerState::IDLE);
}



//똑같은 하나의 플레이어를 위해
void Player::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainPlayer = this;
}

bool FreeMove = false;

//자유 행동 상태
bool Player::FreeMoveState(float _DeltaTime)
{
	if (true == GameEngineInput::IsPress("FreeMoveSwitch"))
	{
		FreeMove = true;
	}

	if (true == FreeMove)
	{
		if (GameEngineInput::IsPress("LeftMove"))
		{
			SetMove(float4::Left * 1000.0f * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Left * 1000.0f * _DeltaTime);
		}
		else if (GameEngineInput::IsPress("RightMove"))
		{
			SetMove(float4::Right * 1000.0f * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Right * 1000.0f * _DeltaTime);
		}
		else if (GameEngineInput::IsPress("UpMove"))
		{
			SetMove(float4::Up * 1000.0f * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Up * 1000.0f * _DeltaTime);
		}
		else if (GameEngineInput::IsPress("DownMove"))
		{
			SetMove(float4::Down * 1000.0f * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Down * 1000.0f * _DeltaTime);
		}
	}

	if (true == FreeMove)
	{
		return true;
	}

	return false;
}

//플레이어 업데이트
void Player::Update(float _DeltaTime)
{
	//몬스터 오더를 들고 있는 충돌체와 플레이어의 충돌체 처리
	if (nullptr != BodyCollision)
	{
		std::vector<GameEngineCollision*> Collision;
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Monster), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
		{
			for (size_t i = 0; i < Collision.size(); i++)
			{
				GameEngineActor* ColActor = Collision[i]->GetActor();
				ColActor->Death();
			}
		}
	}


	//프리무브
	if (true == FreeMoveState(_DeltaTime))
	{
		return;
	}

	//스테이지 클리어
	if (GameEngineInput::IsDown("StageClear"))
	{
		TutorialMap::MainMap->StageClearOn();
	}

	//총알 클릭하면 나가게하기
	if ((GameEngineInput::IsDown("EnginemouseLeft")) &&
		(0 < GetLevel()->GetMousePosToCamera().x) &&
		(GameEngineWindow::GetMousePosition().x < GameEngineWindow::GetScreenSize().x) &&
		(0 < GetLevel()->GetMousePosToCamera().y) &&
		GameEngineWindow::GetMousePosition().y < GameEngineWindow::GetScreenSize().y)
	{
		for (size_t i = 0; i < Bullets.size(); i++)
		{
			if (false == Bullets[i]->isOn())
			{
				Bullets[i]->SetPos({ GetPos().x,GetPos().y - 16 });
				Bullets[i]->On();
				break;
			}
		}
	}

	if (true == (GameEngineInput::IsPress("Reload")) && PlayerState::IDLE == StateValue)
	{
		if (false == shaking)
		{
			GetLevel()->SetCameraMove({ 1,1 });

		}
		else
		{
			GetLevel()->SetCameraMove({ -1,-1 });
		}

		BulletTime += _DeltaTime;
		if (1 < BulletTime)
		{
			for (size_t i = 0; i < Bullets.size(); i++)
			{
				if (true == Bullets[i]->isOn())
				{
					Bullets[i]->Off();
					Bullets[i]->SetFisrt(false);
					Bullets[i]->GetAnimationRender()->ChangeAnimation("Running");
				}
			}

			return;
		}

		shaking = !shaking;
	}

	if ((GameEngineInput::IsUp("Reload")))
	{
		BulletTime = 0;
	}


	//상태변화 및 이동
	UpdateState(_DeltaTime);
}

//상태에 따른 애니메이션 변화
void Player::DirCheck(const std::string_view& _AnimationName)
{
	std::string PrevDirString = DirString;
	AnimationRender->ChangeAnimation(DirString + _AnimationName.data());

	if (GameEngineInput::IsPress("LeftMove") && (GameEngineInput::IsPress("RightMove")))
	{
		return;
	}

	if (PrevDirString != DirString)
	{
		AnimationRender->ChangeAnimation(DirString + _AnimationName.data());
	}
}

//플레이어 랜더
void Player::Render(float _DeltaTime)
{
	/*HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	float4 ActorPos = GetPos() - GetLevel()->GetCameraPos();*/

	/*Rectangle(DoubleDC,
		ActorPos.ix() - GetBodyCollision()->GetScale().hix(),
		ActorPos.iy() - GetBodyCollision()->GetScale().hiy(),
		ActorPos.ix() + GetBodyCollision()->GetScale().hix(),
		ActorPos.iy() + GetBodyCollision()->GetScale().hix()
		);*/

		//BodyCollision->DebugRender();


		/*std::string dir = "direction : ";
		dir += DirString;

		std::string dir2 = "playerstate : ";
		dir2 += std::to_string( (int)StateValue);*/

		std::string dir3 = "posx : ";
		dir3 += std::to_string((int)GetPos().x);

		std::string dir4 = "posy : ";
		dir4 += std::to_string((int)GetPos().y);
		
		/*std::string dir5 = "cameraposx : ";
		dir5 += std::to_string((int)GetLevel()->GetCameraPos().x);

		std::string dir6 = "cameraposx : ";
		dir6 += std::to_string((int)GetLevel()->GetCameraPos().y);*/

		std::string dir7 = "bullettime : ";
		dir7 += std::to_string((int)BulletTime); 

		/*GameEngineLevel::DebugTextPush(dir);
		GameEngineLevel::DebugTextPush(dir2);*/
		GameEngineLevel::DebugTextPush(dir3);
		GameEngineLevel::DebugTextPush(dir4);
		/*GameEngineLevel::DebugTextPush(dir5);
		GameEngineLevel::DebugTextPush(dir6);*/
		/*GameEngineLevel::DebugTextPush(dir7);*/

		/*std::string Text = "출력";
		SetBkMode(DoubleDC, TRANSPARENT);
		TextOut(DoubleDC, 0, 0, Text.c_str(), Text.size());*/

		// 디버깅용.
}

void Player::Gravity(float _DeltaTime)
{
	SetMove({ 0, GravityPower * _DeltaTime });
}

void Player::SoftGravity(float _DeltaTime)
{
	SetMove({ 0, GravityPower / 3 * _DeltaTime });
}

bool Player::IsLeftWall()
{
	return LeftCollision->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Wall), .TargetColType = CT_Rect, .ThisColType = CT_Rect });
}

bool Player::IsRightWall()
{
	return RightCollision->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Wall), .TargetColType = CT_Rect, .ThisColType = CT_Rect });
}

bool Player::IsUpWall()
{
	return UpCollision->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Wall), .TargetColType = CT_Rect, .ThisColType = CT_Rect });
}

//땅에 있는 지 체크
bool Player::IsGround()
{
	return (DownCollision->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Wall), .TargetColType = CT_Rect, .ThisColType = CT_Rect }));
}

void Player::CheckUp()
{
	std::vector<GameEngineCollision*> Collision;
	if (true == UpCollision->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Wall), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
	{
		for (size_t i = 0; i < Collision.size(); i++)
		{
			SetPos({ GetPos().x,Collision[i]->GetCollisionData().Bot() + 37 });
		}
	}
}

void Player::CheckGround()
{
	//만약 아래충돌체와 벽이 충돌하고 있으면 끌어올려준다.
	std::vector<GameEngineCollision*> Collision;
	if (true == DownCollision->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Wall), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
	{
		for (size_t i = 0; i < Collision.size(); i++)
		{
			SetPos({ GetPos().x,Collision[i]->GetCollisionData().Top() });
		}
	}
	
}

void Player::CheckPos()
{

	CheckGround();
	CheckUp();
}

