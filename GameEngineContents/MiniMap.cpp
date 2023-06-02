#include "PrecompileHeader.h"
#include "MiniMap.h"
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineUIRenderer.h>

MiniMap::MiniMap()
{
}

MiniMap::~MiniMap()
{
}
float4 MiniMap::MiniViewRatio;

void MiniMap::Update(float _DeltaTime)
{
	float4 m = { 1280.f,720.f};
	Render1->GetTransform()->SetLocalScale(m * MiniViewRatio);

	//Render1->GetTransform()->SetLocalScale({100,100});

	float4 s = Render1->GetTransform()->GetLocalScale();

}

void MiniMap::Start()
{


	
	Render0 = CreateComponent<GameEngineUIRenderer>();
	
	Render0->SetTexture("backgroundMini.png");
	
	Render0->GetTransform()->SetLocalScale({ (290.f), 120.f });
	
	Render1 = CreateComponent<GameEngineUIRenderer>();
	
	
	float4 a = GetTransform()->GetLocalScale();
	float4 b = Render1->GetTransform()->GetLocalScale();
	
	
}

// 이건 디버깅용도나 
void MiniMap::Render(float _Delta)
{

};
