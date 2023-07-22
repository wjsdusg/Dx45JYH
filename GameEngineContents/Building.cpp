#include "PrecompileHeader.h"
#include "Building.h"
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