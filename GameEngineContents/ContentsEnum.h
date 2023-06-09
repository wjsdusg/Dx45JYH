#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
 float4 MapSize;
 float4 MiniMapSize;
 float4 MiniViewRatio;
 float4 MapRightP;
 float4 MapLeftP;
 float4 MapUpP;
 float4 MapDownP;
 float Slope;
 float Y_intercept;

 //y>= a*x+b �̸� x,y���� ��ų� �����ִ�.
 float4 TIleScale = { 40.f,40.f };
 bool CheckPointOnUpLine(float4 Point1,float4 Point2,float4 CheckPoint)
 {
	 float a = (Point1.y - Point2.y) / (Point1.x - Point2.x);
	 float b = Point2.y - a * Point2.x;
	 Slope = a;
	 b -= GameEngineWindow::GetScreenSize().y / 2;
	 Y_intercept = b;
	
	 bool check = CheckPoint.y >= a * CheckPoint.x + b;
	 return check;
 }

 bool CheckPointOnDownLine(float4 Point1, float4 Point2, float4 CheckPoint)
 {
	 float a = (Point1.y - Point2.y) / (Point1.x - Point2.x);
	 float b = Point2.y - a * Point2.x;
	 Slope = a;
	 b += GameEngineWindow::GetScreenSize().y / 2;
	 Y_intercept = b;

	 bool check = CheckPoint.y <= a * CheckPoint.x + b;
	 return check;
 }

 float4 MovePointLeftOnLine(float4 _PrePos, float _Speed,float _DeltaTime)
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