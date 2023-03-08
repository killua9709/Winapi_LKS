#pragma once
#include "STLevel.h"
#include <GameEngineCore/GameEngineResources.h>

// Ό³Έν :
class Player;
class Scroll;
class Bullet;
class Wall;
class Stage1_1Level : public STLevel
{
public:
	// constrcuter destructer
	Stage1_1Level();
	~Stage1_1Level();

	// delete Function
	Stage1_1Level(const Stage1_1Level& _Other) = delete;
	Stage1_1Level(Stage1_1Level&& _Other) noexcept = delete;
	Stage1_1Level& operator=(const Stage1_1Level& _Other) = delete;
	Stage1_1Level& operator=(Stage1_1Level&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override {}
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;


private:
	void SoundLoad();
	void ImageLoad();
	void CameraRectUpdate();

	Wall* Left = nullptr;
	Wall* Right = nullptr;
	Wall* Top = nullptr;
	Wall* Bot = nullptr;

	float LeftElse =0 ;
	float RightElse=0;
	float TopElse=0;
	float BotElse=0;

	Player* Mario = nullptr;
	Scroll* scroll = nullptr;
	bool Fix = false;
};

