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
MapOverlay::MapOverlay()
{
}

MapOverlay::~MapOverlay()
{
}

void MapOverlay::Update(float _DeltaTime)
{



}

void MapOverlay::Start()
{
	AddScreenSizeY = false;

	float tilenum = MapUpP.y * MapRightP.x * 2/TileScale.x/TileScale.y;
	
	float y = MapUpP.y;
	float x = 0;
	float4 Pos = { x,y };

	/*bool LeftLineCheck = true;
	for (float i = 0; i <= tilenum; i++)
	{
		if (Pos.y <= 0)
		{
			break;
		}
		if (true == LeftLineCheck)
		{
			CheckPointOnUpLine(MapLeftP, MapUpP, Pos);
			MovePointToLineX(Pos);
			LeftLineCheck = false;

			std::shared_ptr<class GameEngineCollision> NewCollision = CreateComponent<GameEngineCollision>();
			NewCollision->GetTransform()->SetLocalScale(TileScale);
			NewCollision->GetTransform()->SetLocalPosition(Pos);
			NewCollision->SetOrder(static_cast<int>(ColEnum::MapOverlay));
			std::shared_ptr<class GameEngineSpriteRenderer> NewRender = CreateComponent<GameEngineSpriteRenderer>();
			NewRender->GetTransform()->SetLocalScale(TileScale);
			NewRender->GetTransform()->SetLocalPosition(Pos);
			NewRender->SetTexture("Black.png");
			NewRender->CameraCullingOn();
			ColNRenders[NewCollision] = NewRender;
		}
		else
		{
			std::shared_ptr<class GameEngineCollision> NewCollision = CreateComponent<GameEngineCollision>();
			NewCollision->GetTransform()->SetLocalScale(TileScale);
			NewCollision->GetTransform()->SetLocalPosition(Pos);
			NewCollision->SetOrder(static_cast<int>(ColEnum::MapOverlay));
			std::shared_ptr<class GameEngineSpriteRenderer> NewRender = CreateComponent<GameEngineSpriteRenderer>();
			NewRender->GetTransform()->SetLocalScale(TileScale);
			NewRender->GetTransform()->SetLocalPosition(Pos);
			NewRender->SetTexture("Black.png");
			NewRender->CameraCullingOn();
			ColNRenders[NewCollision] = NewRender;
		}
		if (true == CheckPointOnUpLine(MapRightP, MapUpP, Pos))
		{
			LeftLineCheck = true;
			Pos.y -= TileScale.y;
			continue;
		}

		Pos.x += TileScale.x;
	}*/

	AddScreenSizeY = true;
	if (nullptr == GameEngineSprite::Find("MapOverray"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("MapOverray").GetFullPath());
	}
	//TileMap = CreateComponent<GameEngineTileMapRenderer>();
	//TileMap->CreateTileMap(MapRightP.x*2/TileScale.x, MapUpP.y * 2 / TileScale.y, TileScale);

	//TileMap->TilemapCullingOn();
	//TileMap->GetTransform()->SetLocalPosition({MapLeftP.x,MapDownP.y});
	//float4 ss =TileMap->GetTransform()->GetLocalPosition();
	//TileMap->GetTransform()->SetLocalScale({ 1.f,1.f });
	//GetLevel()->GetMainCamera();
	////TileMap->CalSortZ(GetLevel()->GetMainCamera());
	//for (int i = 0; i < MapRightP.x * 2 / TileScale.x; i++)
	//{
	//	for (int j = 0; j < MapUpP.y * 2 / TileScale.y; j++)
	//	{
	//		TileMap->SetTile(i, j, "MapOverray");
	//	}		
	//}
	

	
	

	
}

// 이건 디버깅용도나 
void MapOverlay::Render(float _Delta)
{

};
