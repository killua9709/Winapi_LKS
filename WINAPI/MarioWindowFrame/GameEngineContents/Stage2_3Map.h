#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Stage2_3Map : public GameEngineActor
{
public:
	static Stage2_3Map* MainMap;


public:
	// constrcuter destructer
	Stage2_3Map();
	~Stage2_3Map();

	// delete Function
	Stage2_3Map(const Stage2_3Map& _Other) = delete;
	Stage2_3Map(Stage2_3Map&& _Other) noexcept = delete;
	Stage2_3Map& operator=(const Stage2_3Map& _Other) = delete;
	Stage2_3Map& operator=(Stage2_3Map&& _Other) noexcept = delete;

	inline void StageClearOn()
	{
		IsStageClear = true;
	}

	void SetScroll(bool _state)
	{
		GetScroll = _state;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool Fix = false;
	bool IsStageClear = false;
	bool GetScroll = false;
	GameEngineRender* BackGroundRender = NULL;
	GameEngineRender* MapRender = NULL;
};

