#pragma once
#include "STLevel.h"
#include <GameEngineCore/GameEngineResources.h>

// Ό³Έν :
class Player;
class Scroll;
class Tutorial2Level : public STLevel
{
public:
	// constrcuter destructer
	Tutorial2Level();
	~Tutorial2Level();

	// delete Function
	Tutorial2Level(const Tutorial2Level& _Other) = delete;
	Tutorial2Level(Tutorial2Level&& _Other) noexcept = delete;
	Tutorial2Level& operator=(const Tutorial2Level& _Other) = delete;
	Tutorial2Level& operator=(Tutorial2Level&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override {}
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;


private:

	void SoundLoad();
	void ImageLoad();
	Player* Mario = nullptr;
	Scroll* scroll = nullptr;
	bool Fix = false;
};

