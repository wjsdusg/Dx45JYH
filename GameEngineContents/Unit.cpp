#include "PrecompileHeader.h"
#include "Unit.h"
extern float CalAngle1To2(float4 _Pos1, float4 _Pos2);

Unit::Unit()
{

}

Unit::~Unit()
{
}


float4 Unit::MovePointTowardsTarget(float4 _Pos1, float4 _Pos2, float _Speed,float _Delta)
{
	float degree = CalAngle1To2(_Pos1, _Pos2);
	Angle = degree;
	float radian = degree * GameEngineMath::DegToRad;
	float4 AddPos;
	AddPos.x = _Speed * _Delta * cosf(radian);
	AddPos.y = _Speed * _Delta * sinf(radian);
	
	return AddPos;
}