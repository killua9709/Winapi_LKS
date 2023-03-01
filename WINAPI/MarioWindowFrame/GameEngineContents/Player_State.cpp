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
	default:
		break;
	}

}

void Player::ChangeUpdateState(PlayerState _State, float _DeltaTime)
{
	StateValue = _State;

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
	case PlayerState::Attack:
		//AttackUpdate(_DeltaTime);
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
	default:
		break;
	}

}

// FSM ���� ����� �Ҷ� �̵��ϸ鼭 ������ ������ ����.
void Player::IdleStart()
{
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
		if (GameEngineInput::IsPress("UpMove"))
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
	if (true == IsGround() && (GameEngineInput::IsPress("UpMove")))
	{
		ChangeState(PlayerState::JUMP);
		return;
	}

	//���ʹ�ư ������
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		if (false == IsLeftWall())
		{
			SetMove(float4::Left * MoveSpeed * _DeltaTime);
		}
	}
	//�����ʹ�ư ������
	else if (true == GameEngineInput::IsPress("RightMove"))
	{
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
			if (false == IsLeftWall())
			{
				SetMove(float4::Left * MoveSpeed * _DeltaTime);
			}
			else
			{
				ChangeState(PlayerState::LeftWallJump);
				return;
			}
		}
		//�����ʹ�ư ������
		else if (true == GameEngineInput::IsPress("RightMove"))
		{
			if (false == IsRightWall())
			{
				SetMove(float4::Right * MoveSpeed * _DeltaTime);
			}
			else
			{
				ChangeState(PlayerState::RightWallJump);
				return;
			}
		}
	}
	else
	{
		ChangeState(PlayerState::Fall);
		
		return;
	}

	if (true == IsUpWall())
	{
		ChangeState(PlayerState::IDLE);
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
	Gravity(_DeltaTime);

	if (true == IsGround())
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

	//���ʹ�ư ������
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		if (false == IsLeftWall())
		{
			SetMove(float4::Left * MoveSpeed * _DeltaTime);
		}
	}
	//�����ʹ�ư ������
	else if (true == GameEngineInput::IsPress("RightMove"))
	{
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
	//���� �浹ü�� ���� ���� ������ jump�� ��ȯ
	if (false == IsLeftWall())
	{
		StateValue = PlayerState::JUMP;
		UpdateState(_DeltaTime);
		return;
	}

	//���� ��� �ִ� �߿� �ٽ� ��Ű�� ������
	if (true == GameEngineInput::IsDown("UpMove"))
	{

	}

	//�������� ���������� 
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
	}
	else
	{
		if (true == GameEngineInput::IsDown("LeftMove"))
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
		ChangeState(PlayerState::IDLE);
		return;
	}

	DirCheck("WallJump");
}

void Player::LeftWallJumpEnd()
{
	//�������� �ʱ�ȭ
	jumppowercount = 0;
	JumpPowerMax = 50.0f;
	jumptime = 0;
	jumpsoundchange = !jumpsoundchange;
}

void Player::RightWallJumpStart()
{
	DirCheck("WallJump");
}

void Player::RightWallJumpUpdate(float _DeltaTime)
{
	//���� �浹ü�� ���� ���� ������ jump�� ��ȯ
	if (false == IsRightWall())
	{
		StateValue = PlayerState::JUMP;
		UpdateState(_DeltaTime);
		return;
	}

	//���� ��� �ִ� �߿� �ٽ� ��Ű�� ������
	if (true == GameEngineInput::IsDown("UpMove"))
	{

	}

	//�������� ���������� 
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
	}
	else
	{
		if (true == GameEngineInput::IsDown("RightMove"))
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
		ChangeState(PlayerState::IDLE);
		return;
	}

	DirCheck("WallJump");
}

void Player::RightWallJumpEnd()
{
	//�������� �ʱ�ȭ
	jumppowercount = 0;
	JumpPowerMax = 50.0f;
	jumptime = 0;
	jumpsoundchange = !jumpsoundchange;
}


