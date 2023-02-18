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
	default:
		break;
	}

}

void Player::ChangeUpdateState(PlayerState _State, float _Time)
{
	StateValue = _State;

	switch (StateValue)
	{
	case PlayerState::IDLE:
		IdleUpdate(_Time);
		break;
	case PlayerState::MOVE:
		MoveUpdate(_Time);
		break;
	case PlayerState::JUMP:
		JumpUpdate(_Time);
		break;
	case PlayerState::Attack:
		//AttackUpdate(_Time);
		break;
	default:
		break;
	}
}

void Player::UpdateState(float _Time)
{
	switch (StateValue)
	{
	case PlayerState::IDLE:
		IdleUpdate(_Time);
		break;
	case PlayerState::MOVE:
		MoveUpdate(_Time);
		break;
	case PlayerState::JUMP:
		JumpUpdate(_Time);
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
void Player::IdleUpdate(float _Time) 
{
	//���� ���� ��� �ִ� ���¿���
	if (GameEngineInput::IsPress("UpMove"))
	{
		ChangeState(PlayerState::JUMP);
	}
	//���� �������ϰ� ������ �Ѵ� �����ٸ�
	bool both = (true == GameEngineInput::IsPress("LeftMove")) && (true == GameEngineInput::IsPress("RightMove"));

	if (both)
	{
		return; // ���� ������Ʈ�� ü�����ϸ� �Ʒ� �ڵ带 ����Ǹ� 
	}
	else if((false == both) && ((true == GameEngineInput::IsPress("LeftMove")) || (true == GameEngineInput::IsPress("RightMove"))))
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
void Player::MoveUpdate(float _Time) 
{
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

	// float4 MoveDir = float4::Zero;
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		SetMove(float4::Left * MoveSpeed);
	} 
	else if (true == GameEngineInput::IsPress("RightMove"))
	{
		SetMove(float4::Right * MoveSpeed);
	}


	DirCheck("Move");
}
void Player::MoveEnd() 
{

}

void Player::JumpStart()
{
	DirCheck("Jump");
	SetMove(float4::Up * JumpPower);
}
void Player::JumpUpdate(float _Time)
{
	DirCheck("Jump");
	//���� ���� ��Ҵٸ�...
}
void Player::JumpEnd() 
{

}
