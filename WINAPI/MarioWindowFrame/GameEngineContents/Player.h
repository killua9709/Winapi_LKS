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
	Fall
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

	void SetCollimage(GameEngineImage* _collImage)
	{
		Collimage = _collImage;
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
	float JumpPower = 300.0f;
	float JumpPowerMax = 50.0f; //8000 //16000
	float GravityPower = 200.0f;

	//점프관련
	float jumppowercount = 0;
	float jumptime = 0;
	bool jumpsoundchange = false;

	//미래위치
	float4 CheckPos = { float4::Zero };

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

	GameEngineImage* Collimage = nullptr;
	GameEngineSoundPlayer JumpSoundPlayer;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;


	void DirCheck(const std::string_view& _AnimationName);

	// State
	bool FreeMoveState(float _DeltaTime);

	void ChangeState(PlayerState _State);
	void ChangeUpdateState(PlayerState _State, float _DeltaTime);
	void UpdateState(float _DeltaTime);
	void Gravity(float _DeltaTime);


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

	bool IsGround();

	int Value = 0;
};

