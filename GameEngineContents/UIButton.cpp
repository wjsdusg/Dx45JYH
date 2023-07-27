#include "PrecompileHeader.h"
#include "UIButton.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineFontRenderer.h>
#include <GameEngineCore/GameEngineFSM.h>
#include "ContentsEnum.h"
#include "Unit.h"
#include "Mouse.h"
#include "Barrack.h"
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
	//44
	FSMInit();
	MainUIButton = this;
	Render0 = CreateComponent<GameEngineUIRenderer>();
	Render0->SetSprite("button.png", 39);
	Render1 = CreateComponent<GameEngineUIRenderer>();
	Render1->SetSprite("button.png", 6);
	Render2 = CreateComponent<GameEngineUIRenderer>();
	Render2->SetSprite("button.png", 4);
	Render3 = CreateComponent<GameEngineUIRenderer>();
	Render3->SetSprite("button.png", 10);
	Render4 = CreateComponent<GameEngineUIRenderer>();
	Render4->SetSprite("button.png", 35);
	Render5 = CreateComponent<GameEngineUIRenderer>();
	Render5->SetSprite("button.png", 44);
	ColRender = CreateComponent<GameEngineUIRenderer>();
	Collision = CreateComponent<GameEngineCollision>();
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
			 Render0->On();
			 Render0->GetTransform()->SetLocalScale({ 50.f,42.f,1.f });
			 Render0->GetTransform()->SetLocalPosition({ 408.f,34.f });
			 Render1->On();
			 Render1->GetTransform()->SetLocalScale({ 50.f,42.f,1.f });
			 Render1->GetTransform()->SetLocalPosition({ 408.f + x,34.f });
			 Render2->On();
			 Render2->GetTransform()->SetLocalScale({ 50.f,42.f,1.f });
			 Render2->GetTransform()->SetLocalPosition({ 405.f + x * 2,34.f });
			 Render3->On();
			 Render3->GetTransform()->SetLocalScale({ 50.f,42.f,1.f });
			 Render3->GetTransform()->SetLocalPosition({ 405.f + x * 3,34.f });
			 Render4->On();
			 Render4->GetTransform()->SetLocalScale({ 50.f,42.f,1.f });
			 Render4->GetTransform()->SetLocalPosition({ 408.f,34.f - y });
			 Render4->Off();
			 
			 ColRender->SetSprite("Button.png", 2);
			 ColRender->Off();
		},
		.Update = [this](float _DeltaTime)
		{
			
			GameEngineCamera* Camera = GetLevel()->GetCamera(100).get();
			float4 Mouse = GameEngineInput::GetMousePosition();
			// 랜더러 
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
			//스탑
			if (true == GameEngineTransform::AABB2DToSpehre2D(Render0->GetTransform()->GetCollisionData(), MouseData))
			{
				ColRender->On();
				Collision->On();
				ColRender->GetTransform()->SetLocalScale(Render0->GetTransform()->GetLocalScale());
				ColRender->GetTransform()->SetLocalPosition(Render0->GetTransform()->GetLocalPosition());
				Collision->GetTransform()->SetLocalScale(Render0->GetTransform()->GetLocalScale());
				Collision->GetTransform()->SetLocalPosition(Render0->GetTransform()->GetLocalPosition());
				if (true == GameEngineInput::IsUp("EngineMouseLeft"))
				{
					std::vector<std::shared_ptr<Unit>> Units = Unit::GetUnits();
					for (auto Start = Units.begin(); Start != Units.end(); Start++)
					{
						if (true == (*Start)->GetIsClick())
						{
							(*Start)->FSM.ChangeState("Stay");
							Mouse::NewMainMouse->FSM.ChangeState("UnitsClick");
						}
					}				
				}
			}
			//이동
			else if (true == GameEngineTransform::AABB2DToSpehre2D(Render1->GetTransform()->GetCollisionData(), MouseData))
			{
				ColRender->On();
				Collision->On();
				ColRender->GetTransform()->SetLocalScale(Render1->GetTransform()->GetLocalScale());
				ColRender->GetTransform()->SetLocalPosition(Render1->GetTransform()->GetLocalPosition());
				Collision->GetTransform()->SetLocalScale(Render1->GetTransform()->GetLocalScale());
				Collision->GetTransform()->SetLocalPosition(Render1->GetTransform()->GetLocalPosition());
				if (true == GameEngineInput::IsUp("EngineMouseLeft"))
				{
					Mouse::NewMainMouse->FSM.ChangeState("UnitClickMove");
				}
			}
			//공격
			else if (true == GameEngineTransform::AABB2DToSpehre2D(Render2->GetTransform()->GetCollisionData(), MouseData))
			{
				ColRender->On();
				Collision->On();
				ColRender->GetTransform()->SetLocalScale(Render2->GetTransform()->GetLocalScale());
				ColRender->GetTransform()->SetLocalPosition(Render2->GetTransform()->GetLocalPosition());
				Collision->GetTransform()->SetLocalScale(Render2->GetTransform()->GetLocalScale());
				Collision->GetTransform()->SetLocalPosition(Render2->GetTransform()->GetLocalPosition());
				if (true == GameEngineInput::IsUp("EngineMouseLeft"))
				{
					Mouse::NewMainMouse->FSM.ChangeState("UnitClickAttack");
				}
			}
			//패트롤
			else if (true == GameEngineTransform::AABB2DToSpehre2D(Render3->GetTransform()->GetCollisionData(), MouseData))
			{
				ColRender->On();
				Collision->On();
				ColRender->GetTransform()->SetLocalScale(Render3->GetTransform()->GetLocalScale());
				ColRender->GetTransform()->SetLocalPosition(Render3->GetTransform()->GetLocalPosition());
				Collision->GetTransform()->SetLocalScale(Render3->GetTransform()->GetLocalScale());
				Collision->GetTransform()->SetLocalPosition(Render3->GetTransform()->GetLocalPosition());
				if (true == GameEngineInput::IsUp("EngineMouseLeft"))
				{
					Mouse::NewMainMouse->FSM.ChangeState("UnitClickPatrol");
				}
			}
			//홀드
			else if (true == GameEngineTransform::AABB2DToSpehre2D(Render4->GetTransform()->GetCollisionData(), MouseData))
			{
				ColRender->On();
				Collision->On();
				ColRender->GetTransform()->SetLocalScale(Render4->GetTransform()->GetLocalScale());
				ColRender->GetTransform()->SetLocalPosition(Render4->GetTransform()->GetLocalPosition());
				Collision->GetTransform()->SetLocalScale(Render4->GetTransform()->GetLocalScale());
				Collision->GetTransform()->SetLocalPosition(Render4->GetTransform()->GetLocalPosition());
				if (true == GameEngineInput::IsUp("EngineMouseLeft"))
				{
					std::vector<std::shared_ptr<Unit>> Units = Unit::GetUnits();
					for (auto Start = Units.begin(); Start != Units.end(); Start++)
					{
						if (true == (*Start)->GetIsClick())
						{
							(*Start)->IsHold = true;
							(*Start)->FSM.ChangeState("HoldAttack");
						}
					}

				}
			}
			else 
			{
				ColRender->Off();
				Collision->Off();
			}

		},
		.End = [this]()
		{
			Render0->Off();			
			Render1->Off();			
			Render2->Off();			
			Render3->Off();			
			Render4->Off();
			ColRender->Off();
			Collision->Off();
			
		}
		}
	);

	FSM.CreateState(
		{ .Name = "BuildingControl",
		.Start = [this]()
		{
			 Render5->On();
			 Render5->GetTransform()->SetLocalScale({ 50.f,42.f,1.f });
			 Render5->GetTransform()->SetLocalPosition({ 408.f,34.f });		 

			 ColRender->SetSprite("Button.png", 2);
			 ColRender->Off();
		},
		.Update = [this](float _DeltaTime)
		{

			GameEngineCamera* Camera = GetLevel()->GetCamera(100).get();
			float4 Mouse = GameEngineInput::GetMousePosition();
			// 랜더러 
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
			//스탑
			if (true == GameEngineTransform::AABB2DToSpehre2D(Render5->GetTransform()->GetCollisionData(), MouseData))
			{
				ColRender->On();
				Collision->On();
				ColRender->GetTransform()->SetLocalScale(Render5->GetTransform()->GetLocalScale());
				ColRender->GetTransform()->SetLocalPosition(Render5->GetTransform()->GetLocalPosition());
				Collision->GetTransform()->SetLocalScale(Render5->GetTransform()->GetLocalScale());
				Collision->GetTransform()->SetLocalPosition(Render5->GetTransform()->GetLocalPosition());
				if (true == GameEngineInput::IsUp("EngineMouseLeft"))
				{
					Barrack::MainBarrack->TransunitToMap();
				}
			}			
			else
			{
				ColRender->Off();
				Collision->Off();
			}

		},
		.End = [this]()
		{			
			Render5->Off();
			ColRender->Off();
			Collision->Off();

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
	FSM.ChangeState("Default");
}