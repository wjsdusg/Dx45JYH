#include "PrecompileHeader.h"
#include "Building.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineTileMapRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "GlobalValue.h"
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


Building::Building()
{	

}

Building::~Building()
{
}
void Building::Update(float _DeltaTime)
{
	/*std::vector<std::shared_ptr<GameEngineCollision>> ColTest;
	if (Collision->CollisionAll(static_cast<int>(ColEnum::Building), ColTest, ColType::AABBBOX2D, ColType::AABBBOX2D), 0 != ColTest.size())
	{
		for (std::shared_ptr<GameEngineCollision> Col : ColTest)
		{
			std::shared_ptr<Building> NewBuilding = Col->GetActor()->DynamicThis<Building>();
			if (NewBuilding == DynamicThis<Building>())
			{
				continue;
			}
			NewBuilding->FSM.ChangeState("Stay");
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
		if (true == SelectionCircle->IsUpdate())
		{
			SelectionCircle->Off();
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
void Building::Start()
{
	
	
	Object::Start();
	float HalfY = Render0->GetTransform()->GetLocalScale().hy();
	HalfY -= 10.f;
	Render0->GetTransform()->SetLocalPosition({ 0,HalfY });
	SelectionCircle = CreateComponent<GameEngineSpriteRenderer>();
	SelectionCircle->Off();
	//CreateTileFOV(GetTransform()->GetLocalPosition());
	MyField = Field::DungeonMap;
	
	StateInit();
}



void Building::StateInit()
{
	FSM.CreateState(
		{ .Name = "Stay",
		.Start = [this]()
		{			
			Render0->ChangeAnimation("Stay");
			float4 _Pos = MapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());
			IndexX = _Pos.ix();
			IndexY = _Pos.iy();
			float4 _Pos2 = MapEditor::ConvertTileXYToPos(IndexX, IndexY);
			GetTransform()->SetLocalPosition(_Pos2);
			GlobalValue::Collision->SetAt(IndexX, IndexY);
		},
		.Update = [this](float _DeltaTime)
		{

			/*if (nullptr != FOVCollision && nullptr != FOVCollision->Collision(ColEnum::Unit,ColType::SPHERE2D,ColType::AABBBOX2D))
			{
				TargetCol = FOVCollision->Collision(ColEnum::Unit, ColType::SPHERE2D, ColType::AABBBOX2D);
				TargetPos = TargetCol->GetActor()->GetTransform()->GetLocalPosition();				
				FSM.ChangeState("Attack");
			}	*/		

		},
		.End = []() {}
		}
	);
	FSM.CreateState(
		{ .Name = "Attack",
		.Start = [this]()
		{
			
			
		},
		.Update = [this](float _DeltaTime)
		{
			if (Render0->IsAnimationEnd())
			{
				//AnimationEnd = true;
				//각도계산용
				CalAngle(GetTransform()->GetLocalPosition(), TargetPos);

				if (true == TargetCol->GetActor()->IsDeath()|| nullptr == FOVCollision->Collision(ColEnum::Enemy, ColType::SPHERE2D, ColType::AABBBOX2D))
				{
					TargetCol = nullptr;
					FSM.ChangeState("Stay");
				}
				else
				{
					TargetPos = TargetCol->GetActor()->DynamicThis<Building>()->GetTransform()->GetLocalPosition();
					if (
						TargetPos.XYDistance(GetTransform()->GetLocalPosition())
						> (TargetCol->GetActor()->DynamicThis<Building>()->GetCollsion()->GetTransform()->GetLocalScale().x)
						)
					{
						FSM.ChangeState("Chase");
					}
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
			for (int i = 0; i < TileCollsionSetPos.size(); i++)
			{
				GlobalValue::Collision->ClrAt(TileCollsionSetPos[i].ix(), TileCollsionSetPos[i].iy());
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

float Building::CalAngle(float4 _Pos1, float4 _Pos2)
{
	float degree = CalAngle1To2(_Pos1, _Pos2);
	Angle = degree;
	return Angle;
}

void Building::SetTileCollsion()
{
	if (nullptr != Render0)
	{
		float4 Scale =Render0->GetTransform()->GetLocalScale();
		float4 Pos =Render0->GetTransform()->GetWorldPosition();
		IndexX= MapEditor::ConvertPosToTileXY(Pos).ix();
		IndexY = MapEditor::ConvertPosToTileXY(Pos).iy();

		float4 UpPos = Pos;
		UpPos.y+=Scale.hy();		
		float4 IndexUp = MapEditor::ConvertPosToTileXY(UpPos);
		
		float4 RightPos = Pos;
		RightPos.x += Scale.hx();
		float4 IndexR = MapEditor::ConvertPosToTileXY(RightPos);

		float4 LeftPos = Pos;
		LeftPos.x -= Scale.hx();
		float4 IndexL = MapEditor::ConvertPosToTileXY(LeftPos);

		float4 DownPos = Pos;
		DownPos.y -= Scale.hy();
		float4 IndexDown = MapEditor::ConvertPosToTileXY(DownPos);
		for (int j = IndexUp.iy(); j <= IndexDown.iy(); j++)
		{
			for (int i = IndexUp.ix(); i <= IndexR.ix(); i++)
			{
				TileCollsionSetPos.push_back({ static_cast<float>(i),static_cast<float>(j) });
				GlobalValue::Collision->SetAt(i, j);
			}
		}
		
	}
}

void Building::ArrEnemyunit()
{
	int x = IndexX;
	int y = IndexY;
	int num = 0;
	if (0 >= EnemyNum|| 1>EnemyUnits.size())
	{
		return;
	}
	for (int n = 1; n <= 180; n++) {
		for (int dy = -n; dy <= n; dy++) {
			for (int dx = -n; dx <= n; dx ++) {
				
				int nx = x + dx;
				int ny = y + dy;
				if (true == GlobalValue::Collision->IsOutBound(nx, ny))
				{
					return;
				}
				if (false == GlobalValue::Collision->IsCollision(nx, ny))
				{
					float4 Pos = MapEditor::ConvertTileXYToPos(nx, ny);
					if (nullptr != EnemyUnits[num])
					{
						EnemyUnits[num]->On();
						EnemyUnits[num]->GetTransform()->SetLocalPosition(Pos);
						EnemyUnits[num]->SetTeam(Team::Enemy);
						num++;
					}					
				}
				if (EnemyUnits.size() == num)
				{
					//EnemyUnits.clear();
					//EnemyNum = 0;
					return;
				}
				
			}
		}
	}
}