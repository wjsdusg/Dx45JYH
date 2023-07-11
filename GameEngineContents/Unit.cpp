#include "PrecompileHeader.h"
#include "Unit.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineTileMapRenderer.h>
#include "ContentsEnum.h"
#include "MapOverlay.h"
#include "Minion.h"
#include "Mouse.h"
#include "GlobalValue.h"
#include "MapEditor.h"

extern float CalAngle1To2(float4 _Pos1, float4 _Pos2);
extern float4 MainMouse;
extern float4 IsoTileScale;
extern float4 MapUpP;
std::vector<std::shared_ptr<Unit>> Unit::Units;

std::vector<std::shared_ptr<Unit>> Unit::GetUnits()
{
	return Units;
}
int num = 0;
Unit::Unit()
{
	UnitID = num;
	num++;
	
}

Unit::~Unit()
{
}
void Unit::Update(float _DeltaTime)
{
	PathTime += _DeltaTime;

	if (0 != PathPos.size() && 0.1f <= PathTime)
	{
		float4 WPos = GetTransform()->GetWorldPosition();

		PathTime = 0.0f;
		float4 Pos = PathPos.front();
		GetTransform()->SetWorldPosition(Pos);
		PathPos.pop_front();
		return;
	}

	if (0 != PathPos.size())
	{
		return;
	}
	

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
	
	if (true == IsClick)
	{
		if (false == SelectionCircle->IsUpdate())
		{
			SelectionCircle->On();
			SelectionCircle->GetTransform()->SetLocalPosition({ 0,-20.f });
			SelectionCircle->GetTransform()->SetLocalScale({ 10.f,10.f });
		}
	}
	if (false == IsClick)
	{
		if (nullptr != SelectionCircle)
		{
			SelectionCircle->Off();
		}
	}

	if (true == GameEngineInput::IsUp("EngineMouseRight") && true == IsClick)
	{
		MousePickPos = MainMouse;
		TargetPos = MainMouse;
		IsHold = false;
		//FSM.ChangeState("Move");

		std::list<PathIndex> Result;

		float4 MPos = MapEditor::ConvertPosToTileXY(MousePickPos);
		float4 UPos = MapEditor::ConvertPosToTileXY(GetTransform()->GetWorldPosition());
		
		PathPos.clear();
		//GlobalValue::AStart.FindPath({ UPos.ix() , UPos.iy()}, { MPos.ix() ,MPos.iy()}, -1, PathResult);

		//for (const PathIndex& Point : PathResult)
		//{
		//	float4 ConvertPos;
		//	ConvertPos.x = (Point.X * 32.0f) + (Point.Y * -32.0f);
		//	ConvertPos.y = (Point.X * -16.0f) + (Point.Y * -16.0f);

		//	ConvertPos += MapUpP;

		//	PathPos.push_back(ConvertPos);
		//}

		GlobalValue::JpsP.Search( UPos.ix() , UPos.iy() ,  MPos.ix() ,MPos.iy() , JPSPathResult);

		for (const JPSCoord& Point : JPSPathResult)
		{
			float4 ConvertPos;
			ConvertPos.x = (Point.m_x * 32.0f) + (Point.m_y * -32.0f);
			ConvertPos.y = (Point.m_x * -16.0f) + (Point.m_y * -16.0f);

			ConvertPos += MapUpP;

			PathPos.push_back(ConvertPos);
		}



		PathTime = 0.0f;
		Mouse::NewMainMouse->GetMoveMark(MousePickPos);
	}

	if (true == GameEngineInput::IsUp("EngineMouseLeft") && true == IsM)
	{
		TargetPos = MainMouse;
		FSM.ChangeState("Move");
		Mouse::NewMainMouse->GetMoveMark(MousePickPos);
		IsM = false;
	}
	if (true == IsClick && true == GameEngineInput::IsUp("A"))
	{
		IsA = true;
	}
	if (true == GameEngineInput::IsUp("EngineMouseLeft") && true == IsA)
	{
		//�����̻���
		MousePickPos = MainMouse;
		TargetPos = MainMouse;		
		FSM.ChangeState("Move");
		Mouse::NewMainMouse->GetMoveMark(MousePickPos);
		//IsA = false;
	}
	if (true == GameEngineInput::IsUp("EngineMouseLeft") && true == IsP)
	{
		//�����̻���
		MousePickPos = MainMouse;
		TargetPos = MainMouse;
		FSM.ChangeState("Move");
		Mouse::NewMainMouse->GetMoveMark(MousePickPos);
		//IsA = false;
	}
	if (true == GameEngineInput::IsUp("H") && true == IsClick)
	{
		IsHold = true;
		FSM.ChangeState("Stay");
	}
	if (true== IsClick &&true == GameEngineInput::IsUp("EngineMouseRight") && (true == IsP || true == IsM || true == IsHold || true == IsA))
	{
		IsP = false;
		IsM  = false;
		IsHold = false;
		IsA = false;
	}
	
	{
		/*float4 Pos = MapOverlay::MainMapOverlay->GetTransform()->GetWorldPosition();
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
		}*/
	}
	
	FSM.Update(_DeltaTime);
}
void Unit::Start()
{
	Units.push_back(DynamicThis<Unit>());
	StateInit();
	Object::Start();
	SelectionCircle = CreateComponent<GameEngineSpriteRenderer>();
	SelectionCircle->Off();
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
			
			if (nullptr != FOVCollision&&nullptr != FOVCollision->Collision(ColEnum::Enemy,ColType::SPHERE2D,ColType::AABBBOX2D)&&false==IsHold)
			{				
				TargetCol = FOVCollision->Collision(ColEnum::Enemy, ColType::SPHERE2D, ColType::AABBBOX2D);
				TargetPos = TargetCol->GetActor()->GetTransform()->GetLocalPosition();
				PrePos = GetTransform()->GetLocalPosition();
				float s2 = GetTransform()->GetLocalPosition().XYDistance(TargetCol->GetTransform()->GetWorldPosition());
				FSM.ChangeState("Chase");
			}
			if (true == IsHold && nullptr!= Collision->Collision(ColEnum::Enemy, ColType::SPHERE2D, ColType::AABBBOX2D))
			{
				TargetPos = Collision->Collision(ColEnum::Enemy, ColType::SPHERE2D, ColType::AABBBOX2D)->GetActor()->GetTransform()->GetLocalPosition();
				FSM.ChangeState("HoldAttack");
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
			if (nullptr != TargetCol)
			{
				TargetCol = nullptr;
			}
		},
		.Update = [this](float _DeltaTime)
		{
			GetTransform()->AddLocalPosition(MovePointTowardsTarget(GetTransform()->GetLocalPosition(), TargetPos, Speed, _DeltaTime));
			if (TargetPos.XYDistance(GetTransform()->GetLocalPosition()) <= 5.f)
			{
				FSM.ChangeState("Stay");
			}
			
		},
		.End = [this]()
		{
			
		}
		}
	);
	FSM.CreateState(
		{ .Name = "Chase",
		.Start = [this]() {
			//Angle���
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
			float s = abs(FOVCollision->GetTransform()->GetLocalScale().x);
			float s2 = GetTransform()->GetLocalPosition().XYDistance(TargetCol->GetTransform()->GetWorldPosition());

			if (nullptr != FOVCollision && nullptr != TargetCol)
			{							
				TargetPos = TargetCol->GetActor()->GetTransform()->GetLocalPosition();
			}
			if (20.f <= abs(PreAngle - Angle))
			{
				FSM.ChangeState("Chase");
			}

			if (nullptr == TargetCol || true == TargetCol->GetActor()->IsDeath())
			{
				TargetCol = nullptr;
				FSM.ChangeState("Stay");
			}			
			//�þ� ���� ����� �����ڸ� ����
			
			else if (s
				<s2
				)
			{
				//TargetCol = FOVCollision->Collision(ColEnum::Enemy, ColType::SPHERE2D, ColType::AABBBOX2D);
				TargetCol = nullptr;
				TargetPos = PrePos;
				FSM.ChangeState("Move");
			}
			//��ũ��Ͱ������� ����
			else if (
				TargetPos.XYDistance(GetTransform()->GetLocalPosition()) 
				<= (TargetCol->GetActor()->DynamicThis<Unit>()->GetCollsion()->GetTransform()->GetLocalScale().x)
				)
			{
				FSM.ChangeState("Attack");
			}
			//�ȿ��� ������굵����
			GetTransform()->AddLocalPosition(MovePointTowardsTarget(GetTransform()->GetLocalPosition(), TargetPos, Speed, _DeltaTime));
		},
		.End = []() {}
		}
	);
	
	FSM.CreateState(
		{ .Name = "Attack",
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
				//��������
				MovePointTowardsTarget(GetTransform()->GetLocalPosition(), TargetPos, Speed, 0);

				if (true==TargetCol->GetActor()->IsDeath())
				{
					TargetCol=nullptr;
					FSM.ChangeState("Stay");
				}
				else
				{
					TargetPos = TargetCol->GetActor()->DynamicThis<Unit>()->GetTransform()->GetLocalPosition();
					if (
						TargetPos.XYDistance(GetTransform()->GetLocalPosition())
						> (TargetCol->GetActor()->DynamicThis<Unit>()->GetCollsion()->GetTransform()->GetLocalScale().x)
						)
					{
						FSM.ChangeState("Chase");
					}							
				}

				if (20.f <= abs(PreAngle - Angle))
				{
					FSM.ChangeState("Attack");
				}

			}
			
		},
		.End = []() {}
		}
	);
	FSM.CreateState(
		{ .Name = "HoldAttack",
		.Start = [this]() 
		{
			//��������
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
			MovePointTowardsTarget(GetTransform()->GetLocalPosition(), TargetPos, Speed, 0);
				if (20.f <= abs(PreAngle - Angle))
				{
					FSM.ChangeState("HoldAttack");
				}
				if (nullptr == Collision->Collision(ColEnum::Enemy, ColType::SPHERE2D, ColType::AABBBOX2D))
				{
					FSM.ChangeState("Stay");
				}
			}
		},
		.End = []() {}
		}
	);
	FSM.CreateState(
		{ .Name = "Die",
		.Start = [this]() 
		{
			Render0->ChangeAnimation("Die");
			auto it = std::find(Units.begin(), Units.end(), DynamicThis<Unit>());
			if (it != Units.end())
			{
				std::swap(*it, Units.back());
				Units.pop_back();
			}
			this->ObjectDeath();
		},
		.Update = [this](float _DeltaTime)
		{
			if (true == Render0->IsAnimationEnd())
			{
				Death();
			}
		},
		.End = []() {}
		}
	);
	
	FSM.ChangeState("Stay");
}