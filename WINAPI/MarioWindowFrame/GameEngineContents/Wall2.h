#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Wall2 : public GameEngineActor
{
public:
	// constrcuter destructer
	Wall2();
	~Wall2();

	// delete Function
	Wall2(const Wall2& _Other) = delete;
	Wall2(Wall2&& _Other) noexcept = delete;
	Wall2& operator=(const Wall2& _Other) = delete;
	Wall2& operator=(Wall2&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

};

