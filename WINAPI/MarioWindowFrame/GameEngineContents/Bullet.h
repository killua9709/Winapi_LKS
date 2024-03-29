#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>



// ���� :
class Bullet : public GameEngineActor
{
public:
	// constrcuter destructer
	Bullet();
	~Bullet();

	// delete Function
	Bullet(const Bullet& _Other) = delete;
	Bullet(Bullet&& _Other) noexcept = delete;
	Bullet& operator=(const Bullet& _Other) = delete;
	Bullet& operator=(Bullet&& _Other) noexcept = delete;

	void SetFisrt(bool _first)
	{
		first = _first;
	}

	GameEngineRender* GetAnimationRender()
	{
		return AnimationRender;
	}

	void Fire();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	GameEngineSoundPlayer GetSoundPlayer;
	GameEngineRender* AnimationRender = nullptr;
	bool first = false;
	float4 targetpos = float4::Zero;
	float4 Move = float4::Zero;
};

