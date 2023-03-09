#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

// ���� :
class Thorn : public GameEngineActor
{
public:
	// constrcuter destructer
	Thorn();
	~Thorn();

	// delete Function
	Thorn(const Thorn& _Other) = delete;
	Thorn(Thorn&& _Other) noexcept = delete;
	Thorn& operator=(const Thorn& _Other) = delete;
	Thorn& operator=(Thorn&& _Other) noexcept = delete;

	void SetInfloat(float4 _change)
	{
		Infloat = _change;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineSoundPlayer GetSoundPlayer;
	float4 Infloat = float4::Zero;
};

