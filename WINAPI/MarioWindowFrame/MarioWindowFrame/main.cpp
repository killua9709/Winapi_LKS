#include <Windows.h>
#include <GameEngineContents/StudyGameCore.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineMath.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// std::vector<unsigned int> Value = GameEngineMath::GetDigits(-1000);

	StudyGameCore::GetInst().CoreStart(hInstance);
	return 1;
}