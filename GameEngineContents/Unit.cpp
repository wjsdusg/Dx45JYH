#include "PrecompileHeader.h"
#include "Unit.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTileMapRenderer.h>
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
	if (false == GameEngineInput::IsKey("G"))
	{
		GameEngineInput::CreateKey("G",'G');
	}
}

Unit::~Unit()
{
}
void Unit::Update(float _DeltaTime)
{
	
	
	if (true == GameEngineTransform::AABB2DToAABB2D(Render0->GetTransform()->GetCollisionData(), MouseData))
	{
		//GetLevel()
	}
	std::vector<std::shared_ptr<GameEngineCollision>> ColTest;

	if (Collision->CollisionAll(static_cast<int>(ColEnum::MapOverlay), ColTest, ColType::SPHERE2D, ColType::SPHERE2D), 0 != ColTest.size())
	{
		for (std::shared_ptr<GameEngineCollision> Col : ColTest)
		{
			/*std::shared_ptr<MapOverlay> NewMapOverlay = Col->GetActor()->DynamicThis<MapOverlay>();
			if (nullptr != NewMapOverlay)
			{
				NewMapOverlay->GetColNRenders()[Col]->Death();
				Col->Death();
			}*/
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
	if (true == IsClick)
	{
		if (nullptr == SelectionCircle)
		{
			SelectionCircle = CreateComponent<GameEngineSpriteRenderer>();
			SelectionCircle->GetTransform()->SetLocalPosition({ 0,-20.f });

			SelectionCircle->GetTransform()->SetLocalScale({ 10.f,10.f });
		}
	}
	if (false == IsClick)
	{
		if (nullptr != SelectionCircle)
		{
			SelectionCircle->Death();
			SelectionCircle = nullptr;

		}
	}

	if (true == GameEngineInput::IsUp("EngineMouseRight") && true == IsClick)
	{
		MousePickPos = MainMouse;
		
		FSM.ChangeState("Move");
	}



	FSM.Update(_DeltaTime);
	
	float4 Pos = MapOverlay::MainMapOverlay->GetTransform()->GetWorldPosition();
	NewMapOverlay->TileMap->SetTile(Render0->GetTransform()->GetWorldPosition()-Pos, "FOGWAR.png", 2);
    //	MapOverlay::MainMapOverlay->TileMap->SetTile(Render0->GetTransform()->GetWorldPosition()-Pos, "FOGWAR.png", 2);
	
	//if()
}
void Unit::Start()
{
	Units.push_back(DynamicThis<Unit>());
	StateInit();
}

float4 Unit::MovePointTowardsTarget(float4 _Pos1, float4 _Pos2, float _Speed, float _Delta)
{
	float degree = CalAngle1To2(_Pos1, _Pos2);
	Angle = degree;
	float radian = degree * GameEngineMath::DegToRad;
	float4 AddPos;
	AddPos.x = _Speed * _Delta * cosf(radian);
	AddPos.y = _Speed * _Delta * sinf(radian);

	return AddPos;
}

//FSM.CreateState(
//	{ .Name = "Move",
//	.Start = [this]() {},
//	.Update = [this](float _DeltaTime) {},
//	.End = []() {}
//	}
//);  fsm
void Unit::StateInit()
{
	FSM.CreateState(
		{ .Name = "Stay",
		.Start = [this]() {},
		.Update = [this](float _DeltaTime) {},
		.End = []() {}
		}
	);
	FSM.CreateState(
		{ .Name = "Move",
		.Start = [this]() {
			MovePointTowardsTarget(GetTransform()->GetLocalPosition(), MousePickPos, Speed, 0);
			if (Angle < 5 || Angle >= 355)
			{
				Render0->ChangeAnimation("LMove");
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}
			if (Angle < 85 && Angle >= 5)
			{
				Render0->ChangeAnimation("LUp45Move");
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}

			if (Angle < 95 && Angle >= 85)
			{
				Render0->ChangeAnimation("UpMove");
			}
			if (Angle < 175 && Angle >= 95)
			{
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
				Render0->ChangeAnimation("LUp45Move");
			}
			if (Angle < 185 && Angle >= 175)
			{
				Render0->ChangeAnimation("LMove");
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
			}
			if (Angle < 265 && Angle >= 185)
			{
				Render0->ChangeAnimation("LDown45Move");
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
			}
			if (Angle < 275 && Angle >= 265)
			{
				Render0->ChangeAnimation("DownMove");

			}
			if (Angle < 355 && Angle >= 275)
			{
				Render0->ChangeAnimation("LDown45Move");
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}
		},
		.Update = [this](float _DeltaTime)
		{
			GetTransform()->AddLocalPosition(MovePointTowardsTarget(GetTransform()->GetLocalPosition(), MousePickPos, Speed, _DeltaTime));
			if (MousePickPos.XYDistance(GetTransform()->GetLocalPosition()) <= 1.f)
			{
				FSM.ChangeState("Stay");
			}
			
		},
		.End = []() {}
		}
	);
	FSM.CreateState(
		{ .Name = "Fight",
		.Start = [this]() {},
		.Update = [this](float _DeltaTime) {},
		.End = []() {}
		}
	);
	FSM.CreateState(
		{ .Name = "Die",
		.Start = [this]() {},
		.Update = [this](float _DeltaTime) {},
		.End = []() {}
		}
	);

	FSM.ChangeState("Stay");
}