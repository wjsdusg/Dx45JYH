#include "PrecompileHeader.h"
#include "DefenseMap.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

DefenseMap* DefenseMap::MainDefenseMap;
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
	MainDefenseMap = this;
	Render0 = CreateComponent<GameEngineSpriteRenderer>();

	Render0->SetTexture("defense.png");
	Render0->SetScaleToTexture("defense.png");
	Render0->CameraCullingOn();
	GetTransform()->SetLocalPosition({ MapRightP.x,MapDownP.y });
	GetTransform()->AddLocalPosition({- Render0->GetTransform()->GetLocalScale().x / 2,Render0->GetTransform()->GetLocalScale().y / 2 });

}

// 이건 디버깅용도나 
void DefenseMap::Render(float _Delta)
{

};
