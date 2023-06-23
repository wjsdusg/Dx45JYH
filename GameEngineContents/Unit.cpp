#include "PrecompileHeader.h"
#include "Unit.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTileMapRenderer.h>
#include "ContentsEnum.h"
#include "MapOverlay.h"
#include "Minion.h"
extern float CalAngle1To2(float4 _Pos1, float4 _Pos2);
extern float4 MainMouse;
extern float4 IsoTileScale;
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
	/*std::vector<std::shared_ptr<GameEngineCollision>> ColTest;
	if (Collision->CollisionAll(static_cast<int>(ColEnum::Unit), ColTest, ColType::AABBBOX2D, ColType::AABBBOX2D), 0 != ColTest.size())
	{
		for (std::shared_ptr<GameEngineCollision> Col : ColTest)
		{
			std::shared_ptr<Unit> NewUnit = Col->GetActor()->DynamicThis<Unit>();
			if (NewUnit == DynamicThis<Unit>())
			{
				continue;
			}
			NewUnit->FSM.ChangeState("Stay");
		}
	}*/
	MouseData.SPHERE.Center = MainMouse.DirectFloat3;
	MouseData.SPHERE.Radius = 0.0f;

	if (true == GameEngineTransform::AABB2DToSpehre2D(Render0->GetTransform()->GetCollisionData(), MouseData))
	{
		if (true == GameEngineInput::IsUp("EngineMouseLeft"))
		{
			if (true == IsClick && DoubleClickTimer < 0.5f)
			{
				/*for (int i = 0; i < Units.size(); i++)
				{
					Units[i]->IsClick = true;
				}*/
				for (auto Start = Units.begin(); Start!=Units.end(); Start++)
				{
					(*Start)->IsClick = true;
				}

			}
			else
			{
				for (auto Start = Units.begin(); Start != Units.end(); Start++)
				{
					(*Start)->IsClick = false;
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
		TargetPos = MainMouse;
		FSM.ChangeState("Move");
	}

	{
		float4 Pos = MapOverlay::MainMapOverlay->GetTransform()->GetWorldPosition();
		for (float i = GetTransform()->GetWorldPosition().y - FOV; i <= GetTransform()->GetWorldPosition().y + FOV; i += IsoTileScale.y / 2)
		{
			for (float j = GetTransform()->GetWorldPosition().x - FOV; j <= GetTransform()->GetWorldPosition().x + FOV; j += IsoTileScale.x/2)
			{
				float4 Pos2{ j,i };
				
				if (FOV >= Pos2.XYDistance(GetTransform()->GetWorldPosition()))
				{
					MapOverlay::MainMapOverlay->TileMap->SetTile(Pos2 - Pos, "FOGWAR.png", 1);
				}
			}
		}
	}
	
	FSM.Update(_DeltaTime);
}
void Unit::Start()
{
	Units.push_back(DynamicThis<Unit>());
	StateInit();
	Object::Start();
	//CreateTileFOV(GetTransform()->GetLocalPosition());
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

void Unit::StateInit()
{
	FSM.CreateState(
		{ .Name = "Stay",
		.Start = [this]() 
		{
			
			if (Angle < 10 || Angle >= 350)
			{
				Render0->ChangeAnimation("LStay");
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}
			if (Angle < 80 && Angle >= 10)
			{
				Render0->ChangeAnimation("LUp45Stay");
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}

			if (Angle < 100 && Angle >= 80)
			{
				Render0->ChangeAnimation("UpStay");
			}
			if (Angle < 170 && Angle >= 100)
			{
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
				Render0->ChangeAnimation("LUp45Stay");
			}
			if (Angle < 190 && Angle >= 170)
			{
				Render0->ChangeAnimation("LStay");
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
			}
			if (Angle < 260 && Angle >= 190)
			{
				Render0->ChangeAnimation("LDown45Stay");
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
			}
			if (Angle < 280 && Angle >= 260)
			{
				Render0->ChangeAnimation("DownStay");

			}
			if (Angle < 350 && Angle >= 280)
			{
				Render0->ChangeAnimation("LDown45Stay");
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}
		},
		.Update = [this](float _DeltaTime)
		{
			
			if (nullptr != FOVCollision&&nullptr != FOVCollision->Collision(ColEnum::Monster,ColType::SPHERE2D,ColType::AABBBOX2D))
			{				
				TargetCol = FOVCollision->Collision(ColEnum::Monster, ColType::SPHERE2D, ColType::AABBBOX2D);
				TargetPos = TargetCol->GetActor()->GetTransform()->GetLocalPosition();
				PrePos = GetTransform()->GetLocalPosition();
				FSM.ChangeState("Chase");
			}
		},
		.End = []() {}
		}
	);
	FSM.CreateState(
		{ .Name = "Move",
		.Start = [this]() {
			MovePointTowardsTarget(GetTransform()->GetLocalPosition(), TargetPos, Speed, 0);
			if (Angle < 10 || Angle >= 350)
			{
				Render0->ChangeAnimation("LMove");
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}
			if (Angle < 80 && Angle >= 10)
			{
				Render0->ChangeAnimation("LUp45Move");
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}

			if (Angle < 100 && Angle >= 80)
			{
				Render0->ChangeAnimation("UpMove");
			}
			if (Angle < 170 && Angle >= 100)
			{
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
				Render0->ChangeAnimation("LUp45Move");
			}
			if (Angle < 190 && Angle >= 170)
			{
				Render0->ChangeAnimation("LMove");
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
			}
			if (Angle < 260 && Angle >= 190)
			{
				Render0->ChangeAnimation("LDown45Move");
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
			}
			if (Angle < 280 && Angle >= 260)
			{
				Render0->ChangeAnimation("DownMove");

			}
			if (Angle < 350 && Angle >= 280)
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
			GetTransform()->AddLocalPosition(MovePointTowardsTarget(GetTransform()->GetLocalPosition(), TargetPos, Speed, _DeltaTime));
			if (MousePickPos.XYDistance(GetTransform()->GetLocalPosition()) <= 1.f)
			{
				FSM.ChangeState("Stay");
			}
			
		},
		.End = []() {}
		}
	);
	FSM.CreateState(
		{ .Name = "Chase",
		.Start = [this]() {
			MovePointTowardsTarget(GetTransform()->GetLocalPosition(), TargetPos, Speed, 0);
			if (Angle < 10 || Angle >= 350)
			{
				Render0->ChangeAnimation("LMove");
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}
			if (Angle < 80 && Angle >= 10)
			{
				Render0->ChangeAnimation("LUp45Move");
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}

			if (Angle < 100 && Angle >= 80)
			{
				Render0->ChangeAnimation("UpMove");
			}
			if (Angle < 170 && Angle >= 100)
			{
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
				Render0->ChangeAnimation("LUp45Move");
			}
			if (Angle < 190 && Angle >= 170)
			{
				Render0->ChangeAnimation("LMove");
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
			}
			if (Angle < 260 && Angle >= 190)
			{
				Render0->ChangeAnimation("LDown45Move");
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
			}
			if (Angle < 280 && Angle >= 260)
			{
				Render0->ChangeAnimation("DownMove");

			}
			if (Angle < 350 && Angle >= 280)
			{
				Render0->ChangeAnimation("LDown45Move");
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}
			PreAngle = Angle;
		},
		.Update = [this](float _DeltaTime)
		{
			if (nullptr != FOVCollision && nullptr != FOVCollision->Collision(ColEnum::Monster,ColType::SPHERE2D,ColType::AABBBOX2D))
			{
								
				TargetPos = FOVCollision->Collision(ColEnum::Monster, ColType::SPHERE2D, ColType::AABBBOX2D)->GetActor()->GetTransform()->GetLocalPosition();
				float4 pos = GetTransform()->GetLocalPosition();
				
			}
			if (20.f <= abs(PreAngle - Angle))
			{
				FSM.ChangeState("Chase");
			}
			GetTransform()->AddLocalPosition(MovePointTowardsTarget(GetTransform()->GetLocalPosition(), TargetPos, Speed, _DeltaTime));

			//TargetCol=
			
			if (nullptr == FOVCollision->Collision(ColEnum::Monster, ColType::SPHERE2D, ColType::AABBBOX2D))
			{
				TargetCol = nullptr;
			}
			if (nullptr == TargetCol)
			{
				FSM.ChangeState("Stay");
			}
			if (FightFOV < GetTransform()->GetLocalPosition().XYDistance(TargetPos))
			{
				TargetPos = PrePos;
				FSM.ChangeState("Move");
			}
			if (
				TargetPos.XYDistance(GetTransform()->GetLocalPosition()) 
				<= (TargetCol->GetActor()->DynamicThis<Unit>()->GetCollsion()->GetTransform()->GetLocalScale().x)
				)
			{
				FSM.ChangeState("Fight");
			}

		},
		.End = []() {}
		}
	);
	FSM.CreateState(
		{ .Name = "Fight",
		.Start = [this]() 
		{
			MovePointTowardsTarget(GetTransform()->GetLocalPosition(), TargetPos, Speed, 0);
			if (Angle < 10 || Angle >= 350)
			{
				Render0->ChangeAnimation("LAttack");
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}
			if (Angle < 80 && Angle >= 10)
			{
				Render0->ChangeAnimation("LUp45Attack");
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}

			if (Angle < 100 && Angle >= 80)
			{
				Render0->ChangeAnimation("UpAttack");
			}
			if (Angle < 170 && Angle >= 100)
			{
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
				Render0->ChangeAnimation("LUp45Attack");
			}
			if (Angle < 190 && Angle >= 170)
			{
				Render0->ChangeAnimation("LAttack");
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
			}
			if (Angle < 260 && Angle >= 190)
			{
				Render0->ChangeAnimation("LDown45Attack");
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
			}
			if (Angle < 280 && Angle >= 260)
			{
				Render0->ChangeAnimation("DownAttack");

			}
			if (Angle < 350 && Angle >= 280)
			{
				Render0->ChangeAnimation("LDown45Attack");
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}
			PreAngle = Angle;
		},
		.Update = [this](float _DeltaTime)
		{
			if (Render0->IsAnimationEnd())
			{
				//AnimationEnd = true;
				MovePointTowardsTarget(GetTransform()->GetLocalPosition(), TargetPos, Speed, 0);
				if (20.f <= abs(PreAngle - Angle))
				{
					FSM.ChangeState("Fight");
				}
				if (nullptr == TargetCol)
				{
					FSM.ChangeState("Stay");
				}


				TargetPos = TargetCol->GetActor()->DynamicThis<Unit>()->GetTransform()->GetLocalPosition();
				if (
					TargetPos.XYDistance(GetTransform()->GetLocalPosition())
			> (TargetCol->GetActor()->DynamicThis<Unit>()->GetCollsion()->GetTransform()->GetLocalScale().x)
					)
				{
					FSM.ChangeState("Chase");
				}

			}
			
		},
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