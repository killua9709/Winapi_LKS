#include "Player.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsEnums.h"


// State
void Player::ChangeState(PlayerState _State)
{
	PlayerState NextState = _State;
	PlayerState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case PlayerState::IDLE:
		IdleStart();
		break;
	case PlayerState::MOVE:
		MoveStart();
		break;
	case PlayerState::JUMP:
		JumpStart();
		break;
	case PlayerState::Fall:
		FallStart();
		break;
	case PlayerState::LeftWallJump:
		LeftWallJumpStart();
		break;
	case PlayerState::RightWallJump:
		RightWallJumpStart();
		break;
	case PlayerState::LeftWallJumping:
		LeftWallJumpingStart();
		break;
	case PlayerState::RightWallJumping:
		RightWallJumpingStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case PlayerState::IDLE:
		IdleEnd();
		break;
	case PlayerState::MOVE:
		MoveEnd();
		break;
	case PlayerState::JUMP:
		JumpEnd();
		break;
	case PlayerState::Fall:
		FallEnd();
		break;
	case PlayerState::LeftWallJump:
		LeftWallJumpEnd();
		break;
	case PlayerState::RightWallJump:
		RightWallJumpEnd();
		break;
	case PlayerState::LeftWallJumping:
		LeftWallJumpingEnd();
		break;
	case PlayerState::RightWallJumping:
		RightWallJumpingEnd();
		break;
	default:
		break;
	}

}

void Player::UpdateState(float _DeltaTime)
{
	switch (StateValue)
	{
	case PlayerState::IDLE:
		IdleUpdate(_DeltaTime);
		break;
	case PlayerState::MOVE:
		MoveUpdate(_DeltaTime);
		break;
	case PlayerState::JUMP:
		JumpUpdate(_DeltaTime);
		break;
	case PlayerState::Fall:
		FallUpdate(_DeltaTime);
		break;
	case PlayerState::LeftWallJump:
		LeftWallJumpUpdate(_DeltaTime);
		break;
	case PlayerState::RightWallJump:
		RightWallJumpUpdate(_DeltaTime);
		break;
	case PlayerState::LeftWallJumping:
		LeftWallJumpingUpdate(_DeltaTime);
		break;
	case PlayerState::RightWallJumping:
		RightWallJumpingUpdate(_DeltaTime);
		break;
	default:
		break;
	}

}

// FSM ���� ����� �Ҷ� �̵��ϸ鼭 ������ ������ ����.
void Player::IdleStart()
{
	CheckPos();
	DirCheck("Idle");
}
void Player::IdleUpdate(float _DeltaTime)
{
	//���� ���� ��� ���� �ʴ� ���¶��
	if (false == IsGround())
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	//���� ���� ��� �ִ� ���¿���
	if (true == IsGround())
	{
		if (GameEngineInput::IsDown("UpMove"))
		{
			ChangeState(PlayerState::JUMP);
			return;
		}

		//���� �������ϰ� ������ �Ѵ� �����ٸ�
		bool both = (true == GameEngineInput::IsPress("LeftMove")) && (true == GameEngineInput::IsPress("RightMove"));

		if (both)
		{
			return; // ���� ������Ʈ�� ü�����ϸ� �Ʒ� �ڵ带 ����Ǹ� 
		}
		else if ((false == both) && ((true == GameEngineInput::IsPress("LeftMove")) || (true == GameEngineInput::IsPress("RightMove"))))
		{	//�Ѵ� ������ �ʾҰ� ���� �Ǵ� �������� �����ٸ� 

			ChangeState(PlayerState::MOVE);
			return;
		}
	}
}
void Player::IdleEnd()
{

}

void Player::MoveStart()
{
	DirCheck("Move");
}
void Player::MoveUpdate(float _DeltaTime)
{

	if (false == IsGround())
	{
		ChangeState(PlayerState::Fall);
		return;
	}
	//�Ѵ� �ȴ����ų� �Ѵ� ������ ���̵� ���·� ���ư���
	if (
		(false == GameEngineInput::IsPress("LeftMove") &&
			false == GameEngineInput::IsPress("RightMove")) ||
		(true == GameEngineInput::IsPress("LeftMove") &&
			true == GameEngineInput::IsPress("RightMove"))
		)
	{
		// 
		ChangeState(PlayerState::IDLE);
		return;
	}

	//�����̴� ���� ������ �Ҷ�
	if (true == IsGround() && (GameEngineInput::IsDown("UpMove")))
	{
		ChangeState(PlayerState::JUMP);
		return;
	}

	//���ʹ�ư ������
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		DirString = "Left_";
		if (false == IsLeftWall())
		{
			SetMove(float4::Left * MoveSpeed * _DeltaTime);
		}
	}
	//�����ʹ�ư ������
	else if (true == GameEngineInput::IsPress("RightMove"))
	{
		DirString = "Right_";
		if (false == IsRightWall())
		{
			SetMove(float4::Right * MoveSpeed * _DeltaTime);
		}
	}


	DirCheck("Move");
}
void Player::MoveEnd()
{

}

void Player::JumpStart()
{
	//�������� ���� �ʱ�ȭ
	jumppowercount = 0;
	JumpPowerMax = 50.0f;
	jumptime = 0;
	jumpsoundchange = !jumpsoundchange;

	DirCheck("Jump");
	if (false == jumpsoundchange)
	{
		JumpSoundPlayer = GameEngineResources::GetInst().SoundPlayToControl("jump1.wav");
		JumpSoundPlayer.LoopCount(1);
		JumpSoundPlayer.Volume(0.2f);
	}
	else
	{
		JumpSoundPlayer = GameEngineResources::GetInst().SoundPlayToControl("jump2.wav");
		JumpSoundPlayer.LoopCount(1);
		JumpSoundPlayer.Volume(0.2f);
	}
}


void Player::JumpUpdate(float _DeltaTime)
{
	CheckUp();
	if (true == IsUpWall())
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

	if (true == IsLeftWall())
	{
		DirString = "Left_";
		ChangeState(PlayerState::LeftWallJump);
		return;
	}

	if (true == IsRightWall())
	{
		DirString = "Right_";
		ChangeState(PlayerState::RightWallJump);
		return;
	}

	//�����Ŀ�ī��Ʈ�� �����ص� �����Ŀ��ƽ����� �۴ٸ� ���� �̵���Ų��.
	if (jumppowercount < JumpPowerMax)
	{
		SetMove(float4::Up * JumpPower * _DeltaTime);

		//�����Ŀ��� �����Ŀ� ī��Ʈ�� ���Ѵ� // ����������� ��� ������ �Ǿ� �ϱ� ������
		jumppowercount += JumpPower * _DeltaTime;

		if (true == GameEngineInput::IsPress("UpMove"))
		{
			jumptime += _DeltaTime;
		}

		if (true == GameEngineInput::IsPress("UpMove") && jumptime > 0.12f)
		{
			JumpPowerMax = 80.0f;
		}

		//���ʹ�ư ������
		if (true == GameEngineInput::IsPress("LeftMove"))
		{
			DirString = "Left_";
			if (false == IsLeftWall())
			{
				SetMove(float4::Left * MoveSpeed * _DeltaTime);
			}
		}
		//�����ʹ�ư ������
		else if (true == GameEngineInput::IsPress("RightMove"))
		{
			DirString = "Right_";
			if (false == IsRightWall())
			{
				SetMove(float4::Right * MoveSpeed * _DeltaTime);
			}
		}
	}
	else
	{
		ChangeState(PlayerState::Fall);
		
		return;
	}

	DirCheck("Jump");
}
void Player::JumpEnd()
{
	
}

void Player::FallStart()
{

}

void Player::FallUpdate(float _DeltaTime)
{
	CheckGround();
	if (true == IsLeftWall())
	{
		StateValue = PlayerState::LeftWallJump;
		DirString = "Left_";
		UpdateState(_DeltaTime);
		return;
	}
	
	if (true == IsRightWall())
	{
		StateValue = PlayerState::RightWallJump;
		DirString = "Right_";
		UpdateState(_DeltaTime);
		return;
	}

	Gravity(_DeltaTime);

	if (true == IsGround())
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

	//���ʹ�ư ������
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		DirString = "Left_";
		if (false == IsLeftWall())
		{
			SetMove(float4::Left * MoveSpeed * _DeltaTime);
		}
	}
	//�����ʹ�ư ������
	else if (true == GameEngineInput::IsPress("RightMove"))
	{
		DirString = "Right_";
		if (false == IsRightWall())
		{
			SetMove(float4::Right * MoveSpeed * _DeltaTime);
		}
	}

	DirCheck("Jump");

}

void Player::FallEnd()
{

}

void Player::LeftWallJumpStart()
{
	DirCheck("WallJump");
}

void Player::LeftWallJumpUpdate(float _DeltaTime)
{
	CheckUp();
	//���� ��� �ִ� �߿� �ٽ� ��Ű�� ������
	if (true == GameEngineInput::IsDown("UpMove"))
	{
		ChangeState(PlayerState::LeftWallJumping);
		return;
	}

	//������Ű ������ �̵�
	if (true == GameEngineInput::IsPress("RightMove"))
	{
		SetMove(float4::Right * MoveSpeed * _DeltaTime);
	}

	//�������� ���������� 
	if (jumppowercount < JumpPowerMax)
	{
		//���� �浹ü�� ���� ���� ������ jump�� ��ȯ
		if (false == IsLeftWall())
		{
			StateValue = PlayerState::JUMP;
			UpdateState(_DeltaTime);
			return;
		}

		SetMove(float4::Up * JumpPower * _DeltaTime);

		//�����Ŀ��� �����Ŀ� ī��Ʈ�� ���Ѵ� // ����������� ��� ������ �Ǿ� �ϱ� ������
		jumppowercount += JumpPower * _DeltaTime;

		if (true == GameEngineInput::IsPress("UpMove"))
		{
			jumptime += _DeltaTime;
		}

		if (true == GameEngineInput::IsPress("UpMove") && jumptime > 0.12f)
		{
			JumpPowerMax = 80.0f;
		}
	}
	else
	{
		//���� �浹ü�� ���� ���� ������ fall�� ��ȯ
		if (false == IsLeftWall())
		{
			StateValue = PlayerState::Fall;
			UpdateState(_DeltaTime);
			return;
		}
		if (true == GameEngineInput::IsPress("LeftMove"))
		{
			SoftGravity(_DeltaTime);
		}
		else
		{
			Gravity(_DeltaTime);
		}
	}

	//���� ��Ҵٸ�
	if (true == IsGround())
	{
		//�������� �ʱ�ȭ
		jumppowercount = 0;
		JumpPowerMax = 50.0f;
		jumptime = 0;
		ChangeState(PlayerState::IDLE);
		return;
	}

	DirCheck("WallJump");
}

void Player::LeftWallJumpEnd()
{
	
}

void Player::RightWallJumpStart()
{
	DirCheck("WallJump");
}

void Player::RightWallJumpUpdate(float _DeltaTime)
{
	CheckUp();
	//���� ��� �ִ� �߿� �ٽ� ��Ű�� ������
	if (true == GameEngineInput::IsDown("UpMove"))
	{
		ChangeState(PlayerState::RightWallJumping);
		return;
	}

	//����Ű ������ �̵�
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		SetMove(float4::Left * MoveSpeed * _DeltaTime);
	}

	//�������� ���������� 
	if (jumppowercount < JumpPowerMax)
	{
		//���� �浹ü�� ���� ���� ������ jump�� ��ȯ
		if (false == IsRightWall())
		{
			StateValue = PlayerState::JUMP;
			UpdateState(_DeltaTime);
			return;
		}
		SetMove(float4::Up * JumpPower * _DeltaTime);

		//�����Ŀ��� �����Ŀ� ī��Ʈ�� ���Ѵ� // ����������� ��� ������ �Ǿ� �ϱ� ������
		jumppowercount += JumpPower * _DeltaTime;

		if (true == GameEngineInput::IsPress("UpMove"))
		{
			jumptime += _DeltaTime;
		}

		if (true == GameEngineInput::IsPress("UpMove") && jumptime > 0.12f)
		{
			JumpPowerMax = 80.0f;
		}
	}
	else
	{
		//���� �浹ü�� ���� ���� ������ Fall�� ��ȯ
		if (false == IsRightWall())
		{
			StateValue = PlayerState::Fall;
			UpdateState(_DeltaTime);
			return;
		}

		if (true == GameEngineInput::IsPress("RightMove"))
		{
			SoftGravity(_DeltaTime);
		}
		else
		{
			Gravity(_DeltaTime);
		}
	}

	//���� ��Ҵٸ�
	if (true == IsGround())
	{
		//�������� �ʱ�ȭ
		jumppowercount = 0;
		JumpPowerMax = 50.0f;
		jumptime = 0;
		ChangeState(PlayerState::IDLE);
		return;
	}

	DirCheck("WallJump");
}

void Player::RightWallJumpEnd()
{
	
}

void Player::LeftWallJumpingStart()
{
	jumppowercount = 0;
	JumpPowerMax = 50.0f;
	jumptime = 0;
	jumpsoundchange = !jumpsoundchange;

	if (false == jumpsoundchange)
	{
		JumpSoundPlayer = GameEngineResources::GetInst().SoundPlayToControl("jump1.wav");
		JumpSoundPlayer.LoopCount(1);
		JumpSoundPlayer.Volume(0.2f);
	}
	else
	{
		JumpSoundPlayer = GameEngineResources::GetInst().SoundPlayToControl("jump2.wav");
		JumpSoundPlayer.LoopCount(1);
		JumpSoundPlayer.Volume(0.2f);
	}

	DirCheck("Jump");
}

void Player::LeftWallJumpingUpdate(float _DeltaTime)
{
	CheckUp();
	if (true == IsUpWall())
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

	if (true == IsGround())
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

	if (true == IsRightWall())
	{
		ChangeState(PlayerState::RightWallJump);
		return;
	}

	if (jumppowercount < JumpPowerMax)
	{
		DirString = "Right_";
		SetMove({ float4::Right * MoveSpeed*2 * _DeltaTime });
		SetMove({ float4::Up * JumpPower * _DeltaTime });

		jumppowercount += JumpPower * _DeltaTime;
	}
	else
	{
		if (jumptime < 0.1f)
		{
			jumptime += _DeltaTime;
			Gravity(_DeltaTime);
		}
		else
		{
			ChangeState(PlayerState::Fall);
			return;
		}
	}
	
	DirCheck("Jump");
}

void Player::LeftWallJumpingEnd()
{

}

void Player::RightWallJumpingStart()
{
	jumppowercount = 0;
	JumpPowerMax = 50.0f;
	jumptime = 0;
	jumpsoundchange = !jumpsoundchange;

	if (false == jumpsoundchange)
	{
		JumpSoundPlayer = GameEngineResources::GetInst().SoundPlayToControl("jump1.wav");
		JumpSoundPlayer.LoopCount(1);
		JumpSoundPlayer.Volume(0.2f);
	}
	else
	{
		JumpSoundPlayer = GameEngineResources::GetInst().SoundPlayToControl("jump2.wav");
		JumpSoundPlayer.LoopCount(1);
		JumpSoundPlayer.Volume(0.2f);
	}

	DirCheck("Jump");
}

void Player::RightWallJumpingUpdate(float _DeltaTime)
{
	CheckUp();
	if (true == IsUpWall())
	{
		CheckPos();
		ChangeState(PlayerState::IDLE);
		return;
	}

	if (true == IsGround())
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

	if (true == IsLeftWall())
	{
		ChangeState(PlayerState::LeftWallJump);
		return;
	}

	if (jumppowercount < JumpPowerMax)
	{
		DirString = "Left_";
		SetMove({ float4::Left * MoveSpeed * 2 * _DeltaTime });
		SetMove({ float4::Up * JumpPower * _DeltaTime });

		jumppowercount += JumpPower * _DeltaTime;
	}
	else
	{
		if (jumptime < 0.1f)
		{
			jumptime += _DeltaTime;
			Gravity(_DeltaTime);
		}
		else
		{
			ChangeState(PlayerState::Fall);
			return;
		}
	}

	DirCheck("Jump");
}

void Player::RightWallJumpingEnd()
{

}


