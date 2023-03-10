#pragma once
#include "STLevel.h"
#include <GameEngineCore/GameEngineResources.h>

// Ό³Έν :
class Player;
class Scroll;
class Door;
class Last_danceLevel : public STLevel
{
public:
	// constrcuter destructer
	Last_danceLevel();
	~Last_danceLevel();

	// delete Function
	Last_danceLevel(const Last_danceLevel& _Other) = delete;
	Last_danceLevel(Last_danceLevel&& _Other) noexcept = delete;
	Last_danceLevel& operator=(const Last_danceLevel& _Other) = delete;
	Last_danceLevel& operator=(Last_danceLevel&& _Other) noexcept = delete;



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
	Door* door = nullptr;
	bool Fix = false;

};

