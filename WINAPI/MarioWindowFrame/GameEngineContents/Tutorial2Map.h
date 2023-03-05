#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Tutorial2Map : public GameEngineActor
{
public:
	static Tutorial2Map* MainMap;


public:
	// constrcuter destructer
	Tutorial2Map();
	~Tutorial2Map();

	// delete Function
	Tutorial2Map(const Tutorial2Map& _Other) = delete;
	Tutorial2Map(Tutorial2Map&& _Other) noexcept = delete;
	Tutorial2Map& operator=(const Tutorial2Map& _Other) = delete;
	Tutorial2Map& operator=(Tutorial2Map&& _Other) noexcept = delete;

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
	GameEngineRender* TutorialMapRender = NULL;
};

