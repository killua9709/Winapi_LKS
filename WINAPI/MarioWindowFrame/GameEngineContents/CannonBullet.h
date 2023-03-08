#pragma once
#include <GameEngineCore/GameEngineActor.h>


// Ό³Έν :
class CannonBullet : public GameEngineActor
{
public:
	// constrcuter destructer
	CannonBullet();
	~CannonBullet();

	// delete Function
	CannonBullet(const CannonBullet& _Other) = delete;
	CannonBullet(CannonBullet&& _Other) noexcept = delete;
	CannonBullet& operator=(const CannonBullet& _Other) = delete;
	CannonBullet& operator=(CannonBullet&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	GameEngineRender* AnimationRender = nullptr;

};

