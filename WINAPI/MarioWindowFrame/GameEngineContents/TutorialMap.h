#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class TutorialMap : public GameEngineActor
{
public:
	static TutorialMap* MainMap;


public:
	// constrcuter destructer
	TutorialMap();
	~TutorialMap();

	// delete Function
	TutorialMap(const TutorialMap& _Other) = delete;
	TutorialMap(TutorialMap&& _Other) noexcept = delete;
	TutorialMap& operator=(const TutorialMap& _Other) = delete;
	TutorialMap& operator=(TutorialMap&& _Other) noexcept = delete;

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
	GameEngineRender* TutorialMapRender0 = NULL;
	GameEngineRender* TutorialMapRender1 = NULL;
};

