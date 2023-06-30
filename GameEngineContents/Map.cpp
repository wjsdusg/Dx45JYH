#include "PrecompileHeader.h"
#include "Map.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


Map::Map()
{
}

Map::~Map()
{
}

extern float4 MapSize;
extern float4 MapRightP;
extern float4 MapLeftP;
extern float4 MapUpP;
extern float4 MapDownP;
extern float MapRatio;
void Map::Update(float _DeltaTime)
{


	std::vector<std::shared_ptr<GameEngineCollision>> ColTest;

	

}

void Map::Start()
{
	/*{
		if (nullptr == GameEngineSprite::Find("RealBackground.png"))
		{
			GameEngineDirectory NewDir;
			NewDir.MoveParentToDirectory("ContentResources");
			NewDir.Move("ContentResources");
			NewDir.Move("Texture");
			NewDir.Move("Map");
			GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("RealBackground.png").GetFullPath(), 1, 1);
		}	
		
	}*/
	Render0 = CreateComponent<GameEngineSpriteRenderer>();
	
	Render0->SetTexture("Background2.png");
	Render0->SetScaleToTexture("Background2.png");
	Render0->CameraCullingOn();
	MapSize = Render0->GetTransform()->GetLocalScale();
	MapRightP = { MapSize.x / 2.f,0.f };
	MapLeftP = { -MapSize.x / 2.f,0.f };
	MapUpP = { 0.f,MapSize.y / 2.f };
	MapDownP = { 0.f,-MapSize.y / 2.f };
	MapRatio = MapSize.x / MapSize.y;
	

}

// 이건 디버깅용도나 
void Map::Render(float _Delta)
{

};
