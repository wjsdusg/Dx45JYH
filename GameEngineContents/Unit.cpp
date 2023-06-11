#include "PrecompileHeader.h"
#include "Unit.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "ContentsEnum.h"
#include "MapOverlay.h"
extern float CalAngle1To2(float4 _Pos1, float4 _Pos2);
extern float4 MainMouse;

std::vector<std::shared_ptr<Unit>> Unit::Units;
float Unit::DoubleClickTimer = 0.f;

int num = 0;
Unit::Unit()
{
	Id = num;
	num++;
}

Unit::~Unit()
{
}
void Unit::Update(float _DeltaTime)
{
	if (true == GameEngineTransform::AABB2DToAABB2D(Render0->GetTransform()->GetCollisionData(),MouseData))
	{
		//GetLevel()
	}
	std::vector<std::shared_ptr<GameEngineCollision>> ColTest;

	if (Collision->CollisionAll(static_cast<int>(ColEnum::MapOverlay), ColTest, ColType::SPHERE2D, ColType::SPHERE2D), 0 != ColTest.size())
	{
		for (std::shared_ptr<GameEngineCollision> Col : ColTest)
		{
			std::shared_ptr<MapOverlay> NewMapOverlay = Col->GetActor()->DynamicThis<MapOverlay>();
			if (nullptr != NewMapOverlay)
			{
				NewMapOverlay->GetColNRenders()[Col]->Death();
				Col->Death();
			}
		}
	}
	if (Collision->CollisionAll(static_cast<int>(ColEnum::Unit), ColTest, ColType::SPHERE2D, ColType::SPHERE2D), 0 != ColTest.size())
	{
		for (std::shared_ptr<GameEngineCollision> Col : ColTest)
		{
			std::shared_ptr<Unit> NewUnit = Col->GetActor()->DynamicThis<Unit>();
			if (NewUnit == DynamicThis<Unit>())
			{
				continue;
			}
			IsMove = false;
		}
	}
	MouseData.SPHERE.Center = MainMouse.DirectFloat3;
	MouseData.SPHERE.Radius = 0.0f;
	
	if (true == GameEngineTransform::AABB2DToSpehre2D(Render0->GetTransform()->GetCollisionData(), MouseData))
	{
		if (true == GameEngineInput::IsUp("EngineMouseLeft"))
		{
			if (true == IsClick && DoubleClickTimer < 0.5f)
			{
				for (int i = 0; i < Units.size(); i++)
				{
					Units[i]->IsClick = true;
				}
				
			}
			else
			{
				for (int i = 0; i < Units.size(); i++)
				{
					Units[i]->IsClick = false;
				}

				IsClick = true;
			}
			DoubleClickTimer = 0.f;
		}
	}
	if (IsClick == true)
	{
		DoubleClickTimer += _DeltaTime;
	}
	

}
void Unit::Start()
{
	Units.push_back(DynamicThis<Unit>());
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