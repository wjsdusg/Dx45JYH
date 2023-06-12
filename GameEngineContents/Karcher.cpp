#include "PrecompileHeader.h"
#include "Karcher.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "ContentsEnum.h"
#include "MapOverlay.h"
extern float4 MainMouse;
extern  float CalAngle1To2(float4 _Pos1, float4 _Pos2);
Karcher::Karcher()
{
}

Karcher::~Karcher()
{
}


void Karcher::Update(float _DeltaTime)
{
	Unit::Update(_DeltaTime);


	if (true == IsClick)
	{
		if (nullptr == SelectionCircle)
		{
			SelectionCircle = CreateComponent<GameEngineSpriteRenderer>();
			SelectionCircle->GetTransform()->SetLocalPosition({ 0,-20.f });

			SelectionCircle->GetTransform()->SetLocalScale({ 10.f,10.f });
		}
	}
	if (false == IsClick)
	{
		if (nullptr != SelectionCircle)
		{
			SelectionCircle->Death();
			SelectionCircle = nullptr;

		}
	}

	if (true == GameEngineInput::IsUp("EngineMouseRight") && true == IsClick)
	{
		MousePickPos = MainMouse;
		IsMove = true;
	}

	if (MousePickPos.XYDistance(GetTransform()->GetLocalPosition()) <= 2.f)
	{
		IsMove = false;
	}
	if (true == IsMove)
	{
		GetTransform()->AddLocalPosition(MovePointTowardsTarget(GetTransform()->GetLocalPosition(), MousePickPos, Speed, _DeltaTime));
	}



}

void Karcher::Start()
{
	Unit::Start();
	GetTransform()->AddLocalPosition({ 0.f,-200.f });
	//MousePickPos = GetTransform()->GetLocalPosition();
	if (nullptr == GameEngineSprite::Find("archerk"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Unit");
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("archerk.png").GetFullPath(), 16, 11);
	}
	Render0 = CreateComponent<GameEngineSpriteRenderer>();

	Render0->GetTransform()->SetLocalScale({ 40.f,40.f });
	//Render0->CreateAnimation({ .AnimationName = "Move", .SpriteName = "archerk.png", .ScaleToTexture = false });
	Render0->CreateAnimation({ "Move", "archerk.png",0,5,0.1});
	Render0->CreateAnimation({ "Attack", "archerk.png",6,11,0.1 });
	Render0->ChangeAnimation("Move");
	//MainRenderer->CreateAnimation({ "Win", "TestAnimation.png", 0, 5, 0.1f, true, true });
	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform()->SetLocalScale({ 40.f,40.f });
	Collision->SetOrder(static_cast<int>(ColEnum::Unit));
}

// 이건 디버깅용도나 
void Karcher::Render(float _Delta)
{

};
