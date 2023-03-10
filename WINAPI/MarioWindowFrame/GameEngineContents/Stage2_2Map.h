#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Stage2_2Map : public GameEngineActor
{
public:
	static Stage2_2Map* MainMap;


public:
	// constrcuter destructer
	Stage2_2Map();
	~Stage2_2Map();

	// delete Function
	Stage2_2Map(const Stage2_2Map& _Other) = delete;
	Stage2_2Map(Stage2_2Map&& _Other) noexcept = delete;
	Stage2_2Map& operator=(const Stage2_2Map& _Other) = delete;
	Stage2_2Map& operator=(Stage2_2Map&& _Other) noexcept = delete;

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

