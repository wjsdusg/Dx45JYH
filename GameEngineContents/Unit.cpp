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
#include "Building.h"

extern float CalAngle1To2(float4 _Pos1, float4 _Pos2);
extern float4 MainMouse;
extern float4 IsoTileScale;
extern float4 MapUpP;
extern float4 TileScale;
std::vector<std::shared_ptr<Unit>> Unit::Units;
float Unit::AddSpeed=0;
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
	bool asd4 = IsNextTileCollision();
	int sdg = 0;
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
	//누르는순간 마우스에서 타겟포스를 정해준다.
	if (true == GameEngineInput::IsUp("EngineMouseRight") && true == IsClick/*&&MyField==Field::DungeonMap*/)
	{
		MousePickPos = MainMouse;
		//TargetPos = MainMouse;
		
		IsHold = false;
		
		if (MapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition()) != MapEditor::ConvertPosToTileXY(TargetPos))
		{
			//GlobalValue::Collision->ClrAt(IndexX, IndexY);
			PathCal();
			FSM.ChangeState("Move");
		}
		
	}
	{
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
		if (true == IsClick && true == GameEngineInput::IsUp("EngineMouseRight") && (true == IsP || true == IsM || true == IsHold || true == IsA))
		{
			IsP = false;
			IsM = false;
			IsHold = false;
			IsA = false;
		}

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
	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform()->SetLocalScale(TileScale);
	Collision->SetOrder(static_cast<int>(ColEnum::Unit));
	Collision->SetColType(ColType::AABBBOX2D);

	FOVCollision = CreateComponent<GameEngineCollision>();
	FOVCollision->GetTransform()->SetLocalScale({ FightFOV,FightFOV,1.f });
	FOVCollision->SetColType(ColType::SPHERE2D);
	FOVCollision->SetOrder(static_cast<int>(ColEnum::UnitFOV));

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
			IndexX = _Pos.ix();
			IndexY = _Pos.iy();
			float4 _Pos2 = MapEditor::ConvertTileXYToPos(IndexX, IndexY);
			GetTransform()->SetLocalPosition(_Pos2);
			GlobalValue::Collision->SetAt(IndexX, IndexY);
		},
		.Update = [this](float _DeltaTime)
		{
			float4 _Pos = MapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());
			if (IndexX != _Pos.x || IndexY != _Pos.y)
			{
				GlobalValue::Collision->ClrAt(IndexX, IndexY);
				IndexX = _Pos.ix();
				IndexY = _Pos.iy();
				float4 _Pos2 = MapEditor::ConvertTileXYToPos(IndexX, IndexY);
				GetTransform()->SetLocalPosition(_Pos2);
				GlobalValue::Collision->SetAt(IndexX, IndexY);
			}
			//유닛우선 쫒기
			std::vector<std::shared_ptr<GameEngineCollision>> ColTest;

			if (nullptr != FOVCollision
				&&FOVCollision->CollisionAll(static_cast<int>(ColEnum::Unit), ColTest, ColType::SPHERE2D, ColType::AABBBOX2D)
				&& 0!=ColTest.size()
				&&false==IsHold)
			{				
				for (std::shared_ptr<GameEngineCollision> Col : ColTest)
				{
					std::shared_ptr<Unit> NewUnit = Col->GetActor()->DynamicThis<Unit>();
					if (nullptr == NewUnit)
					{
						continue;
					}
					else if (NewUnit == DynamicThis<Unit>())
					{
						continue;
					}
					else if (MyTeam != NewUnit->GetTeam())
					{
						TargetCol = NewUnit->GetCollsion();
						TargetPos = TargetCol->GetActor()->GetTransform()->GetLocalPosition();
						PrePos = GetTransform()->GetLocalPosition();
						PathCal();
						CopyIndexX = MapEditor::ConvertPosToTileXY(TargetCol->GetActor()->GetTransform()->GetLocalPosition()).ix();
						CopyIndexY = MapEditor::ConvertPosToTileXY(TargetCol->GetActor()->GetTransform()->GetLocalPosition()).iy();
						FSM.ChangeState("Chase");
						break;
					}
				}				
			}
			else if (nullptr != FOVCollision
				&& FOVCollision->CollisionAll(static_cast<int>(ColEnum::Building), ColTest, ColType::SPHERE2D, ColType::AABBBOX2D)
				&& 0 != ColTest.size()
				&& false == IsHold)
			{
				for (std::shared_ptr<GameEngineCollision> Col : ColTest)
				{
					std::shared_ptr<Building> NewBuilding = Col->GetActor()->DynamicThis<Building>();
					if (nullptr == NewBuilding)
					{
						continue;
					}					
					else if (MyTeam != NewBuilding->GetTeam())
					{
						TargetCol = NewBuilding->GetCollsion();
						TargetPos = TargetCol->GetActor()->GetTransform()->GetLocalPosition();
						PrePos = GetTransform()->GetLocalPosition();
						PathCal();
						CopyIndexX = MapEditor::ConvertPosToTileXY(TargetCol->GetActor()->GetTransform()->GetLocalPosition()).ix();
						CopyIndexY = MapEditor::ConvertPosToTileXY(TargetCol->GetActor()->GetTransform()->GetLocalPosition()).iy();
						FSM.ChangeState("Chase");
						break;
					}
				}
			}
			if (true == IsHold && nullptr!= Collision->Collision(ColEnum::Unit, ColType::SPHERE2D, ColType::AABBBOX2D))
			{
				TargetPos = Collision->Collision(ColEnum::Unit, ColType::SPHERE2D, ColType::AABBBOX2D)->GetActor()->GetTransform()->GetLocalPosition();
				FSM.ChangeState("HoldAttack");
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
					float4 Pos2 = MapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());
					
					PathPos.pop_front();					
					
				}
				InterTargetPos = PathPos.front();
								
				PathPos.pop_front();	
				
				//각도계산
				PreAngle = Angle;
				CalAngle(GetTransform()->GetLocalPosition(), InterTargetPos);
				//지금 내가 가는 방향에 장애물이 없다면 그타일을 미리선점하고 그쪽으로 움직인다.
				if (false == IsNextTileCollision())
				{

					//현재위치콜리전 삭제
					GlobalValue::Collision->ClrAt(IndexX, IndexY);
					if (MapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition()) == MapEditor::ConvertPosToTileXY(InterTargetPos)/*&&180>abs(PreAngle-Angle)*/)
					{
						float4 _Pos = MapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());
						IndexX = _Pos.ix();
						IndexY = _Pos.iy();
						GlobalValue::Collision->SetAt(IndexX, IndexY);
						
						ShortTargetPos = MapEditor::ConvertTileXYToPos(IndexX, IndexY);
					}
					else 
					{
						//각도를 알기떄문에 그냥 쓰면된다
						float4 Pos = MapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());
						IndexX = Pos.ix();
						IndexY = Pos.iy();

						Pos = ReturnIndexPlusPos();
						IndexX = Pos.ix();
						IndexY = Pos.iy();
						
						GlobalValue::Collision->SetAt(IndexX, IndexY);
						
						ShortTargetPos = MapEditor::ConvertTileXYToPos(IndexX, IndexY);
					}
					
				}
				else if (true == IsNextTileCollision())
				{
					//경로계산
					PathCal();
					if (0 != PathPos.size())
					{
						if (MapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition()) == MapEditor::ConvertPosToTileXY(PathPos.front()))
						{
							PathPos.pop_front();
						}
						InterTargetPos = PathPos.front();

						PathPos.pop_front();

						CalAngle(MapEditor::ConvertPosToTilePos(GetTransform()->GetLocalPosition()), InterTargetPos);

						//현재위치콜리전 삭제
						GlobalValue::Collision->ClrAt(IndexX, IndexY);
						//각도를 알기떄문에 그냥 쓰면된다
						float4 Pos = MapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());
						IndexX = Pos.ix();
						IndexY = Pos.iy();

						Pos = ReturnIndexPlusPos();
						IndexX = Pos.ix();
						IndexY = Pos.iy();
						
						GlobalValue::Collision->SetAt(IndexX, IndexY);
						ShortTargetPos = MapEditor::ConvertTileXYToPos(IndexX, IndexY);
					}
				}
			}
			
			   			
			{
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
			}

			if (nullptr != TargetCol)
			{
				TargetCol = nullptr;
			}
		},
		.Update = [this](float _DeltaTime)
		{			
			GetTransform()->AddLocalPosition(MovePointTowardsTarget(GetTransform()->GetLocalPosition(), InterTargetPos, Speed, _DeltaTime));			
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
					if (false == IsNextTileCollision())
					{
						
						GlobalValue::Collision->ClrAt(IndexX, IndexY);
						//각도를 알기떄문에 그냥 쓰면된다						
						float4 Pos = ReturnIndexPlusPos();
						IndexX = Pos.ix();
						IndexY = Pos.iy();						
						GlobalValue::Collision->SetAt(IndexX, IndexY);
						ShortTargetPos = MapEditor::ConvertTileXYToPos(IndexX, IndexY);
					}
					else if(true == IsNextTileCollision())
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
	//쫒기전에 타겟콜을 미리 지정해줘야한다.
	FSM.CreateState(
		{ .Name = "Chase",
		.Start = [this]()
		{
			if (0 != PathPos.size())
			{

				if (GetTransform()->GetLocalPosition() == PathPos.front())
				{
					float4 Pos2 = MapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());

					PathPos.pop_front();

				}
				InterTargetPos = PathPos.front();

				PathPos.pop_front();

				//각도계산
				PreAngle = Angle;
				CalAngle(GetTransform()->GetLocalPosition(), InterTargetPos);
				//지금 내가 가는 방향에 장애물이 없다면 그타일을 미리선점하고 그쪽으로 움직인다.
				if (false == IsNextTileCollision())
				{

					//현재위치콜리전 삭제
					GlobalValue::Collision->ClrAt(IndexX, IndexY);
					if (MapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition()) == MapEditor::ConvertPosToTileXY(InterTargetPos)/*&&180>abs(PreAngle-Angle)*/)
					{
						float4 _Pos = MapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());
						IndexX = _Pos.ix();
						IndexY = _Pos.iy();
						GlobalValue::Collision->SetAt(IndexX, IndexY);

						ShortTargetPos = MapEditor::ConvertTileXYToPos(IndexX, IndexY);
					}
					else
					{
						//각도를 알기떄문에 그냥 쓰면된다
						float4 Pos = MapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());
						IndexX = Pos.ix();
						IndexY = Pos.iy();

						Pos = ReturnIndexPlusPos();
						IndexX = Pos.ix();
						IndexY = Pos.iy();

						GlobalValue::Collision->SetAt(IndexX, IndexY);

						ShortTargetPos = MapEditor::ConvertTileXYToPos(IndexX, IndexY);
					}

				}
				else if (true == IsNextTileCollision())
				{
					//경로계산
					PathCal();
					if (0 != PathPos.size())
					{
						if (MapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition()) == MapEditor::ConvertPosToTileXY(PathPos.front()))
						{
							PathPos.pop_front();
						}
						InterTargetPos = PathPos.front();

						PathPos.pop_front();

						CalAngle(MapEditor::ConvertPosToTilePos(GetTransform()->GetLocalPosition()), InterTargetPos);

						//현재위치콜리전 삭제
						GlobalValue::Collision->ClrAt(IndexX, IndexY);
						//각도를 알기떄문에 그냥 쓰면된다
						float4 Pos = MapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());
						IndexX = Pos.ix();
						IndexY = Pos.iy();

						Pos = ReturnIndexPlusPos();
						IndexX = Pos.ix();
						IndexY = Pos.iy();

						GlobalValue::Collision->SetAt(IndexX, IndexY);
						ShortTargetPos = MapEditor::ConvertTileXYToPos(IndexX, IndexY);
					}
				}
			}


			{
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
			}
			CopyUnit = nullptr;
			CopyBuilding = nullptr;
		},
		.Update = [this](float _DeltaTime)
		{
			
			float Min =10000.f;
			if (nullptr == FOVCollision)
			{
				return;
			}
			// 가장가까운대상에게 타겟팅된다.
			std::vector<std::shared_ptr<GameEngineCollision>> ColTest;
			if (FOVCollision->CollisionAll(static_cast<int>(ColEnum::Unit), ColTest, ColType::SPHERE2D, ColType::AABBBOX2D), 0 != ColTest.size())
			{
				for (std::shared_ptr<GameEngineCollision> Col : ColTest)
				{
					std::shared_ptr<Unit> NewUnit = Col->GetActor()->DynamicThis<Unit>();
					if (nullptr == NewUnit)
					{
						continue;
					}
					else if (NewUnit == DynamicThis<Unit>())
					{
						continue;
					}
					else if (MyTeam != NewUnit->GetTeam())
					{
						if (Min > NewUnit->GetTransform()->GetLocalPosition().XYDistance(GetTransform()->GetLocalPosition()))
						{
							Min = NewUnit->GetTransform()->GetLocalPosition().XYDistance(GetTransform()->GetLocalPosition());
							CopyUnit = NewUnit;
						}					
					}					
				}
				if (nullptr != CopyUnit && nullptr != TargetCol && CopyUnit->GetCollsion() != TargetCol)
				{
					TargetCol = CopyUnit->GetCollsion();
					TargetPos = TargetCol->GetActor()->GetTransform()->GetLocalPosition();
					PathCal();
					CopyIndexX = MapEditor::ConvertPosToTileXY(TargetCol->GetActor()->GetTransform()->GetLocalPosition()).ix();
					CopyIndexY = MapEditor::ConvertPosToTileXY(TargetCol->GetActor()->GetTransform()->GetLocalPosition()).iy();
					FSM.ChangeState("Chase");
					return;
				}
			}
			else if(FOVCollision->CollisionAll(static_cast<int>(ColEnum::Building), ColTest, ColType::OBBBOX2D, ColType::AABBBOX2D), 0 != ColTest.size())
			{
				for (std::shared_ptr<GameEngineCollision> Col : ColTest)
				{
					std::shared_ptr<Building> NewBuilding = Col->GetActor()->DynamicThis<Building>();
					if (nullptr == NewBuilding)
					{
						continue;
					}					
					else if (MyTeam != NewBuilding->GetTeam())
					{
						if (Min > NewBuilding->GetTransform()->GetLocalPosition().XYDistance(GetTransform()->GetLocalPosition()))
						{
							Min = NewBuilding->GetTransform()->GetLocalPosition().XYDistance(GetTransform()->GetLocalPosition());
							CopyBuilding = NewBuilding;
						}
					}
				}
				if (nullptr != CopyBuilding && nullptr != TargetCol && CopyBuilding->GetCollsion() != TargetCol)
				{
					TargetCol = CopyBuilding->GetCollsion();
					TargetPos = TargetCol->GetActor()->GetTransform()->GetLocalPosition();
					PathCal();
					CopyIndexX = MapEditor::ConvertPosToTileXY(TargetCol->GetActor()->GetTransform()->GetLocalPosition()).ix();
					CopyIndexY = MapEditor::ConvertPosToTileXY(TargetCol->GetActor()->GetTransform()->GetLocalPosition()).iy();
					FSM.ChangeState("Chase");
					return;
				}
			}			
			//타겟이사라지면대기상태로변경
			if (nullptr == TargetCol || true == TargetCol->GetActor()->IsDeath())
			{
				TargetCol = nullptr;
				FSM.ChangeState("Stay");
				return;
			}			
			//시야 범위 벗어나면 기존자리 복귀			
			else if (abs(FOVCollision->GetTransform()->GetLocalScale().x)
				< GetTransform()->GetLocalPosition().XYDistance(TargetCol->GetTransform()->GetWorldPosition())
				)
			{				
				TargetCol = nullptr;
				TargetPos = PrePos;
				PathCal();
				FSM.ChangeState("Move");
				return;
			}

			if(nullptr != TargetCol)
			{
				
				int _IndexX = TargetCol->GetActor()->DynamicThis<Object>()->IndexX;
				int _IndexY = TargetCol->GetActor()->DynamicThis<Object>()->IndexY;
				if(_IndexX != CopyIndexX || _IndexY != CopyIndexY)
				{
					TargetPos = MapEditor::ConvertTileXYToPos(_IndexX, _IndexY);
					PathCal();
					CopyIndexX = MapEditor::ConvertPosToTileXY(TargetCol->GetActor()->GetTransform()->GetLocalPosition()).ix();
					CopyIndexY = MapEditor::ConvertPosToTileXY(TargetCol->GetActor()->GetTransform()->GetLocalPosition()).iy();
					FSM.ChangeState("Chase");
					return;
				}
				
			}
			
			//안에서 각도계산도해줌
			GetTransform()->AddLocalPosition(MovePointTowardsTarget(GetTransform()->GetLocalPosition(), InterTargetPos, Speed, _DeltaTime));
			if (ShortTargetPos == InterTargetPos && InterTargetPos.XYDistance(GetTransform()->GetLocalPosition()) <= 2.f)
			{
				GetTransform()->SetLocalPosition(InterTargetPos);
				if (0 == PathPos.size())
				{
					FSM.ChangeState("Attack");
				}
				else
				{
					FSM.ChangeState("Chase");
				}
			}
			else
			{
				if (ShortTargetPos.XYDistance(GetTransform()->GetLocalPosition()) <= 2.f)
				{
					if (false == IsNextTileCollision())
					{

						GlobalValue::Collision->ClrAt(IndexX, IndexY);
						//각도를 알기떄문에 그냥 쓰면된다						
						float4 Pos = ReturnIndexPlusPos();
						IndexX = Pos.ix();
						IndexY = Pos.iy();
						GlobalValue::Collision->SetAt(IndexX, IndexY);
						ShortTargetPos = MapEditor::ConvertTileXYToPos(IndexX, IndexY);
					}
					else if (true == IsNextTileCollision())
					{
						PathCal();
						CopyIndexX = MapEditor::ConvertPosToTileXY(TargetCol->GetActor()->GetTransform()->GetLocalPosition()).ix();
						CopyIndexY = MapEditor::ConvertPosToTileXY(TargetCol->GetActor()->GetTransform()->GetLocalPosition()).iy();
						FSM.ChangeState("Chase");
					}
				}
			}
		},
		.End = []() {}
		}
	);
	
	FSM.CreateState(
		{ .Name = "Attack",
		.Start = [this]() 
		{
			CalAngle(GetTransform()->GetLocalPosition(), TargetCol->GetTransform()->GetLocalPosition());
			PreAngle = Angle;
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
			
		},
		.Update = [this](float _DeltaTime)
		{
			if (Render0->IsAnimationEnd())
			{				
				if (nullptr== TargetCol||true==TargetCol->GetActor()->IsDeath())
				{
					TargetCol=nullptr;
					FSM.ChangeState("Stay");
					return;
				}
				else
				{
					TargetPos = TargetCol->GetActor()->DynamicThis<Unit>()->GetTransform()->GetLocalPosition();
					float sds = TargetPos.XYDistance(GetTransform()->GetLocalPosition());
					float sds33 = (TargetCol->GetActor()->DynamicThis<Unit>()->GetCollsion()->GetTransform()->GetLocalScale().x);
					if (
						//둘사이거리
						sds
						//상대충돌체x크기
						> sds33
						)
					{

						PathCal();
						CopyIndexX = MapEditor::ConvertPosToTileXY(TargetCol->GetActor()->GetTransform()->GetLocalPosition()).ix();
						CopyIndexY = MapEditor::ConvertPosToTileXY(TargetCol->GetActor()->GetTransform()->GetLocalPosition()).iy();
						FSM.ChangeState("Chase");
						return;
					}							
				}
				//std::shared_ptr<Object> NewObject = TargetCol->DynamicThis<Object>();
				//NewObject->CurHp -= ATK;
				CalAngle(GetTransform()->GetLocalPosition(), TargetCol->GetTransform()->GetLocalPosition());
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
			
			CalAngle(GetTransform()->GetLocalPosition(), TargetPos);
				if (20.f <= abs(PreAngle - Angle))
				{
					FSM.ChangeState("HoldAttack");
				}
				if (nullptr == Collision->Collision(ColEnum::Unit, ColType::SPHERE2D, ColType::AABBBOX2D))
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
	CalAngle(GetTransform()->GetLocalPosition(), TargetPos);
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

bool Unit::IsNextTileCollision()
{
	int _IndexX = -1;
	int _IndexY = -1;
		
	
	if (Angle < 10 || Angle >= 350)
	{
		_IndexX = IndexX + 1;
		_IndexY = IndexY - 1;
		return GlobalValue::Collision->IsCollision(_IndexX, _IndexY);
	}
	if (Angle < 80 && Angle >= 10)
	{
		_IndexX = IndexX;
		_IndexY = IndexY - 1;
		return GlobalValue::Collision->IsCollision(_IndexX, _IndexY);
	}

	if (Angle < 100 && Angle >= 80)
	{
		_IndexX = IndexX - 1;
		_IndexY = IndexY - 1;
		return GlobalValue::Collision->IsCollision(_IndexX, _IndexY);
	}
	if (Angle < 170 && Angle >= 100)
	{
		_IndexX = IndexX - 1;
		_IndexY = IndexY;
		return GlobalValue::Collision->IsCollision(_IndexX, _IndexY);
	}
	if (Angle < 190 && Angle >= 170)
	{
		_IndexX = IndexX - 1;
		_IndexY = IndexY + 1;
		return GlobalValue::Collision->IsCollision(_IndexX, _IndexY);
	
	}
	if (Angle < 260 && Angle >= 190)
	{
		_IndexX = IndexX;
		_IndexY = IndexY + 1;
		return GlobalValue::Collision->IsCollision(_IndexX, _IndexY);
	}
	if (Angle < 280 && Angle >= 260)
	{	
		_IndexX = IndexX + 1;
		_IndexY = IndexY + 1;
		return GlobalValue::Collision->IsCollision(_IndexX, _IndexY);
	}
	if (Angle < 350 && Angle >= 280)
	{
		_IndexX = IndexX + 1;
		_IndexY = IndexY;
		return GlobalValue::Collision->IsCollision(_IndexX, _IndexY);
	}
}

float4 Unit::ReturnIndexPlusPos()
{
	int _IndexX = -1;
	int _IndexY = -1;
	float4 _Pos = float4::Zero;
	
	if (Angle < 10 || Angle >= 350)
	{
		_IndexX = IndexX + 1;
		_IndexY = IndexY - 1;
		_Pos = { static_cast<float>(_IndexX),static_cast<float>(_IndexY) };
		return _Pos;
	}
	else if (Angle < 80 && Angle >= 10)
	{
		_IndexX = IndexX;
		_IndexY = IndexY - 1;
		_Pos = { static_cast<float>(_IndexX),static_cast<float>(_IndexY) };
		return _Pos;
	}	
	else if (Angle < 100 && Angle >= 80)
	{
		_IndexX = IndexX - 1;
		_IndexY = IndexY - 1;
		_Pos = { static_cast<float>(_IndexX),static_cast<float>(_IndexY) };
		return _Pos;
	}
	else if (Angle < 170 && Angle >= 100)
	{
		_IndexX = IndexX - 1;
		_IndexY = IndexY;
		_Pos = { static_cast<float>(_IndexX),static_cast<float>(_IndexY) };
		return _Pos;
	}
	else if (Angle < 190 && Angle >= 170)
	{
		_IndexX = IndexX - 1;
		_IndexY = IndexY + 1;
		_Pos = { static_cast<float>(_IndexX),static_cast<float>(_IndexY) };
		return _Pos;
	}
	else if (Angle < 260 && Angle >= 190)
	{
		_IndexX = IndexX;
		_IndexY = IndexY + 1;
		_Pos = { static_cast<float>(_IndexX),static_cast<float>(_IndexY) };
		return _Pos;
	}
	else if (Angle < 280 && Angle >= 260)
	{
		_IndexX = IndexX + 1;
		_IndexY = IndexY + 1;
		_Pos = { static_cast<float>(_IndexX),static_cast<float>(_IndexY) };
		return _Pos;
	}
	else if (Angle < 350 && Angle >= 280)
	{
		_IndexX = IndexX + 1;
		_IndexY = IndexY;
		_Pos = { static_cast<float>(_IndexX),static_cast<float>(_IndexY) };
		return _Pos;
	}
	else
	{
		return _Pos;
	}
}

float Unit::CalAngle(float4 _Pos1, float4 _Pos2)
{
	float degree = CalAngle1To2(_Pos1, _Pos2);
	Angle = degree;
	return Angle;
}