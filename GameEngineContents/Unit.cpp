#include "PrecompileHeader.h"
#include "Unit.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "ContentsEnum.h"
#include "MapOverlay.h"
extern float CalAngle1To2(float4 _Pos1, float4 _Pos2);
extern float4 MainMouse;

std::vector<std::shared_ptr<Unit>> Unit::Units;

Unit::Unit()
{

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
	MouseData.SPHERE.Center = MainMouse.DirectFloat3;
	MouseData.SPHERE.Radius = 0.0f;
	//À¯´Ö ºÎµ÷«‰´Ù´Â°É ¾Ë°í½ÍÀºµ¥
	//if (true == GameEngineTransform::AABB2DToSpehre2D(Render0->GetTransform()->GetCollisionData(), Æ÷°ýÀûÀÎ À¯´ÖÀÇ·»´õ Æ®·£½ºÆû)

	if (true == GameEngineTransform::AABB2DToSpehre2D(Render0->GetTransform()->GetCollisionData(), MouseData))
	{
		if (true == GameEngineInput::IsUp("EngineMouseLeft"))
		{
			for (int i = 0; i < Units.size(); i++)
			{
				Units[i]->IsClick = false;
			}
			IsClick = true;

		}
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