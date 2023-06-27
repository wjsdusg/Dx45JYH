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
	if (MiniMap::MainMiniMap->MiniPoints.size() != 0)
	{
		for (std::shared_ptr<GameEngineUIRenderer> NewObject : MiniMap::MainMiniMap->MiniPoints)
		{
			NewObject->Death();
			NewObject = nullptr;
		}
	}
	ObjectsSetTile();
	for (std::shared_ptr<Object> NewObject : Objects)
	{
		std::shared_ptr<GameEngineUIRenderer> NewPoint = CreateComponent<GameEngineUIRenderer>();
		
		NewPoint->GetTransform()->SetParent(MiniMap::MainMiniMap->GetTransform());
		NewPoint->GetTransform()->SetLocalScale({ 5.f,5.f,1.f });
		NewPoint->GetTransform()->SetLocalPosition(NewObject->GetTransform()->GetWorldPosition()* MiniViewRatio);
		MiniMap::MainMiniMap->MiniPoints.push_back(NewPoint);
	}

}

void Object::Start()
{
	if (nullptr != DynamicThis<Unit>())
	{
		Objects.push_back(DynamicThis<Object>());

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