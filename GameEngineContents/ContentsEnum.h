#pragma once
#include <GameEngineBase/GameEngineMath.h>
 float4 MapSize;
 float4 MiniMapSize;
 float4 MiniViewRatio;
 float4 MapRightP;
 float4 MapLeftP;
 float4 MapUpP;
 float4 MapDownP;
 float Slope;
 float Y_intercept;
 //y>= a*x+b 이면 x,y점이 닿거나 위에있다.

 bool CheckPointOnUpLine(float4 Point1,float4 Point2,float4 CheckPoint)
 {
	 float a = (Point1.y - Point2.y) / (Point1.x - Point2.x);
	 float b = Point2.y - a * Point2.x;
	 Slope = a;
	 b -= 250.f;
	 Y_intercept = b;
	
	 bool check = CheckPoint.y >= a * CheckPoint.x + b;
	 return check;
 }

 bool CheckPointOnDownLine(float4 Point1, float4 Point2, float4 CheckPoint)
 {
	 float a = (Point1.y - Point2.y) / (Point1.x - Point2.x);
	 float b = Point2.y - a * Point2.x;
	 Slope = a;
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

