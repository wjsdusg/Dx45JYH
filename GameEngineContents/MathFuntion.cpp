#pragma once
#include "PrecompileHeader.h"

float4 MapSize;
float4 MiniMapSize;
float4 MiniViewRatio;
float4 MapRightP;
float4 MapLeftP;
float4 MapUpP;
float4 MapDownP;
float MapRatio;
float Slope;
float Y_intercept;
bool AddScreenSizeY = true;

float4 UIMouse;
float4 MainMouse;
//y>= a*x+b 이면 x,y점이 닿거나 위에있다.
float4 TileScale = { 64.f,32.f,1 };
float4 IsoTileScale = {128,64.f,1};

bool CheckPointOnUpLine(float4 Point1, float4 Point2, float4 CheckPoint)
{
	float a = (Point1.y - Point2.y) / (Point1.x - Point2.x);
	float b = Point2.y - a * Point2.x;
	Slope = a;
	if (true == AddScreenSizeY)
	{
		b -= GameEngineWindow::GetScreenSize().y / 2;
	}
	Y_intercept = b;

	bool check = CheckPoint.y >= a * CheckPoint.x + b;
	return check;
}

bool CheckPointOnDownLine(float4 Point1, float4 Point2, float4 CheckPoint)
{
	float a = (Point1.y - Point2.y) / (Point1.x - Point2.x);
	float b = Point2.y - a * Point2.x;
	Slope = a;
	if (true == AddScreenSizeY)
	{
		b += GameEngineWindow::GetScreenSize().y / 2;
	}
	Y_intercept = b;

	bool check = CheckPoint.y <= a * CheckPoint.x + b;
	return check;
}

float4 MovePointLeftOnLine(float4 _PrePos, float _Speed, float _DeltaTime)
{
	float4 Pos;
	Pos.x = _PrePos.x - (_Speed / sqrtf(1 + Slope * Slope)) * _DeltaTime;
	Pos.y = Slope * Pos.x + Y_intercept;
	return Pos;
}

float4 MovePointRightOnLine(float4 _PrePos, float _Speed, float _DeltaTime)
{
	float4 Pos;
	Pos.x = _PrePos.x + (_Speed / sqrtf(1 + Slope * Slope)) * _DeltaTime;
	Pos.y = Slope * Pos.x + Y_intercept;
	return Pos;
}


void MovePointToLine(float4& _PrePos)
{
	_PrePos.y = Slope * _PrePos.x + Y_intercept;

}
void MovePointToLineX(float4& _PrePos)
{
	_PrePos.x = (_PrePos.y - Y_intercept) / Slope;


}
float CalAngle1To2(float4 _Pos1, float4 _Pos2)
{
	float AngleInRadians = atan2(_Pos2.y - _Pos1.y, _Pos2.x - _Pos1.x);
	float AngleInDegrees = AngleInRadians * GameEngineMath::RadToDeg;
	if (AngleInDegrees < 0) {
		AngleInDegrees += 360; // 각도가 음수인 경우 양수로 변환
	}
	return AngleInDegrees;
}

int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

int CalculateSideRhombusCount()
{
	float4 Pos;
	Pos.x = IsoTileScale.x;
	Pos.y = IsoTileScale.y;
	Pos.x /= 2;
	Pos.y /= 2;
	//IsoTileScale /= 10.f;
	float _Big = sqrtf(static_cast<float>(pow(MapUpP.y, 2)) + static_cast<float>(pow(MapRightP.x, 2)));
	float _Small = sqrtf(static_cast<float>(pow(Pos.y, 2)) + static_cast<float>(pow(Pos.x, 2)));
	int num = static_cast<int>(_Big / _Small);
	num++;
	return num;
}

