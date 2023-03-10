#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Stage2_BossMap : public GameEngineActor
{
public:
	static Stage2_BossMap* MainMap;


public:
	// constrcuter destructer
	Stage2_BossMap();
	~Stage2_BossMap();

	// delete Function
	Stage2_BossMap(const Stage2_BossMap& _Other) = delete;
	Stage2_BossMap(Stage2_BossMap&& _Other) noexcept = delete;
	Stage2_BossMap& operator=(const Stage2_BossMap& _Other) = delete;
	Stage2_BossMap& operator=(Stage2_BossMap&& _Other) noexcept = delete;

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

