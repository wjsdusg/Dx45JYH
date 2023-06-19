#include "PrecompileHeader.h"
#include "MiniMap.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineButton.h>
#include <GameEngineCore/GameEngineTileMapRenderer.h>
MiniMap::MiniMap()
{
}

MiniMap::~MiniMap()
{
}
extern float MapRatio;
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
extern int CalculateSideRhombusCount();
extern int gcd(int a, int b);
extern float4 IsoTileScale;

 MiniMap* MiniMap::MainMiniMap=nullptr;

void MiniMap::Update(float _DeltaTime)
{
	
	Render1->GetTransform()->SetLocalScale(GameEngineWindow::GetScreenSize() * MiniViewRatio);
	Render1->GetTransform()->SetLocalPosition(GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition() * MiniViewRatio);
	
	
	float4 s = Render1->GetTransform()->GetLocalScale();

}

void MiniMap::Start()
{
	
	MainMiniMap = this;
	
	Render0 = CreateComponent<GameEngineUIRenderer>();
	
	Render0->SetTexture("backgroundMini.png");
	
	Render0->GetTransform()->SetLocalScale({ 270.f, 120.f });
	
	MiniMapSize = Render0->GetTransform()->GetLocalScale();
	
	Render1 = CreateComponent<GameEngineUIRenderer>();
	
	//MiniMapOverlay = CreateComponent<GameEngineUIRenderer>();
	//
	////MiniMapOverlay->GetTransform()->SetParent(Render0->GetTransform());
	//MiniMapOverlay->GetTransform()->SetLocalScale({ 270.f, 120.f });
	//MiniMapOverlay->SetTexture("BlackMini.png");
	
}

// 이건 디버깅용도나 
void MiniMap::Render(float _Delta)
{

};
