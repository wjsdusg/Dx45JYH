#include "PrecompileHeader.h"
#include <Windows.h>
#include <GameEngineBase\GameEngineFile.h>
#include <GameEngineBase\GameEngineDirectory.h>
#include <GameEngineCore\GameEngineCore.h>
#include <GameEngineContents\ContentsCore.h>

#pragma comment(lib, "GameEngineCore.lib")
#pragma comment(lib, "GameEngineContents.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	float4 ss = float4::AngleToDirection2DToDeg(30.f);
	float sddd = ss.GetAnagleDegZ();
	float4 ss2 = float4::AngleToDirection2DToDeg(0.f);
	float4 ss3= ss.RotaitonZDegReturn(30.f);
	float g=float4::GetAngleVectorToVectorDeg(ss3, ss2);
	
	
	float sda = acosf(float(0.5))*GameEngineMath::RadToDeg;
	GameEngineCore::Start(hInstance,
		ContentsCore::GameStart,
		ContentsCore::GameEnd,
		{ 200, 0 }
	);
}


