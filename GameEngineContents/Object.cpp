#include "PrecompileHeader.h"
#include "Object.h"
#include "Building.h"
#include <GameEngineCore/GameEngineTileMapRenderer.h>
#include "MapOverlay.h"
#include "Unit.h"
#include "MiniMap.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
extern float4 IsoTileScale;
extern float4 MiniViewRatio;
std::vector<std::shared_ptr<Object>> Object::Objects;
int Object::AddHp=0;
int Object::AddATK=0;
float Object::AddAttackSpeed=0;
float Object::AddAttackRange=0;
int Object::AddShield=0;
int Object::Money = 0;
Object::Object()
{
	int a = 0;
}

Object::~Object()
{
}




void Object::Update(float _DeltaTime)
{	
	ObjectsSetTile();	
	std::vector<std::shared_ptr<Object>>::iterator StartObject = Objects.begin();
	std::vector<std::shared_ptr<Object>>::iterator EndObject = Objects.end();
	std::vector<std::shared_ptr<GameEngineUIRenderer>>::iterator StartRenders = MiniMap::MainMiniMap->MiniPoints.begin();
	std::vector<std::shared_ptr<GameEngineUIRenderer>>::iterator EndRenders = MiniMap::MainMiniMap->MiniPoints.end();
	while (StartObject != EndObject)
	{
		(*StartRenders)->GetTransform()->SetLocalPosition((*StartObject)->GetTransform()->GetWorldPosition() * MiniViewRatio);
		if ((*StartObject)->MyTeam==Team::Enemy&&"GREENBOX.PNG"== (*StartRenders)->GetTexName())
		{
			(*StartRenders)->SetTexture("RedBox.png");
		}
		StartObject++;
		StartRenders++;
	}
}

void Object::Start()
{
	if (nullptr != DynamicThis<Unit>())
	{
		Objects.push_back(DynamicThis<Object>());
		std::shared_ptr<GameEngineUIRenderer> NewPoint = CreateComponent<GameEngineUIRenderer>();
		NewPoint->GetTransform()->SetParent(MiniMap::MainMiniMap->GetTransform());
		NewPoint->GetTransform()->SetLocalScale({ 3.f,3.f,1.f });
		if (MyTeam == Team::Mine)
		{
			NewPoint->SetTexture("GreenBox.png");
			
		}
		else
		{
			NewPoint->SetTexture("RedBox.png");
		}
		MiniMap::MainMiniMap->MiniPoints.push_back(NewPoint);
	}
	if (nullptr != DynamicThis<Building>())
	{
		Objects.push_back(DynamicThis<Object>());
		std::shared_ptr<GameEngineUIRenderer> NewPoint = CreateComponent<GameEngineUIRenderer>();
		NewPoint->GetTransform()->SetParent(MiniMap::MainMiniMap->GetTransform());
		NewPoint->GetTransform()->SetLocalScale({ 3.f,3.f,1.f });
		if (MyTeam == Team::Mine)
		{
			NewPoint->SetTexture("GreenBox.png");
		}
		else
		{
			NewPoint->SetTexture("RedBox.png");
		}
		MiniMap::MainMiniMap->MiniPoints.push_back(NewPoint);
	}
}
void Object::ObjectsSetTile()
{
	
	/*float4 Pos = MapOverlay::MainMapOverlay->GetTransform()->GetWorldPosition();
	for (std::shared_ptr<Object> NewObject : Objects)
	{
		for (float i = NewObject->GetTransform()->GetWorldPosition().y - FOV; i <= NewObject->GetTransform()->GetWorldPosition().y + FOV; i += IsoTileScale.y / 2)
		{
			for (float j = NewObject->GetTransform()->GetWorldPosition().x - FOV; j <= NewObject->GetTransform()->GetWorldPosition().x + FOV; j += IsoTileScale.x / 2)
			{
				float4 Pos2{ j,i };
				if (FOV >= Pos2.XYDistance(NewObject->GetTransform()->GetWorldPosition()))
				{
					MapOverlay::MainMapOverlay->TileMap->SetTile(Pos2 - Pos, "FOGWAR.png", 2);
				}
			}
		}
	}*/
		
	
}

void Object::ObjectDeath()
{
	int Count = 0;
	
	for (int i = 0; i < Objects.size(); i++)
	{
		if (DynamicThis<Object>() == Objects[i])
		{
			Objects.erase(Objects.begin() + Count);
			MiniMap::MainMiniMap->MiniPoints[i]->Death();
			MiniMap::MainMiniMap->MiniPoints.erase(MiniMap::MainMiniMap->MiniPoints.begin()+Count);
			break;
		}
		Count++;
	}	
}