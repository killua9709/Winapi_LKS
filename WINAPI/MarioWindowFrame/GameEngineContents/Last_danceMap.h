#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Last_danceMap : public GameEngineActor
{
public:
	static Last_danceMap* MainMap;


public:
	// constrcuter destructer
	Last_danceMap();
	~Last_danceMap();

	// delete Function
	Last_danceMap(const Last_danceMap& _Other) = delete;
	Last_danceMap(Last_danceMap&& _Other) noexcept = delete;
	Last_danceMap& operator=(const Last_danceMap& _Other) = delete;
	Last_danceMap& operator=(Last_danceMap&& _Other) noexcept = delete;

	inline void StageClearOn()
	{
		IsStageClear = true;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool IsStageClear = false;

	GameEngineRender* BackGroundRender = NULL;
	GameEngineRender* Last_danceMapRender0 = NULL;
	GameEngineRender* Last_danceMapRender1 = NULL;
};

