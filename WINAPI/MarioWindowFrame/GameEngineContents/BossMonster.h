#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineResources.h>



// Ό³Έν :

class BossMonster : public GameEngineActor
{
public:
	// constrcuter destructer
	BossMonster();
	~BossMonster();

	// delete Function
	BossMonster(const BossMonster& _Other) = delete;
	BossMonster(BossMonster&& _Other) noexcept = delete;
	BossMonster& operator=(const BossMonster& _Other) = delete;
	BossMonster& operator=(BossMonster&& _Other) noexcept = delete;

	void SetInfloat(float4 _change)
	{
		Infloat = _change;
	}

	void SetInfloat2(float4 _change)
	{
		Infloat2 = _change;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	//void Render(float _Time) override;

private:
	GameEngineRender* AnimationRender = nullptr;
	float4 Infloat = float4::Zero;
	float4 Infloat2 = float4::Zero;
	bool isdeath = false;

	GameEngineSoundPlayer GetSoundPlayer;



};

