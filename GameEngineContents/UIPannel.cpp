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
	
	GameEngineTransform* g = GetTransform();

	int a = 0;
}

void UIPannel::Start()
{
	Render0 = CreateComponent<GameEngineSpriteRenderer>();
	
	Render0->SetScaleToTexture("pannel.png");

	Render0->SetTexture("pannel.png");
	//Render0->GetTransform()->SetLocalScale({ (GameEngineWindow::GetScreenSize().x ), (GameEngineWindow::GetScreenSize().y /5), 0.f, 1.f });




}

// 이건 디버깅용도나 
void UIPannel::Render(float _Delta)
{
	
};
