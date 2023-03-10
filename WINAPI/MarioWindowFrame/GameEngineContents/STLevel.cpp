#include "STLevel.h"
#include <GameEngineCore/GameEngineResources.h>

STLevel::STLevel() 
{
}

STLevel::~STLevel() 
{
}
GameEngineSoundPlayer STLevel::BGMPlayer = nullptr;
bool STLevel::GetScroll = false;
bool STLevel::GetDoor = false;
bool STLevel::GetKey = false;

void STLevel::IsScreenOut()
{
	if (GetCameraPos().x < 0)
	{
		SetCameraPos({ 0, GetCameraPos().y });
	}

	if (GetCameraPos().y < 0)
	{
		float y = GetCameraPos().y;
		SetCameraPos({ GetCameraPos().x, 0 });
	}

	if ((GetCameraPos().x + (GetCameraScale().x * 2)) > 1280)
	{
		SetCameraPos({ 1280 - GetCameraScale().x *2, GetCameraPos().y});
	}

	if (GetCameraPos().y + GetCameraScale().y * 2 > 720)
	{
		SetCameraPos({ GetCameraPos().x, 720 - GetCameraScale().y * 2 });
	}
}

