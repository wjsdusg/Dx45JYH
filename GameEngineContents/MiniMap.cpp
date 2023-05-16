#include "PrecompileHeader.h"
#include "MiniMap.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineVideo.h>
#include <GameEngineCore/GameEngineSprite.h>
#include "TestObject.h"

MiniMap::MiniMap()
{
}

MiniMap::~MiniMap()
{
}


void MiniMap::Update(float _DeltaTime)
{






}

void MiniMap::Start()
{
	Render0 = CreateComponent<GameEngineSpriteRenderer>();
	
	//Render0->SetTexture("background.png");
	Render0->SetTexture("hero.bmp");
	Render0->GetTransform()->SetLocalScale({ (200.f), 150.f});
	//Render0->GetTransform()->SetLocalPosition({ -GameEngineWindow::GetScreenSize().x,-GameEngineWindow::GetScreenSize().y });
	//Render0->SetOrder(50);
	int s =Render0->GetOrder();
}

// 이건 디버깅용도나 
void MiniMap::Render(float _Delta)
{

};
