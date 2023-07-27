#include "PrecompileHeader.h"
#include "DefenseMap.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "MiniMap.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
DefenseMap* DefenseMap::MainDefenseMap;
extern float4 MiniViewRatio;
DefenseMap::DefenseMap()
{
}

DefenseMap::~DefenseMap()
{
}


extern float4 MapRightP;
extern float4 MapLeftP;
extern float4 MapUpP;
extern float4 MapDownP;

void DefenseMap::Update(float _DeltaTime)
{



}

void DefenseMap::Start()
{

	MainDefenseMap = this;
	Render0 = CreateComponent<GameEngineSpriteRenderer>();

	Render0->SetTexture("defense.png");
	Render0->SetScaleToTexture("defense.png");
	Render0->CameraCullingOn();
	GetTransform()->SetLocalPosition({ MapRightP.x,MapDownP.y });
	GetTransform()->AddLocalPosition({- Render0->GetTransform()->GetLocalScale().x / 2,Render0->GetTransform()->GetLocalScale().y / 2 });
	float4 Pos = MiniMap::MainMiniMap->Render0->GetTransform()->GetWorldPosition();
	Pos += GetTransform()->GetWorldPosition() * MiniViewRatio;
	
	Render1 = CreateComponent<GameEngineUIRenderer>();
	Render1->SetTexture("defense.png");
	Render1->GetTransform()->SetLocalScale({ 44,22 });
	Render1->GetTransform()->SetWorldPosition(Pos);
	Render1->SetOrder(-10);
}

// 이건 디버깅용도나 
void DefenseMap::Render(float _Delta)
{

};
