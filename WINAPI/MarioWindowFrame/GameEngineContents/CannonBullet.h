#pragma once

// Ό³Έν :
class CannonBullet
{
public:
	// constrcuter destructer
	CannonBullet();
	~CannonBullet();

	// delete Function
	CannonBullet(const CannonBullet& _Other) = delete;
	CannonBullet(CannonBullet&& _Other) noexcept = delete;
	CannonBullet& operator=(const CannonBullet& _Other) = delete;
	CannonBullet& operator=(CannonBullet&& _Other) noexcept = delete;

protected:

private:

};

