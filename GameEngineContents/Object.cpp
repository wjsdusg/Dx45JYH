#include "PrecompileHeader.h"
#include "Object.h"
#include <GameEngineCore/GameEngineTileMapRenderer.h>
#include "MapOverlay.h"
#include "Unit.h"
extern float4 IsoTileScale;

std::vector<std::shared_ptr<Object>> Object::Objects;
Object::Object()
{
	
}

Object::~Object()
{
}


void Object::TileFOV(float4 _OldPos, float4 _NewPos)
{
	float4 Pos = MapOverlay::MainMapOverlay->GetTransform()->GetWorldPosition();
	float oldStartX = _OldPos.x - FOV;
	float oldEndX = _OldPos.x + FOV;
	float oldStartY = _OldPos.y - FOV;
	float oldEndY = _OldPos.y + FOV;
	
	float newStartX = _NewPos.x - FOV;
	float newEndX = _NewPos.x + FOV;
	float newStartY = _NewPos.y - FOV;
	float newEndY = _NewPos.y + FOV;
	for (float y =oldStartY ; y <= oldEndY; y += IsoTileScale.y / 2)
	{
		for (float x= oldStartX ; x <= oldEndX; x+= IsoTileScale.x / 2)
		{
			float4 Pos2={x,y};
			if (x < newStartX || x > newEndX || y < newStartY || y > newEndY)
			{
				MapOverlay::MainMapOverlay->TileMap->SubCount(Pos2 - Pos);
				if (MapOverlay::MainMapOverlay->TileMap->GetCount(Pos2 - Pos) == 0) 
				{
					MapOverlay::MainMapOverlay->TileMap->SetTile(Pos2 - Pos, "FOGWAR.png", 1);
				}
			}
			if (FOV >= Pos2.XYDistance(GetTransform()->GetWorldPosition()))
			{
				
			}
		}
	}

	for (float y = newStartY; y <= newEndY; y += IsoTileScale.y / 2)
	{
		for (float x = newStartX; x <= newEndX; x += IsoTileScale.x / 2)
		{
			float4 Pos2 = { x,y };
			if (x < oldStartX || x > oldEndX || y < oldStartY || y > oldEndY)
			{
				MapOverlay::MainMapOverlay->TileMap->AddCount(Pos2 - Pos);
				if (MapOverlay::MainMapOverlay->TileMap->GetCount(Pos2 - Pos) == 1)
				{
					MapOverlay::MainMapOverlay->TileMap->SetTile(Pos2 - Pos, "FOGWAR.png", 2);
				}
			}
		}
	}
}



void Object::CreateTileFOV(float4 _NewPos)
{
	float4 Pos = MapOverlay::MainMapOverlay->GetTransform()->GetWorldPosition();
	
	float newStartX = _NewPos.x - FOV;
	float newEndX = _NewPos.x + FOV;
	float newStartY = _NewPos.y - FOV;
	float newEndY = _NewPos.y + FOV;
	

	for (float y = newStartY; y <= newEndY; y += IsoTileScale.y / 2)
	{
		for (float x = newStartX; x <= newEndX; x += IsoTileScale.x / 2)
		{
			float4 Pos2 = { x,y };
			
				MapOverlay::MainMapOverlay->TileMap->AddCount(Pos2 - Pos);
				if (MapOverlay::MainMapOverlay->TileMap->GetCount(Pos2 - Pos) == 1)
				{
					MapOverlay::MainMapOverlay->TileMap->SetTile(Pos2 - Pos, "FOGWAR.png", 2);
				}
			
		}
	}
}

void Object::Update(float _DeltaTime)
{
	ObjectsSetTile();
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