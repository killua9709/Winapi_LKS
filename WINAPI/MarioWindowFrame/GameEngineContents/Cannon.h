#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>
#include "CannonBullet.h"

enum CannonState
{
	Normal1,
	Left2,
	Right3
};

// ���� :
class Cannon : public GameEngineActor
{
public:
	// constrcuter destructer
	Cannon();
	~Cannon();

	// delete Function
	Cannon(const Cannon& _Other) = delete;
	Cannon(Cannon&& _Other) noexcept = delete;
	Cannon& operator=(const Cannon& _Other) = delete;
	Cannon& operator=(Cannon&& _Other) noexcept = delete;

	std::vector<CannonBullet*> GetBullets()
	{
		return Bullets;
	}

	void SetState(CannonState _state)
	{
		CurrentState = _state;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	GameEngineRender* render = nullptr;
	GameEngineSoundPlayer GetSoundPlayer;
	std::vector<CannonBullet*> Bullets;
	CannonState CurrentState = CannonState::Normal1;
	float firetime = 0;
};

