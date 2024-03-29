#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineWindow.h>

// ���� :
class GameEngineSoundPlayer;
class STLevel : public GameEngineLevel
{
public:
	static GameEngineSoundPlayer BGMPlayer;
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

	static void SetGetScroll(bool _state)
	{
		GetScroll = _state;
	}

	static void SetGetDoor(bool _state)
	{
		GetDoor = _state;
	}
	
	static void SetGetKey(bool _state)
	{
		GetKey = _state;
	}

	static bool GetGetKey()
	{
		return GetKey;
	}

	void IsScreenOut();


protected:
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	float screenSizex = GameEngineWindow::GetScreenSize().x;
	float screenSizey = GameEngineWindow::GetScreenSize().y;
	static bool GetScroll;
	static bool GetDoor;
	static bool GetKey;
private:
	
	float4 CameraScale = float4::Zero;
	
};

