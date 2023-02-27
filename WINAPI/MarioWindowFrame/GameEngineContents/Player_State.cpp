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


// FSM 내가 어떤일을 할때 이동하면서 가만히 있을수 없다.
void Player::IdleStart()
{
	DirCheck("Idle");
}
void Player::IdleUpdate(float _DeltaTime)
{
	//만약 땅과 닿아 있는 상태에서
	if (true == IsGround() && (GameEngineInput::IsPress("UpMove")))
	{
		ChangeState(PlayerState::JUMP);
	}

	//만약 오른쪽하고 왼쪽이 둘다 눌린다면
	bool both = (true == GameEngineInput::IsPress("LeftMove")) && (true == GameEngineInput::IsPress("RightMove"));

	if (both)
	{
		return; // 보통 스테이트를 체인지하면 아래 코드를 실행되면 
	}
	else if ((false == both) && ((true == GameEngineInput::IsPress("LeftMove")) || (true == GameEngineInput::IsPress("RightMove"))))
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
void Player::MoveUpdate(float _DeltaTime)
{
	//둘다 안눌리거나 둘다 눌리면 아이들 상태로 돌아간다
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

	//왼쪽버튼 눌릴시
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		SetMove(float4::Left * MoveSpeed * _DeltaTime);
	}
	//오른쪽버튼 눌릴시
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
	//만약 땅과 닿았다면...

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
