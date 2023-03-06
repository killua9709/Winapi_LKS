#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Stage1_1Map : public GameEngineActor
{
public:
	static Stage1_1Map* MainMap;


public:
	// constrcuter destructer
	Stage1_1Map();
	~Stage1_1Map();

	// delete Function
	Stage1_1Map(const Stage1_1Map& _Other) = delete;
	Stage1_1Map(Stage1_1Map&& _Other) noexcept = delete;
	Stage1_1Map& operator=(const Stage1_1Map& _Other) = delete;
	Stage1_1Map& operator=(Stage1_1Map&& _Other) noexcept = delete;

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

