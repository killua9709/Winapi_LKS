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


#include "ContentsEnums.h"
#include "ContentsValue.h"

#include "TutorialMap.h"
#include "STLevel.h"

Player* Player::MainPlayer;

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	//�÷��̾� Ű �Է�
	if (false == GameEngineInput::IsKey("LeftMove"))
	{
		GameEngineInput::CreateKey("LeftMove", 'A');
		GameEngineInput::CreateKey("RightMove", 'D');
		GameEngineInput::CreateKey("DownMove", 'S');
		GameEngineInput::CreateKey("UpMove", 'W');

		GameEngineInput::CreateKey("FreeMoveSwitch", '1');
		GameEngineInput::CreateKey("StageClear", '2');
	}

	//�÷��̾� ���� �ִϸ��̼�
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

	//�÷��̾� �浹ü ����
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

	//�÷��̾� ����
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Sound");
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("jump1.wav"));
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("jump2.wav"));
	}
	ChangeState(PlayerState::IDLE);
}



//�Ȱ��� �ϳ��� �÷��̾ ����
void Player::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainPlayer = this;
}

bool FreeMove = false;

//���� �ൿ ����
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

//�÷��̾� ������Ʈ
void Player::Update(float _DeltaTime)
{
	//���� ������ ��� �ִ� �浹ü�� �÷��̾��� �浹ü ó��
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

	if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(GameCollisionOrder::Object), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
	{
		GameEngineWindow::SettingWindowSize({ 1280,720 });
	}


	//��������
	if (true == FreeMoveState(_DeltaTime))
	{
		return;
	}

	//�������� Ŭ����
	if (GameEngineInput::IsDown("StageClear"))
	{
		TutorialMap::MainMap->StageClearOn();
	}


	//���º�ȭ �� �̵�
	UpdateState(_DeltaTime);
}

//���¿� ���� �ִϸ��̼� ��ȭ
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

//�÷��̾� ����
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


		std::string dir = "direction : ";
		dir += DirString;

		std::string dir2 = "playerstate : ";
		dir2 += std::to_string( (int)StateValue);

		std::string dir3 = "posx : ";
		dir3 += std::to_string((int)GetPos().x);

		std::string dir4 = "posy : ";
		dir4 += std::to_string((int)GetPos().y);


		GameEngineLevel::DebugTextPush(dir);
		GameEngineLevel::DebugTextPush(dir2);
		GameEngineLevel::DebugTextPush(dir3);
		GameEngineLevel::DebugTextPush(dir4);

		/*std::string Text = "���";
		SetBkMode(DoubleDC, TRANSPARENT);
		TextOut(DoubleDC, 0, 0, Text.c_str(), Text.size());*/

		// ������.
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

//���� �ִ� �� üũ
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
	//���� �Ʒ��浹ü�� ���� �浹�ϰ� ������ ����÷��ش�.
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

