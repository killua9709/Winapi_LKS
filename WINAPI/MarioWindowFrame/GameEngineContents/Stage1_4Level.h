#pragma once

// Ό³Έν :
class Stage1_4Level
{
public:
	// constrcuter destructer
	Stage1_4Level();
	~Stage1_4Level();

	// delete Function
	Stage1_4Level(const Stage1_4Level& _Other) = delete;
	Stage1_4Level(Stage1_4Level&& _Other) noexcept = delete;
	Stage1_4Level& operator=(const Stage1_4Level& _Other) = delete;
	Stage1_4Level& operator=(Stage1_4Level&& _Other) noexcept = delete;

protected:

private:

};

