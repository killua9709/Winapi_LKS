#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>
#include <GameEngineCore/GameEngineResources.h>


enum class PlayerState
{
	IDLE,
	MOVE,
	JUMP,
	Attack,
	Fall,
	LeftWallJump,
	RightWallJump, 
	LeftWallJumping,
	RightWallJumping,
};

// 설명 :
class Player : public GameEngineActor
{
public:
	static Player* MainPlayer;

	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	GameEngineCollision* GetBodyCollision()
	{
		return BodyCollision;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;


private:

	// std::vector<WeaponInfo> MyWeapon;

	NumberRenderObject TestNumber;

	float AccTime = 0.0f;
	int StartFrame = 0;
	float MoveSpeed = 200.0f;
	float GravityPower = 200.0f;

	//점프관련
	float JumpPower = 300.0f;	//점프력
	float JumpPowerMax = 50.0f; //최대 누적 점프
	float jumppowercount = 0;	//현재 누적 점프
	float jumptime = 0;			//2단 점프 변화 시간
	bool jumpsoundchange = false;


	std::string DirString = "Right_";
	PlayerState StateValue = PlayerState::IDLE;
	float4 MoveDir = float4::Zero;

	GameEngineRender* AnimationRender = nullptr;

	/////플레이어 충돌체
	GameEngineCollision* BodyCollision = nullptr;
	GameEngineCollision* LeftCollision = nullptr;
	GameEngineCollision* RightCollision = nullptr;
	GameEngineCollision* UpCollision = nullptr;
	GameEngineCollision* DownCollision = nullptr;
	//////

	GameEngineSoundPlayer JumpSoundPlayer;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;


	void DirCheck(const std::string_view& _AnimationName);

	// State
	bool FreeMoveState(float _DeltaTime);

	void ChangeState(PlayerState _State);
	void UpdateState(float _DeltaTime);
	void Gravity(float _DeltaTime);
	void SoftGravity(float _DeltaTime);

	//벽과의 충돌
	bool IsLeftWall();
	bool IsRightWall();
	bool IsUpWall();
	bool IsGround();


	// FSM 내가 어떤일을 할때 이동하면서 가만히 있을수 없다.
	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	void MoveStart();
	void MoveUpdate(float _DeltaTime);
	void MoveEnd();

	void JumpStart();
	void JumpUpdate(float _DeltaTime);
	void JumpEnd();

	void FallStart();
	void FallUpdate(float _DeltaTime);
	void FallEnd();

	void LeftWallJumpStart();
	void LeftWallJumpUpdate(float _DeltaTime);
	void LeftWallJumpEnd();

	void RightWallJumpStart();
	void RightWallJumpUpdate(float _DeltaTime);
	void RightWallJumpEnd();

	void LeftWallJumpingStart();
	void LeftWallJumpingUpdate(float _DeltaTime);
	void LeftWallJumpingEnd();

	void RightWallJumpingStart();
	void RightWallJumpingUpdate(float _DeltaTime);
	void RightWallJumpingEnd();

	
	//상태체크 이전 내 위치조정
	void CheckUp();
	void CheckGround();
	void CheckPos();
	int Value = 0;
};

