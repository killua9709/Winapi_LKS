#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class Stage1_2Map : public GameEngineActor
{
public:
	static Stage1_2Map* MainMap;


public:
	// constrcuter destructer
	Stage1_2Map();
	~Stage1_2Map();

	// delete Function
	Stage1_2Map(const Stage1_2Map& _Other) = delete;
	Stage1_2Map(Stage1_2Map&& _Other) noexcept = delete;
	Stage1_2Map& operator=(const Stage1_2Map& _Other) = delete;
	Stage1_2Map& operator=(Stage1_2Map&& _Other) noexcept = delete;

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

