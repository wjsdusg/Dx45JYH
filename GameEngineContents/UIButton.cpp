#include "PrecompileHeader.h"
#include "UIButton.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTileMapRenderer.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineFontRenderer.h>
#include "ContentsEnum.h"

UIButton* UIButton::MainUIButton=nullptr;

UIButton::UIButton()
{

}

UIButton::~UIButton()
{
}


void UIButton::Update(float _DeltaTime)
{
	
	FSM.Update(_DeltaTime);
}

void UIButton::Start()
{
	if (nullptr == GameEngineSprite::Find("button.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Button");
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("button.png").GetFullPath(), 17, 17);
	}	
	FSMInit();
	MainUIButton = this;
}


void UIButton::Render(float _DeltaTime)
{

}

void UIButton::FSMInit()
{
	FSM.CreateState(
		{ .Name = "UnitControl",
		.Start = [this]()
		{
			 Render0 = CreateComponent<GameEngineUIRenderer>();			
			 Render0->SetSprite("button.png", 39);
			 Render0->GetTransform()->SetLocalScale({ 50.f,42.f,1.f });
			 Render0->GetTransform()->AddLocalPosition({ 408.f,34.f });

			 Render1 = CreateComponent<GameEngineUIRenderer>();			
			 Render1->SetSprite("button.png", 6);
			 Render1->GetTransform()->SetLocalScale({ 50.f,42.f,1.f });
			 Render1->GetTransform()->AddLocalPosition({ 408.f + x,34.f });

			 Render2 = CreateComponent<GameEngineUIRenderer>();			
			 Render2->SetSprite("button.png", 4);
			 Render2->GetTransform()->SetLocalScale({ 50.f,42.f,1.f });
			 Render2->GetTransform()->AddLocalPosition({ 405.f + x * 2,34.f });

			 Render3 = CreateComponent<GameEngineUIRenderer>();			 
			 Render3->SetSprite("button.png", 10);
			 Render3->GetTransform()->SetLocalScale({ 50.f,42.f,1.f });
			 Render3->GetTransform()->AddLocalPosition({ 405.f + x * 3,34.f });

			 Render4 = CreateComponent<GameEngineUIRenderer>();			 
			 Render4->SetSprite("button.png", 35);
			 Render4->GetTransform()->SetLocalScale({ 50.f,42.f,1.f });
			 Render4->GetTransform()->AddLocalPosition({ 408.f,34.f - y });
			 
			 ColRender= CreateComponent<GameEngineUIRenderer>();
			 ColRender->SetSprite("Button.png", 2);
			 ColRender->Off();
		},
		.Update = [this](float _DeltaTime)
		{
			GameEngineCamera* Camera = GetLevel()->GetCamera(100).get();
			float4 Mouse = GameEngineInput::GetMousePosition();
			// ·£´õ·¯ 
			float4x4 ViewPort = Camera->GetViewPort();
			float4x4 Proj = Camera->GetProjection();
			float4x4 View = Camera->GetView();
			Mouse *= ViewPort.InverseReturn();
			Mouse *= Proj.InverseReturn();
			Mouse *= View.InverseReturn();
			CollisionData MouseData;
			MouseData.SPHERE.Center = Mouse.DirectFloat3;			
			MouseData.SPHERE.Radius = 0.0f;
			CollisionData asd = Render0->GetTransform()->GetCollisionData();
				int a = 0;
			if (true == GameEngineTransform::AABB2DToSpehre2D(Render0->GetTransform()->GetCollisionData(), MouseData))
			{
				ColRender->On();
				ColRender->GetTransform()->SetLocalScale(Render0->GetTransform()->GetLocalScale());
				ColRender->GetTransform()->SetLocalPosition(Render0->GetTransform()->GetLocalPosition());
			}
			else if (true == GameEngineTransform::AABB2DToSpehre2D(Render1->GetTransform()->GetCollisionData(), MouseData))
			{
				ColRender->On();
				ColRender->GetTransform()->SetLocalScale(Render1->GetTransform()->GetLocalScale());
				ColRender->GetTransform()->SetLocalPosition(Render1->GetTransform()->GetLocalPosition());
			}
			else if (true == GameEngineTransform::AABB2DToSpehre2D(Render2->GetTransform()->GetCollisionData(), MouseData))
			{
				ColRender->On();
				ColRender->GetTransform()->SetLocalScale(Render2->GetTransform()->GetLocalScale());
				ColRender->GetTransform()->SetLocalPosition(Render2->GetTransform()->GetLocalPosition());
			}
			else if (true == GameEngineTransform::AABB2DToSpehre2D(Render3->GetTransform()->GetCollisionData(), MouseData))
			{
				ColRender->On();
				ColRender->GetTransform()->SetLocalScale(Render3->GetTransform()->GetLocalScale());
				ColRender->GetTransform()->SetLocalPosition(Render3->GetTransform()->GetLocalPosition());
			}
			else if (true == GameEngineTransform::AABB2DToSpehre2D(Render4->GetTransform()->GetCollisionData(), MouseData))
			{
				ColRender->On();
				ColRender->GetTransform()->SetLocalScale(Render4->GetTransform()->GetLocalScale());
				ColRender->GetTransform()->SetLocalPosition(Render4->GetTransform()->GetLocalPosition());
			}
			else 
			{
				ColRender->Off();
			}
		},
		.End = [this]()
		{
			Render0->Death();
			Render0 = nullptr;
			Render1->Death();
			Render1 = nullptr;
			Render2->Death();
			Render2 = nullptr;
			Render3->Death();
			Render3 = nullptr;
			Render4->Death();
			Render4 = nullptr;
		}
		}
	);
	FSM.CreateState(
		{ .Name = "Default",
		.Start = [this]() {},
		.Update = [this](float _DeltaTime) {}
		,
		.End = []() {}
		}
	);
	FSM.ChangeState("UnitControl");
}