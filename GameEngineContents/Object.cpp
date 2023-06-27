#include "PrecompileHeader.h"
#include "Object.h"
#include <GameEngineCore/GameEngineTileMapRenderer.h>
#include "MapOverlay.h"
#include "Unit.h"
#include "MiniMap.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
extern float4 IsoTileScale;
extern float4 MiniViewRatio;
std::list<std::shared_ptr<Object>> Object::Objects;

Object::Object()
{
	
}

Object::~Object()
{
}




void Object::Update(float _DeltaTime)
{	
	ObjectsSetTile();	
	std::list<std::shared_ptr<Object>>::iterator StartObject = Objects.begin();
	std::list<std::shared_ptr<Object>>::iterator EndObject = Objects.end();
	std::vector<std::shared_ptr<GameEngineUIRenderer>>::iterator StartRenders = MiniMap::MainMiniMap->MiniPoints.begin();
	std::vector<std::shared_ptr<GameEngineUIRenderer>>::iterator EndRenders = MiniMap::MainMiniMap->MiniPoints.end();
	while (StartObject != EndObject)
	{
		(*StartRenders)->GetTransform()->SetLocalPosition((*StartObject)->GetTransform()->GetWorldPosition() * MiniViewRatio);
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
		MiniMap::MainMiniMap->MiniPoints.push_back(NewPoint);
	}
}
void Object::ObjectsSetTile()
{
	
	float4 Pos = MapOverlay::MainMapOverlay->GetTransform()->GetWorldPosition();
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
	}
		
	
}