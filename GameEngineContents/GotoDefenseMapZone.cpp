#include "PrecompileHeader.h"
#include "GotoDefenseMapZone.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineFontRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "ContentsEnum.h"

#include "MapEditor.h"
#include "Barrack.h"
extern float4 MainMouse;
extern  float CalAngle1To2(float4 _Pos1, float4 _Pos2);

GotoDefenseMapZone::GotoDefenseMapZone()
{
}

GotoDefenseMapZone::~GotoDefenseMapZone()
{
}


void GotoDefenseMapZone::Update(float _DeltaTime)
{
	
	std::vector<std::shared_ptr<GameEngineCollision>> ColTest;
	if (Collision->CollisionAll(static_cast<int>(ColEnum::Unit), ColTest, ColType::SPHERE2D, ColType::AABBBOX2D)
		&& 0 != ColTest.size()
		)
	{
		Time += _DeltaTime;
	}
	if (Time > 5.f)
	{
		Barrack::MainBarrack->GotoDenFensceMap();
		Death();
	}
}
//
void GotoDefenseMapZone::Start()
{
	
	if (nullptr == GameEngineSprite::Find("Comeback"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Comeback").GetFullPath());
		
	}

	Render0 = CreateComponent<GameEngineSpriteRenderer>();
	Render0->CreateAnimation({ .AnimationName = "Comeback", .SpriteName = "Comeback",.Loop = true,.ScaleToTexture = false });
	Render0->ChangeAnimation("Comeback");
	Render0->GetTransform()->SetLocalScale({ 700.f,480.f });
	
	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform()->SetLocalScale({ 600.f,400.f });
	Collision->SetOrder(static_cast<int>(ColEnum::Player));



}

// 이건 디버깅용도나 
void GotoDefenseMapZone::Render(float _Delta)
{

};
