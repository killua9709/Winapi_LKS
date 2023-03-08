#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 게임플레이에 나오는 벽들 player나 moster에 작용하는 충돌체와 디버그모드에서 보이는 흰색 사각형 렌더를 가진다.
// 기능1. 좌상단 점과 가로 세로 크기만 알면 충돌체와 사각형 렌더를 가진다.
class Wall : public GameEngineActor
{
public:
	// constrcuter destructer
	Wall();
	~Wall();

	// delete Function
	Wall(const Wall& _Other) = delete;
	Wall(Wall&& _Other) noexcept = delete;
	Wall& operator=(const Wall& _Other) = delete;
	Wall& operator=(Wall&& _Other) noexcept = delete;

	
	void Settingdcheck(bool _check)
	{
		dcheck = _check;
	}

	bool GetStateFix()
	{
		return StateFix;
	}

	void SettingStateFix(bool _check)
	{
		StateFix = _check;
	}

protected:
	void Start() override;
	void Render(float _Time) override;	//렌더에 충돌체 크기만큼의 벽모습 생성하자

private:
	bool dcheck = false;
	bool StateFix = false;
};

