#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Stage1_3Map : public GameEngineActor
{
public:
	static Stage1_3Map* MainMap;


public:
	// constrcuter destructer
	Stage1_3Map();
	~Stage1_3Map();

	// delete Function
	Stage1_3Map(const Stage1_3Map& _Other) = delete;
	Stage1_3Map(Stage1_3Map&& _Other) noexcept = delete;
	Stage1_3Map& operator=(const Stage1_3Map& _Other) = delete;
	Stage1_3Map& operator=(Stage1_3Map&& _Other) noexcept = delete;

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

