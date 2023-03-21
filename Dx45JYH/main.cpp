#include <Windows.h>
#include <GameEngineBase\GameEngineFile.h>
#include <GameEngineCore/GameEngineCore.h>
#pragma comment(lib,"GameEngineBase.lib")
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	int Value = -1;

	GameEngineSerializer Data;
	Data.Write(Value);
}