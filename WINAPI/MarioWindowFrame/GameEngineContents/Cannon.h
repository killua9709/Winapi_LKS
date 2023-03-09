#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>
#include "CannonBullet.h"


// Ό³Έν :
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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	GameEngineSoundPlayer GetSoundPlayer;
	std::vector<CannonBullet*> Bullets;

	float firetime = 0;
};

