#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

// Ό³Έν :
class Scroll : public GameEngineActor
{
public:
	// constrcuter destructer
	Scroll();
	~Scroll();

	// delete Function
	Scroll(const Scroll& _Other) = delete;
	Scroll(Scroll&& _Other) noexcept = delete;
	Scroll& operator=(const Scroll& _Other) = delete;
	Scroll& operator=(Scroll&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineSoundPlayer GetSoundPlayer;
};

