#include "PrecompileHeader.h"
#include "MapOverlay.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineTileMapRenderer.h>
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
	if (nullptr == GameEngineSprite::Find("kword"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");

		// TestAnimation.png

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("kword").GetFullPath());


	}

	/*Render0 = CreateComponent<GameEngineSpriteRenderer>();

	Render0->SetTexture("Black.png");
	Render0->GetTransform()->SetLocalScale({ 40.f,40.f });*/

	//TileMap = CreateComponent<GameEngineTileMapRenderer>();
	//TileMap->CreateTileMap(1, 1, { 40,40 });
	//TileMap->SetTile(0, 0, "kword");

}

// 이건 디버깅용도나 
void MapOverlay::Render(float _Delta)
{

};
