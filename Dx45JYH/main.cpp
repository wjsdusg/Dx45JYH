#include "PrecompileHeader.h"
#include <Windows.h>
#include <GameEngineBase\GameEngineFile.h>
#include <GameEngineBase\GameEngineDirectory.h>
#include <GameEngineCore\GameEngineCore.h>
#include <GameEngineContents\ContentsCore.h>
#include <GameEngineBase/GameEngineRandom.h>
#pragma comment(lib, "GameEngineCore.lib")
#pragma comment(lib, "GameEngineContents.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	//_CrtSetBreakAlloc(1000);
	float4 ss = float4::AngleToDirection2DToDeg(30.f);
	float sddd = ss.GetAnagleDegZ();
	float4 ss2 = float4::AngleToDirection2DToDeg(0.f);
	float4 ss3= ss.RotaitonZDegReturn(30.f);
	float g=float4::GetAngleVectorToVectorDeg(ss3, ss2);
	for (int i = 0; i < 10; i++)
	{
	int sd =GameEngineRandom::MainRandom.RandomInt(0, 6);
	}

	float sda = acosf(float(0.5))*GameEngineMath::RadToDeg;

	{
		/*GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentsBin");
		NewDir.Move("ContentsBin");
		
		

		std::string Str = "aaaaa bbbbb ccccc";
		GameEngineSerializer Data;
		Data.Write(Str);

		GameEngineFile NewFile = GameEngineFile(NewDir.GetPlusFileName("AAAA.data").GetFullPath());
		NewFile.SaveBin(Data);
		GameEngineSerializer ss;
		NewFile.LoadBin(ss);
		std::string Str2;
		ss.Read(Str2);

		int a = 0;*/
		

	}

	GameEngineCore::Start(hInstance,
		ContentsCore::GameStart,
		ContentsCore::GameEnd,
		{ 200, 0 }
	);
}


