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
class BossMonster;
class Monster;
class Stage2_BossLevel : public STLevel
{
public:
	// constrcuter destructer
	Stage2_BossLevel();
	~Stage2_BossLevel();

	// delete Function
	Stage2_BossLevel(const Stage2_BossLevel& _Other) = delete;
	Stage2_BossLevel(Stage2_BossLevel&& _Other) noexcept = delete;
	Stage2_BossLevel& operator=(const Stage2_BossLevel& _Other) = delete;
	Stage2_BossLevel& operator=(Stage2_BossLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override {}
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;


private:
	void Initialization();
	void SoundLoad();
	void ImageLoad();

	Wall* Top = nullptr;

	float LeftElse = 0;
	float RightElse = 0;
	float TopElse = 0;
	float BotElse = 0;
	float screeny = 720;

	MouseObject* Mouse = nullptr;
	Player* Mario = nullptr;
	Scroll* scroll = nullptr;
	bool Fix = false;
	Door* door = nullptr;

	bool aa = false;
	bool bb = false;
	bool cc = false;
	bool dd = false;

	BossMonster* boss = nullptr;
	Monster* monster = nullptr;
	Monster* monster2 = nullptr;

};

