#pragma once
#include "STLevel.h"
#include <GameEngineCore/GameEngineResources.h>

// Ό³Έν :
class Player;
class Scroll;
class Bullet;
class Wall;
class MouseObject;
class Door;
class Stage2_1Level : public STLevel
{
public:
	// constrcuter destructer
	Stage2_1Level();
	~Stage2_1Level();

	// delete Function
	Stage2_1Level(const Stage2_1Level& _Other) = delete;
	Stage2_1Level(Stage2_1Level&& _Other) noexcept = delete;
	Stage2_1Level& operator=(const Stage2_1Level& _Other) = delete;
	Stage2_1Level& operator=(Stage2_1Level&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override {}
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;


private:
	void SoundLoad();
	void ImageLoad();
	void CameraRectUpdate(float _DeltaTime);

	Wall* Left = nullptr;
	Wall* Right = nullptr;
	Wall* Top = nullptr;
	Wall* Bot = nullptr;

	float LeftElse = 0;
	float RightElse = 0;
	float TopElse = 0;
	float BotElse = 0;

	MouseObject* Mouse = nullptr;
	Player* Mario = nullptr;
	Scroll* scroll = nullptr;
	bool Fix = false;
	Door* door = nullptr;

	bool aa = false;
	bool bb = false;
	bool cc = false;
	bool dd = false;

};

