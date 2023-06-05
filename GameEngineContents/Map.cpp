#include "PrecompileHeader.h"
#include "Map.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"

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
void Map::Update(float _DeltaTime)
{


	std::vector<std::shared_ptr<GameEngineCollision>> ColTest;

	

}

void Map::Start()
{
	Render0 = CreateComponent<GameEngineSpriteRenderer>();
	
	Render0->SetTexture("background.png");
	Render0->SetScaleToTexture("background.png");
	MapSize = Render0->GetTransform()->GetLocalScale();
	MapRightP = { MapSize.x / 2.f,0.f,1.f };
	MapLeftP = { -MapSize.x / 2.f,0.f,1.f };
	MapUpP = { 0.f,MapSize.y / 2.f,1.f };
	MapDownP = { 0.f,-MapSize.y / 2.f,1.f };

}

// 이건 디버깅용도나 
void Map::Render(float _Delta)
{

};
