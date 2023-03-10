#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineResources.h>


// Ό³Έν :
class Monster : public GameEngineActor
{
public:
	static float4 Infloat;
	static float4 Infloat2;
	// constrcuter destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

	static void SetInfloat(float4 _change)
	{
		Infloat = _change;
	}
	static void SetInfloat2(float4 _change)
	{
		Infloat2 = _change;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	//void Render(float _Time) override;

private:
	GameEngineRender* AnimationRender = nullptr;
	GameEngineSoundPlayer GetSoundPlayer;

};

