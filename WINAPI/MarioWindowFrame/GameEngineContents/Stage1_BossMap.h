#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Stage1_BossMap : public GameEngineActor
{
public:
	static Stage1_BossMap* MainMap;


public:
	// constrcuter destructer
	Stage1_BossMap();
	~Stage1_BossMap();

	// delete Function
	Stage1_BossMap(const Stage1_BossMap& _Other) = delete;
	Stage1_BossMap(Stage1_BossMap&& _Other) noexcept = delete;
	Stage1_BossMap& operator=(const Stage1_BossMap& _Other) = delete;
	Stage1_BossMap& operator=(Stage1_BossMap&& _Other) noexcept = delete;

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

