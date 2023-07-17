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
			
			SelectionCircle->GetTransform()->SetLocalScale({ 10.f,10.f });
		}
	}	
	else
	{
		if (true== SelectionCircle->IsUpdate())
		{
			SelectionCircle->Off();
		}
	}

	if (true == GameEngineInput::IsUp("EngineMouseRight") && true == IsClick/*&&MyField==Field::DungeonMap*/)
	{
		MousePickPos = MainMouse;	
		TargetPos = MainMouse;
		IsHold = false;
		PathCal();
		if (MapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition()) != MapEditor::ConvertPosToTileXY(TargetPos))
		{
			FSM.ChangeState("Move");
		}
		
	}
	if (true == IsClick && true == GameEngineInput::IsUp("A"))
	{
		IsA = true;
	}
	if (true == GameEngineInput::IsUp("EngineMouseLeft") && true == IsM)
	{
		TargetPos = MainMouse;
		FSM.ChangeState("Move");
		Mouse::NewMainMouse->GetMoveMark(MousePickPos);
		IsM = false;
	}
	if (true == GameEngineInput::IsUp("EngineMouseLeft") && true == IsA)
	{
		//여기이상함
		MousePickPos = MainMouse;
		TargetPos = MainMouse;		
		FSM.ChangeState("Move");
		Mouse::NewMainMouse->GetMoveMark(MousePickPos);
		//IsA = false;
	}
	if (true == GameEngineInput::IsUp("EngineMouseLeft") && true == IsP)
	{
		//여기이상함
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
	float HalfY = Render0->GetTransform()->GetLocalScale().hy();
	HalfY -= 10.f;
	Render0->GetTransform()->SetLocalPosition({ 0,HalfY });	
	SelectionCircle = CreateComponent<GameEngineSpriteRenderer>();	
	SelectionCircle->Off();
	//CreateTileFOV(GetTransform()->GetLocalPosition());
	MyField = Field::DungeonMap;
}

float4 Unit::MovePointTowardsTarget(float4 _Pos1, float4 _Pos2, float _Speed, float _Delta)
{
	float degree = CalAngle1To2(_Pos1, _Pos2);
	Angle = static_cast<int>(degree);	
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
			else if (Angle < 80 && Angle >= 10)
			{
				Render0->ChangeAnimation("LUp45Stay");
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}

			else if (Angle < 100 && Angle >= 80)
			{
				Render0->ChangeAnimation("UpStay");
			}
			else if (Angle < 170 && Angle >= 100)
			{
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
				Render0->ChangeAnimation("LUp45Stay");
			}
			else if (Angle < 190 && Angle >= 170)
			{
				Render0->ChangeAnimation("LStay");
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
			}
			else if (Angle < 260 && Angle >= 190)
			{
				Render0->ChangeAnimation("LDown45Stay");
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
			}
			else if (Angle < 280 && Angle >= 260)
			{
				Render0->ChangeAnimation("DownStay");

			}
			else if (Angle < 350 && Angle >= 280)
			{
				Render0->ChangeAnimation("LDown45Stay");
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}
			float4 _Pos = MapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());
			IndexX = _Pos.x;
			IndexY = _Pos.y;
			float4 _Pos2 = MapEditor::ConvertTileXYToPos(IndexX, IndexY);
			GetTransform()->SetLocalPosition(_Pos2);
			GlobalValue::Collision->SetAt(IndexX, IndexY);
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
			
			float4 _Pos = MapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());
			if (IndexX != _Pos.x || IndexY != _Pos.y)
			{
				GlobalValue::Collision->ClrAt(IndexX, IndexY);
				IndexX = _Pos.x;
				IndexY = _Pos.y;
				float4 _Pos2 = MapEditor::ConvertTileXYToPos(IndexX, IndexY);
				GetTransform()->SetLocalPosition(_Pos2);
				GlobalValue::Collision->SetAt(IndexX, IndexY);
			}
			/*if (false == GlobalValue::Collision->IsCollision(IndexX, IndexY))
			{
				GlobalValue::Collision->SetAt(IndexX, IndexY);
			}*/
		},
		.End = []() {}
		}
	);
	FSM.CreateState(
		{ .Name = "Move",
		.Start = [this]() {
			//경로계산
			if (0 != PathPos.size())
			{
				if (GetTransform()->GetLocalPosition() == PathPos.front())
				{
					PathPos.pop_front();
				}
				InterTargetPos = PathPos.front();
				
				PathPos.pop_front();			
			}
			//각도계산
			CalAngle(GetTransform()->GetLocalPosition(), InterTargetPos);
			//지금 내가 가는 방향에 장애물이 없다면 그영역을 미리선점하고 그쪽으로 움직인다.
			if (false == IsTileCollision())
			{				
				GlobalValue::Collision->ClrAt(IndexX, IndexY);
				//각도를 알기떄문에 그냥 쓰면된다
				float4 Pos = ReturnIndexPlusPos();
				GlobalValue::Collision->SetAt(Pos.x, Pos.y);
				ShortTargetPos = MapEditor::ConvertTileXYToPos(Pos.x, Pos.y);
			}
			else if(true == IsTileCollision())
			{
				PathCal();
				if (0 != PathPos.size())
				{
					if (GetTransform()->GetLocalPosition() == PathPos.front())
					{
						PathPos.pop_front();
					}
					InterTargetPos = PathPos.front();

					PathPos.pop_front();
				}
			}

   			if (Angle < 10 || Angle >= 350)
			{
				Render0->ChangeAnimation("LMove");
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}
			else if (Angle < 80 && Angle >= 10)
			{
				Render0->ChangeAnimation("LUp45Move");
				
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}
			else if (Angle < 100 && Angle >= 80)
			{
				Render0->ChangeAnimation("UpMove");
			}
			else if (Angle < 170 && Angle >= 100)
			{
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
				Render0->ChangeAnimation("LUp45Move");
			}
			else if (Angle < 190 && Angle >= 170)
			{
				Render0->ChangeAnimation("LMove");
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
			}
			else if (Angle < 260 && Angle >= 190)
			{
				Render0->ChangeAnimation("LDown45Move");
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
			}
			else if (Angle < 280 && Angle >= 260)
			{
				Render0->ChangeAnimation("DownMove");

			}
			else if (Angle < 350 && Angle >= 280)
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
			GetTransform()->AddLocalPosition(MovePointTowardsTarget(GetTransform()->GetLocalPosition(), InterTargetPos, Speed, _DeltaTime));
			float ss = InterTargetPos.XYDistance(GetTransform()->GetLocalPosition());
			if (ShortTargetPos==InterTargetPos&&InterTargetPos.XYDistance(GetTransform()->GetLocalPosition()) <= 2.f)
			{
				GetTransform()->SetLocalPosition(InterTargetPos);
				if (0 == PathPos.size())
				{
					FSM.ChangeState("Stay");
				}
				else
				{
					FSM.ChangeState("Move");
				}
			}
			else
			{
				if (ShortTargetPos.XYDistance(GetTransform()->GetLocalPosition()) <= 2.f)
				{
					if (false == IsTileCollision())
					{
						GlobalValue::Collision->ClrAt(IndexX, IndexY);
						//각도를 알기떄문에 그냥 쓰면된다
						float4 Pos = ReturnIndexPlusPos();
						GlobalValue::Collision->SetAt(Pos.x, Pos.y);
						ShortTargetPos = MapEditor::ConvertTileXYToPos(Pos.x, Pos.y);
					}
					else
					{
						PathCal();
						FSM.ChangeState("Move");
					}
				}
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
			//Angle계산
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
			//시야 범위 벗어나면 기존자리 복귀
			
			else if (s
				<s2
				)
			{
				//TargetCol = FOVCollision->Collision(ColEnum::Enemy, ColType::SPHERE2D, ColType::AABBBOX2D);
				TargetCol = nullptr;
				TargetPos = PrePos;
				FSM.ChangeState("Move");
			}
			//적크기와같아지면 공격
			else if (
				TargetPos.XYDistance(GetTransform()->GetLocalPosition()) 
				<= (TargetCol->GetActor()->DynamicThis<Unit>()->GetCollsion()->GetTransform()->GetLocalScale().x)
				)
			{
				FSM.ChangeState("Attack");
			}
			//안에서 각도계산도해줌
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
				//각도계산용
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
			//각도계산용
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

void Unit::PathCal()
{
	
	float4 MPos = MapEditor::ConvertPosToTileXY(TargetPos);
	float4 UPos = MapEditor::ConvertPosToTileXY(GetTransform()->GetWorldPosition());

	PathPos.clear();
	//Angle계산
	MovePointTowardsTarget(GetTransform()->GetLocalPosition(), TargetPos, Speed, 0);

	GlobalValue::JpsP.Search(UPos.ix(), UPos.iy(), MPos.ix(), MPos.iy(), JPSPathResult);
		
	if (JPSPathResult.size() == 0)
	{
		if (Angle < 45 || Angle >= 315)
		{
			//오른쪽
			int CloseXRight = GlobalValue::Collision->GetOpenValue(MPos.ix(), MPos.iy(), true, true);
			int CloseXLeft = GlobalValue::Collision->GetOpenValue(MPos.ix(), MPos.iy(), true, false);
			if (CloseXRight == MPos.ix())
			{
				int _Y = MPos.iy();
				while (JPSPathResult.size() == 0)
				{
					CloseXRight--;
					_Y++;
					GlobalValue::JpsP.Search(UPos.ix(), UPos.iy(), CloseXRight, _Y, JPSPathResult);					
					if (GlobalValue::Collision->IsOutBound(CloseXRight, _Y))
					{
						break;
					}
				}
			}
			else
			{
				if (abs(MPos.ix() - CloseXRight) <= abs(MPos.ix() - CloseXLeft))
				{
					GlobalValue::JpsP.Search(UPos.ix(), UPos.iy(), CloseXRight, MPos.iy(), JPSPathResult);
				}
				else
				{
					GlobalValue::JpsP.Search(UPos.ix(), UPos.iy(), CloseXLeft, MPos.iy(), JPSPathResult);
				}
				
			}
		}
		else if (Angle >= 45 && Angle < 135)
		{
			//위
			int CloseYUp = GlobalValue::Collision->GetOpenValue(MPos.ix(), MPos.iy(), false, false);
			int CloseYDown = GlobalValue::Collision->GetOpenValue(MPos.ix(), MPos.iy(), false, true);
			if (CloseYUp == MPos.iy())
			{
				int _X = MPos.ix();
				while (JPSPathResult.size() == 0)
				{
					CloseYUp++;
					_X++;
					GlobalValue::JpsP.Search(UPos.ix(), UPos.iy(), _X, CloseYUp, JPSPathResult);
					
					if (GlobalValue::Collision->IsOutBound(_X, CloseYUp))
					{
						break;
					}
				}
			}
			else
			{				
				if (abs(MPos.iy() - CloseYUp) <= abs(MPos.iy() - CloseYDown))
				{
					GlobalValue::JpsP.Search(UPos.ix(), UPos.iy(), MPos.ix(), CloseYUp, JPSPathResult);
				}
				else
				{
					GlobalValue::JpsP.Search(UPos.ix(), UPos.iy(), MPos.ix(), CloseYDown, JPSPathResult);
				}
			}
		}
		else if (Angle >= 135 && Angle < 225)
		{
			//왼
			int CloseXRight = GlobalValue::Collision->GetOpenValue(MPos.ix(), MPos.iy(), true, true);
			int CloseXLeft = GlobalValue::Collision->GetOpenValue(MPos.ix(), MPos.iy(), true, false);
			if (CloseXLeft == MPos.ix())
			{
				int _Y = MPos.iy();
				while (JPSPathResult.size() == 0)
				{
					CloseXLeft++;
					_Y--;
					GlobalValue::JpsP.Search(UPos.ix(), UPos.iy(), CloseXLeft, _Y, JPSPathResult);
					
					if (GlobalValue::Collision->IsOutBound(CloseXLeft, _Y))
					{
						break;
					}
				}
			}
			else
			{
				if (abs(MPos.ix() - CloseXRight) >= abs(MPos.ix() - CloseXLeft))
				{
					GlobalValue::JpsP.Search(UPos.ix(), UPos.iy(), CloseXLeft, MPos.iy(), JPSPathResult);
				}
				else
				{					
					GlobalValue::JpsP.Search(UPos.ix(), UPos.iy(), CloseXRight, MPos.iy(), JPSPathResult);
				}

			}
		}
		else if (Angle >= 225 && Angle < 315)
		{
			//밑
			int CloseYUp = GlobalValue::Collision->GetOpenValue(MPos.ix(), MPos.iy(), false, false);
			int CloseYDown = GlobalValue::Collision->GetOpenValue(MPos.ix(), MPos.iy(), false, true);
			if (CloseYUp == MPos.iy())
			{
				int _X = MPos.ix();
				while (JPSPathResult.size() == 0)
				{
					CloseYDown--;
					_X--;
					GlobalValue::JpsP.Search(UPos.ix(), UPos.iy(), _X, CloseYDown, JPSPathResult);

					if (GlobalValue::Collision->IsOutBound(_X, CloseYDown))
					{
						break;
					}
				}
			}
			else
			{
				if (abs(MPos.iy() - CloseYUp) >= abs(MPos.iy() - CloseYDown))
				{
					GlobalValue::JpsP.Search(UPos.ix(), UPos.iy(), MPos.ix(), CloseYDown, JPSPathResult);
				}
				else
				{
					GlobalValue::JpsP.Search(UPos.ix(), UPos.iy(), MPos.ix(), CloseYUp, JPSPathResult);
				}
			}
		}
	}

	for (const JPSCoord& Point : JPSPathResult)
	{
		float4 ConvertPos = MapEditor::ConvertTileXYToPos(Point.m_x, Point.m_y);
		PathPos.push_back(ConvertPos);

	}
}

bool Unit::IsTileCollision()
{
	int _IndexX = -1;
	int _IndexY = -1;
	if (0 == Angle)
	{
		_IndexX = IndexX + 1;
		_IndexY = IndexY - 1;
		return GlobalValue::Collision->IsCollision(_IndexX, _IndexY);
	}
	else if (26 == Angle)
	{
		
		_IndexY = IndexY - 1;
		return GlobalValue::Collision->IsCollision(_IndexX, _IndexY);
	}
	else if (90 == Angle)
	{
		_IndexX = IndexX - 1;
		_IndexY = IndexY - 1;
		return GlobalValue::Collision->IsCollision(_IndexX, _IndexY);
	}
	else if (153 == Angle)
	{
		_IndexX = IndexX + 1;
		return GlobalValue::Collision->IsCollision(_IndexX, _IndexY);
	}
	else if (180 == Angle)
	{
		_IndexX = IndexX - 1;
		_IndexY = IndexY + 1;
		return GlobalValue::Collision->IsCollision(_IndexX, _IndexY);
	}
	else if (206 == Angle)
	{
		
		_IndexY = IndexY + 1;
		return GlobalValue::Collision->IsCollision(_IndexX, _IndexY);
	}
	else if (270 == Angle)
	{
		_IndexX = IndexX + 1;
		_IndexY = IndexY + 1;
		return GlobalValue::Collision->IsCollision(_IndexX, _IndexY);
	}
	else if (333 == Angle)
	{
		_IndexX = IndexX + 1;
		return GlobalValue::Collision->IsCollision(_IndexX, _IndexY);
	}
	return false;
}

float4 Unit::ReturnIndexPlusPos()
{
	int _IndexX = -1;
	int _IndexY = -1;
	float4 _Pos = float4::Zero;
	if (0 == Angle)
	{
		_IndexX = IndexX + 1;
		_IndexY = IndexY - 1;
		_Pos = { static_cast<float>(_IndexX),static_cast<float>(_IndexY) };
		return _Pos;
	}
	else if (26 == Angle)
	{

		_IndexY = IndexY - 1;
		_Pos = { static_cast<float>(_IndexX),static_cast<float>(_IndexY) };
		return _Pos;
	}
	else if (90 == Angle)
	{
		_IndexX = IndexX - 1;
		_IndexY = IndexY - 1;
		_Pos = { static_cast<float>(_IndexX),static_cast<float>(_IndexY) };
		return _Pos;
	}
	else if (153 == Angle)
	{
		_IndexX = IndexX + 1;
		_Pos = { static_cast<float>(_IndexX),static_cast<float>(_IndexY) };
		return _Pos;
	}
	else if (180 == Angle)
	{
		_IndexX = IndexX - 1;
		_IndexY = IndexY + 1;
		_Pos = { static_cast<float>(_IndexX),static_cast<float>(_IndexY) };
		return _Pos;
	}
	else if (206 == Angle)
	{

		_IndexY = IndexY + 1;
		_Pos = { static_cast<float>(_IndexX),static_cast<float>(_IndexY) };
		return _Pos;
	}
	else if (270 == Angle)
	{
		_IndexX = IndexX + 1;
		_IndexY = IndexY + 1;
		_Pos = { static_cast<float>(_IndexX),static_cast<float>(_IndexY) };
		return _Pos;
	}
	else if (333 == Angle)
	{
		_IndexX = IndexX + 1;
		_Pos = { static_cast<float>(_IndexX),static_cast<float>(_IndexY) };
		return _Pos;
	}
	else
	{
		return _Pos;
		//MsgAssert("말도안된다");
	}
}

int Unit::CalAngle(float4 _Pos1, float4 _Pos2)
{
	float degree = CalAngle1To2(_Pos1, _Pos2);
	Angle = static_cast<int>(degree);
	return Angle;
}