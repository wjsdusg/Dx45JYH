#include "PrecompileHeader.h"
#include "MapOverlay.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineTileMapRenderer.h>

extern float4 MapSize;
extern float4 MiniMapSize;
extern float4 MiniViewRatio;
extern float4 MapRightP;
extern float4 MapLeftP;
extern float4 MapUpP;
extern float4 MapDownP;
extern float4 TIleScale;
extern  bool CheckPointOnUpLine(float4 Point1, float4 Point2, float4 CheckPoint);
extern  bool CheckPointOnDownLine(float4 Point1, float4 Point2, float4 CheckPoint);

extern void MovePointToLine(float4& _PrePos);

MapOverlay::MapOverlay()
{
}

MapOverlay::~MapOverlay()
{
}

void MapOverlay::Update(float _DeltaTime)
{



}
//ó������Ҷ� ���� ���� äũ�Ѵ�. ����� ������ ���ο� ��Ҵ��� Ȯ���Ѵ�
//������� �� ���� x���� - 20�� ���ش�.
void MapOverlay::Start()
{
	size_t tilenum = MapUpP.y * MapRightP.x * 2;
	Renders.resize(tilenum);
	size_t y = MapUpP.y;
	size_t x = 0;
	float4 Pos = { x,y };
	size_t Minx = 0;
	for (size_t i = 0; i <= tilenum; i++)
	{
		
		if (true == CheckPointOnUpLine(MapLeftP, MapUpP, Pos))
		{

		}
		CheckPointOnUpLine(MapRightP, MapUpP, Pos);
	}

	/*Render0 = CreateComponent<GameEngineRenderer>();
	
	Render0->SetTexture("Black.png");
	Render0->GetTransform()->SetLocalScale({ 40.f,40.f });*/

	/*TileMap = CreateComponent<GameEngineTileMapRenderer>();
	TileMap->CreateTileMap(1, 1, { 40,40 });
	TileMap->SetTile(0, 0, "kword");
	TileMap->GetTransform()->SetLocalScale({ 40,40,1 });
	TileMap->GetTransform()->SetLocalPosition({ 0,0 });
	*/
}

// �̰� �����뵵�� 
void MapOverlay::Render(float _Delta)
{

};
