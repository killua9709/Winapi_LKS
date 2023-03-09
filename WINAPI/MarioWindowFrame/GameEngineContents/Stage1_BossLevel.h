#pragma once

// Ό³Έν :
class Stage1_BossLevel
{
public:
	// constrcuter destructer
	Stage1_BossLevel();
	~Stage1_BossLevel();

	// delete Function
	Stage1_BossLevel(const Stage1_BossLevel& _Other) = delete;
	Stage1_BossLevel(Stage1_BossLevel&& _Other) noexcept = delete;
	Stage1_BossLevel& operator=(const Stage1_BossLevel& _Other) = delete;
	Stage1_BossLevel& operator=(Stage1_BossLevel&& _Other) noexcept = delete;

protected:

private:

};

