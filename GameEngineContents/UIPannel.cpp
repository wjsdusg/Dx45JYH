#include "PrecompileHeader.h"
#include "UIPannel.h"
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

UIPannel::UIPannel()
{
}

UIPannel::~UIPannel()
{
}


void UIPannel::Update(float _DeltaTime)
{
	
	GetTransform()->SetLocalPosition(GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition());
	
	GetTransform()->AddLocalPosition({ 0,(-GameEngineWindow::GetScreenSize().y / 2.f)+80.f});

	
}

void UIPannel::Start()
{
	Render0 = CreateComponent<GameEngineSpriteRenderer>();
	
	//Render0->SetScaleToTexture("pannel.png");

	Render0->SetTexture("pannel.png");
	Render0->GetTransform()->SetLocalScale({ (GameEngineWindow::GetScreenSize().x ), 160.f, 0.f, 1.f });

	int s =Render0->GetOrder();


}

// 이건 디버깅용도나 
void UIPannel::Render(float _Delta)
{
	
};
