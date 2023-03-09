#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Stage2_1Map : public GameEngineActor
{
public:
	static Stage2_1Map* MainMap;


public:
	// constrcuter destructer
	Stage2_1Map();
	~Stage2_1Map();

	// delete Function
	Stage2_1Map(const Stage2_1Map& _Other) = delete;
	Stage2_1Map(Stage2_1Map&& _Other) noexcept = delete;
	Stage2_1Map& operator=(const Stage2_1Map& _Other) = delete;
	Stage2_1Map& operator=(Stage2_1Map&& _Other) noexcept = delete;

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

