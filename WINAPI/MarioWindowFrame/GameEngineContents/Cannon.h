#pragma once

// Ό³Έν :
class Cannon
{
public:
	// constrcuter destructer
	Cannon();
	~Cannon();

	// delete Function
	Cannon(const Cannon& _Other) = delete;
	Cannon(Cannon&& _Other) noexcept = delete;
	Cannon& operator=(const Cannon& _Other) = delete;
	Cannon& operator=(Cannon&& _Other) noexcept = delete;

protected:

private:

};

