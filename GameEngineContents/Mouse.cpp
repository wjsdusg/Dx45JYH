#include "PrecompileHeader.h"
#include "Mouse.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
Mouse* Mouse::MainMouse;
Mouse::Mouse()
{

}

Mouse::~Mouse()
{
}


void Mouse::Update(float _DeltaTime)
{
	{
		std::shared_ptr<GameEngineCamera> Camera = GetLevel()->GetMainCamera();

		// ·£´õ·¯ 
		float4x4 ViewPort = Camera->GetViewPort();
		float4x4 Proj = Camera->GetProjection();
		float4x4 View = Camera->GetView();
		
		float4 Pos = float4::Zero;
		Pos = GameEngineInput::GetMousePosition();
		Pos *= ViewPort.InverseReturn();
		Pos *= Proj.InverseReturn();
		Pos *= View.InverseReturn();
		GetTransform()->SetLocalPosition(Pos);
	}
}

void Mouse::Start()
{
	GameEngineInput::MouseCursorOff();

	if (nullptr == GameEngineSprite::Find("movemark.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Mouse");
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("movemark.png").GetFullPath(), 14, 1);

	}
	Render0 = CreateComponent<GameEngineSpriteRenderer>();

	Render0->GetTransform()->SetLocalScale({ 80.f,80.f,1.f });

	Render0->CreateAnimation({ "Mark", "movemark.png",1,13 });
	
	Render0->ChangeAnimation("Mark");

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform()->SetLocalScale({ 30.f,30.f,1.f });
	Collision->SetOrder(static_cast<int>(ColEnum::Mouse));
	
}


void Mouse::Render(float _DeltaTime)
{

}