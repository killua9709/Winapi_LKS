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


// FSM 내가 어떤일을 할때 이동하면서 가만히 있을수 없다.
void Player::IdleStart() 
{
	DirCheck("Idle");
}
void Player::IdleUpdate(float _Time) 
{
	//만약 땅과 닿아 있는 상태에서
	if (GameEngineInput::IsPress("UpMove"))
	{
		ChangeState(PlayerState::JUMP);
	}
	//만약 오른쪽하고 왼쪽이 둘다 눌린다면
	bool both = (true == GameEngineInput::IsPress("LeftMove")) && (true == GameEngineInput::IsPress("RightMove"));

	if (both)
	{
		return; // 보통 스테이트를 체인지하면 아래 코드를 실행되면 
	}
	else if((false == both) && ((true == GameEngineInput::IsPress("LeftMove")) || (true == GameEngineInput::IsPress("RightMove"))))
	{	//둘다 눌리지 않았고 왼쪽 또는 오른쪽을 누른다면 

		ChangeState(PlayerState::MOVE);
	}

	//만약 땅과 닿아 있지 않은 상태라면
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
	//만약 땅과 닿았다면...
}
void Player::JumpEnd() 
{

}
