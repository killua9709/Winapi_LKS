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

// ���� :
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

	//��������
	float JumpPower = 300.0f;	//������
	float JumpPowerMax = 50.0f; //�ִ� ���� ����
	float jumppowercount = 0;	//���� ���� ����
	float jumptime = 0;			//2�� ���� ��ȭ �ð�
	bool jumpsoundchange = false;


	std::string DirString = "Right_";
	PlayerState StateValue = PlayerState::IDLE;
	float4 MoveDir = float4::Zero;

	GameEngineRender* AnimationRender = nullptr;

	/////�÷��̾� �浹ü
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

	//������ �浹
	bool IsLeftWall();
	bool IsRightWall();
	bool IsUpWall();
	bool IsGround();


	// FSM ���� ����� �Ҷ� �̵��ϸ鼭 ������ ������ ����.
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

	
	//����üũ ���� �� ��ġ����
	void CheckUp();
	void CheckGround();
	void CheckPos();
	int Value = 0;
};

