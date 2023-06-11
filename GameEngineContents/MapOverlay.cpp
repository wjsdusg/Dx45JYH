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
extern float4 TIleScale;
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

	float tilenum = MapUpP.y * MapRightP.x * 2/TIleScale.x/TIleScale.y;
	
	float y = MapUpP.y;
	float x = 0;
	float4 Pos = { x,y };

	bool LeftLineCheck = true;
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
			NewCollision->GetTransform()->SetLocalScale(TIleScale);
			NewCollision->GetTransform()->SetLocalPosition(Pos);
			NewCollision->SetOrder(static_cast<int>(ColEnum::MapOverlay));
			std::shared_ptr<class GameEngineSpriteRenderer> NewRender = CreateComponent<GameEngineSpriteRenderer>();
			NewRender->GetTransform()->SetLocalScale(TIleScale);
			NewRender->GetTransform()->SetLocalPosition(Pos);
			NewRender->SetTexture("Black.png");
			NewRender->CameraCullingOn();
			ColNRenders[NewCollision] = NewRender;
		}
		else
		{
			std::shared_ptr<class GameEngineCollision> NewCollision = CreateComponent<GameEngineCollision>();
			NewCollision->GetTransform()->SetLocalScale(TIleScale);
			NewCollision->GetTransform()->SetLocalPosition(Pos);
			NewCollision->SetOrder(static_cast<int>(ColEnum::MapOverlay));
			std::shared_ptr<class GameEngineSpriteRenderer> NewRender = CreateComponent<GameEngineSpriteRenderer>();
			NewRender->GetTransform()->SetLocalScale(TIleScale);
			NewRender->GetTransform()->SetLocalPosition(Pos);
			NewRender->SetTexture("Black.png");
			NewRender->CameraCullingOn();
			ColNRenders[NewCollision] = NewRender;
		}
		if (true == CheckPointOnUpLine(MapRightP, MapUpP, Pos))
		{
			LeftLineCheck = true;
			Pos.y -= TIleScale.y;
			continue;
		}

		Pos.x += TIleScale.x;
	}

	AddScreenSizeY = true;

	/*TileMap = CreateComponent<GameEngineTileMapRenderer>();
	TileMap->CreateTileMap(1, 1, { 40,40 });
	TileMap->SetTile(0, 0, "kword");
	TileMap->GetTransform()->SetLocalScale({ 40,40,1 });
	TileMap->GetTransform()->SetLocalPosition({ 0,0 });
	*/
}

// 이건 디버깅용도나 
void MapOverlay::Render(float _Delta)
{

};
