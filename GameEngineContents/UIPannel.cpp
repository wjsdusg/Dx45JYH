#include "PrecompileHeader.h"
#include "UIPannel.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
UIPannel::UIPannel()
{
}

UIPannel::~UIPannel()
{
}


void UIPannel::Update(float _DeltaTime)
{
	
	NewObject->GetTransform()->SetLocalPosition(GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition());
	
}

void UIPannel::Start()
{
	std::shared_ptr<class GameEngineUIRenderer> Render0;


	std::shared_ptr<class GameEngineCollision> Collsion;

	Render0 = CreateComponent<GameEngineUIRenderer>();
	
	//Render0->SetScaleToTexture("pannel.png");
	//GetTransform()->SetLocalScale({ (GameEngineWindow::GetScreenSize().x), 50.f, 0.f, 1.f });

	Render0->SetTexture("pannel.png");
	Render0->GetTransform()->SetLocalScale({ (GameEngineWindow::GetScreenSize().x ), 180.f, 1.f});

	GetTransform()->SetLocalPosition(GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition());

	GetTransform()->AddLocalPosition({ 0,(-GameEngineWindow::GetScreenSize().y / 2.f) + 90.f });

	Collision = CreateComponent<GameEngineCollision>();	
	Collision->SetOrder(static_cast<int>(ColEnum::UIPannel));
	Collision->SetColType(ColType::AABBBOX2D);

	NewObject = CreateComponent<GameEngineComponent>();
	Collision->GetTransform()->SetParent(NewObject->GetTransform());
	Collision->GetTransform()->SetLocalScale(Render0->GetTransform()->GetLocalScale());
}

// 이건 디버깅용도나 
void UIPannel::Render(float _Delta)
{
	
};
