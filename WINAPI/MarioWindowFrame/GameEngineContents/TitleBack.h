#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

// Ό³Έν :
class TitleBack : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleBack();
	~TitleBack();
	static bool SceneClear;
	// delete Function
	TitleBack(const TitleBack& _Other) = delete;
	TitleBack(TitleBack&& _Other) noexcept = delete;
	TitleBack& operator=(const TitleBack& _Other) = delete;
	TitleBack& operator=(TitleBack&& _Other) noexcept = delete;

	static bool GetSceneClear()
	{
		return SceneClear;
	}
protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	int ScreenNumber = 0;
	
	GameEngineSoundPlayer BGMPlayer;
};

