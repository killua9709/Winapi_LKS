#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

// Ό³Έν :
class Door : public GameEngineActor
{
public:
	// constrcuter destructer
	Door();
	~Door();

	// delete Function
	Door(const Door& _Other) = delete;
	Door(Door&& _Other) noexcept = delete;
	Door& operator=(const Door& _Other) = delete;
	Door& operator=(Door&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineSoundPlayer GetSoundPlayer;
};

