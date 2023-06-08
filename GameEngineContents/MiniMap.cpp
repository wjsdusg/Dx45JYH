#include "PrecompileHeader.h"
#include "MiniMap.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineButton.h>
MiniMap::MiniMap()
{
}

MiniMap::~MiniMap()
{
}
extern float4 MiniViewRatio;
extern float4 MiniMapSize;
void MiniMap::Update(float _DeltaTime)
{
	
	Render1->GetTransform()->SetLocalScale(GameEngineWindow::GetScreenSize() * MiniViewRatio);
	Render1->GetTransform()->SetLocalPosition(GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition() * MiniViewRatio);
	
	
	float4 s = Render1->GetTransform()->GetLocalScale();

}

void MiniMap::Start()
{
	

	
	Render0 = CreateComponent<GameEngineUIRenderer>();
	
	Render0->SetTexture("backgroundMini.png");
	
	Render0->GetTransform()->SetLocalScale({ 290.f, 120.f });
	
	MiniMapSize = Render0->GetTransform()->GetLocalScale();
	
	Render1 = CreateComponent<GameEngineUIRenderer>();
	
	
	float4 a = GetTransform()->GetLocalScale();
	float4 b = Render1->GetTransform()->GetLocalScale();
	

}

// 이건 디버깅용도나 
void MiniMap::Render(float _Delta)
{

};
