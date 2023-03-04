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

// FSM 내가 어떤일을 할때 이동하면서 가만히 있을수 없다.
void Player::IdleStart()
{
	CheckPos();
	DirCheck("Idle");
}
void Player::IdleUpdate(float _DeltaTime)
{
	//만약 땅에 닿아 있지 않는 상태라면
	if (false == IsGround())
	{
		ChangeState(PlayerState::Fall);
		return;
	}

	//만약 땅과 닿아 있는 상태에서
	if (true == IsGround())
	{
		if (GameEngineInput::IsDown("UpMove"))
		{
			ChangeState(PlayerState::JUMP);
			return;
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

	//움직이는 도중 점프를 할때
	if (true == IsGround() && (GameEngineInput::IsDown("UpMove")))
	{
		ChangeState(PlayerState::JUMP);
		return;
	}

	//왼쪽버튼 눌릴시
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		DirString = "Left_";
		if (false == IsLeftWall())
		{
			SetMove(float4::Left * MoveSpeed * _DeltaTime);
		}
	}
	//오른쪽버튼 눌릴시
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
	//점프관련 변수 초기화
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

	//점프파워카운트가 지정해둔 점프파워맥스보다 작다면 위로 이동시킨다.
	if (jumppowercount < JumpPowerMax)
	{
		SetMove(float4::Up * JumpPower * _DeltaTime);

		//점프파워를 점프파워 카운트에 더한다 // 어느정도까지 계속 점프가 되야 하기 때문에
		jumppowercount += JumpPower * _DeltaTime;

		if (true == GameEngineInput::IsPress("UpMove"))
		{
			jumptime += _DeltaTime;
		}

		if (true == GameEngineInput::IsPress("UpMove") && jumptime > 0.12f)
		{
			JumpPowerMax = 80.0f;
		}

		//왼쪽버튼 눌릴시
		if (true == GameEngineInput::IsPress("LeftMove"))
		{
			DirString = "Left_";
			if (false == IsLeftWall())
			{
				SetMove(float4::Left * MoveSpeed * _DeltaTime);
			}
		}
		//오른쪽버튼 눌릴시
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

	//왼쪽버튼 눌릴시
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		DirString = "Left_";
		if (false == IsLeftWall())
		{
			SetMove(float4::Left * MoveSpeed * _DeltaTime);
		}
	}
	//오른쪽버튼 눌릴시
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
	//벽을 잡고 있는 중에 다시 윗키를 누르면
	if (true == GameEngineInput::IsDown("UpMove"))
	{
		ChangeState(PlayerState::LeftWallJumping);
		return;
	}

	//오른쪽키 누르면 이동
	if (true == GameEngineInput::IsPress("RightMove"))
	{
		SetMove(float4::Right * MoveSpeed * _DeltaTime);
	}

	//점프력이 남아있으면 
	if (jumppowercount < JumpPowerMax)
	{
		//왼쪽 충돌체랑 벽이 닿지 않으면 jump로 변환
		if (false == IsLeftWall())
		{
			StateValue = PlayerState::JUMP;
			UpdateState(_DeltaTime);
			return;
		}

		SetMove(float4::Up * JumpPower * _DeltaTime);

		//점프파워를 점프파워 카운트에 더한다 // 어느정도까지 계속 점프가 되야 하기 때문에
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
		//왼쪽 충돌체랑 벽이 닿지 않으면 fall로 변환
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

	//땅에 닿았다면
	if (true == IsGround())
	{
		//점프관련 초기화
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
	//벽을 잡고 있는 중에 다시 윗키를 누르면
	if (true == GameEngineInput::IsDown("UpMove"))
	{
		ChangeState(PlayerState::RightWallJumping);
		return;
	}

	//왼쪽키 누르면 이동
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		SetMove(float4::Left * MoveSpeed * _DeltaTime);
	}

	//점프력이 남아있으면 
	if (jumppowercount < JumpPowerMax)
	{
		//왼쪽 충돌체랑 벽이 닿지 않으면 jump로 변환
		if (false == IsRightWall())
		{
			StateValue = PlayerState::JUMP;
			UpdateState(_DeltaTime);
			return;
		}
		SetMove(float4::Up * JumpPower * _DeltaTime);

		//점프파워를 점프파워 카운트에 더한다 // 어느정도까지 계속 점프가 되야 하기 때문에
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
		//왼쪽 충돌체랑 벽이 닿지 않으면 Fall로 변환
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

	//땅에 닿았다면
	if (true == IsGround())
	{
		//점프관련 초기화
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


