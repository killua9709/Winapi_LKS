#include "Player.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

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
	//���� ���� ��� �ִ� ���¿���
	if (true == IsGround() && (GameEngineInput::IsPress("UpMove")))
	{
		ChangeState(PlayerState::JUMP);
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
	}

	//���� ���� ��� ���� ���� ���¶��
	//

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

	if (true == IsGround() && (GameEngineInput::IsPress("UpMove")))
	{
		ChangeState(PlayerState::JUMP);
	}

	//���ʹ�ư ������
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		SetMove(float4::Left * MoveSpeed * _DeltaTime);
	}
	//�����ʹ�ư ������
	else if (true == GameEngineInput::IsPress("RightMove"))
	{
		SetMove(float4::Right * MoveSpeed * _DeltaTime);
	}


	DirCheck("Move");
}
void Player::MoveEnd()
{

}

void Player::JumpStart()
{
	DirCheck("Jump");

}
float jumppowercount = 0;

void Player::JumpUpdate(float _DeltaTime)
{
	if (jumppowercount < JumpPowerMax)
	{
		SetMove(float4::Up * JumpPower * _DeltaTime);
		jumppowercount += JumpPower;
	}
	else
	{
		ChangeState(PlayerState::IDLE);
		jumppowercount = 0;
	}



	/*if (true == IsGround())
	{
		ChangeState(PlayerState::IDLE);
	}*/
	//���� ���� ��Ҵٸ�...

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

}

void Player::FallEnd()
{

}
