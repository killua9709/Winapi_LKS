#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineWindow.h>

// Ό³Έν :
class STLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	STLevel();
	~STLevel();

	// delete Function
	STLevel(const STLevel& _Other) = delete;
	STLevel(STLevel&& _Other) noexcept = delete;
	STLevel& operator=(const STLevel& _Other) = delete;
	STLevel& operator=(STLevel&& _Other) noexcept = delete;

public:
	inline float4 GetCameraScale() 
	{
		return CameraScale;
	}

	inline void SetCameraScale(float4 _Scale)
	{
		CameraScale = _Scale;
	}

	void IsScreenOut();

protected:
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	float screenSizex = GameEngineWindow::GetScreenSize().x;
	float screenSizey = GameEngineWindow::GetScreenSize().y;
private:

	float4 CameraScale = float4::Zero;
};

