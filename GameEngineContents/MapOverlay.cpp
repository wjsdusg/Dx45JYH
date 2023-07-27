#include "PrecompileHeader.h"
#include "MapOverlay.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineTileMapRenderer.h>
#include "ContentsEnum.h"
extern float4 MapSize;
extern float4 MiniMapSize;
extern float4 MiniViewRatio;
extern float4 MapRightP;
extern float4 MapLeftP;
extern float4 MapUpP;
extern float4 MapDownP;
extern float4 TileScale;
extern  bool CheckPointOnUpLine(float4 Point1, float4 Point2, float4 CheckPoint);
extern  bool CheckPointOnDownLine(float4 Point1, float4 Point2, float4 CheckPoint);
extern void MovePointToLine(float4& _PrePos);
extern void MovePointToLineX(float4& _PrePos);
extern  bool AddScreenSizeY;
extern int CalculateSideRhombusCount();
extern int gcd(int a, int b);
extern float4 IsoTileScale;
MapOverlay* MapOverlay::MainMapOverlay = nullptr;
MapOverlay::MapOverlay()
{
	MainMapOverlay = this;
}

MapOverlay::~MapOverlay()
{
}

void MapOverlay::Update(float _DeltaTime)
{



}

void MapOverlay::Start()
{

	if (nullptr == GameEngineSprite::Find("FOGWAR.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("FOGWAR.png").GetFullPath(), 3, 1);
	}	

	//int s = gcd(MapUpP.y, MapRightP.x);
	//IsoTileScale.y = MapUpP.y / s/2;
	//IsoTileScale.x = MapRightP.x / s/2;
	
	TileMap = CreateComponent<GameEngineTileMapRenderer>();
	TileMap->CreateTileMap(CalculateSideRhombusCount(), CalculateSideRhombusCount(),0 ,IsoTileScale, IsoTileScale,TileMapMode::Iso);
	TileMap->TilemapCullingOn();
	for (size_t y = 0; y < TileMap->GetCount().y; y++)
	{
		for (size_t x = 0; x < TileMap->GetCount().x; x++)
		{
			TileMap->SetTile(x, y, "FOGWAR.png", 0);
		}
	}
	
}

// 이건 디버깅용도나 
void MapOverlay::Render(float _Delta)
{

};
