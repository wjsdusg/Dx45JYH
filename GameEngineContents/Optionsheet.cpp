#include "PrecompileHeader.h"
#include "Optionsheet.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineFontUIRenderer.h>
#include <GameEngineCore/GameEngineFSM.h>
#include "ContentsEnum.h"
#include "Unit.h"
#include "Object.h"
#include "Hero.h"
#include "Karcher.h"
#include "Ksword.h"
#include "Mouse.h"
int Optionsheet::Count = 0;
Optionsheet::Optionsheet()
{
}

Optionsheet::~Optionsheet()
{
}


void Optionsheet::Update(float _DeltaTime)
{
	
	FSM.Update(_DeltaTime);
	if ( true == GameEngineInput::IsUp("F1"))
	{
		FSM.ChangeState("OpenNormalSheet");

	}
	
}

void Optionsheet::Start()
{

	if (nullptr == GameEngineSprite::Find("EpicText.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Optionsheet");
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("EpicText.png").GetFullPath(), 6, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("NomalText.png").GetFullPath(), 6, 1);
		
	}
	NewObject = CreateComponent<GameEngineComponent>();
	float4 SheetScale = { 300.f, 250.f, 1.f };
	
	{
		Render0 = CreateComponent<GameEngineUIRenderer>();
		Render0->CreateAnimation({ "OpenEpicText", "EpicText.png",0,5,0.1f,false });
		Render0->CreateAnimation({ "OpenNomalText", "NomalText.png",0,5,0.1f,false });
		Render0->GetTransform()->SetLocalScale(SheetScale);
		Render0->ChangeAnimation("OpenEpicText");
		Render0->GetTransform()->SetLocalPosition({ -350.f,0.f });
		Render0->Off();
		Render0Select = CreateComponent<GameEngineUIRenderer>();
		Render0Select->SetTexture("OptionSelect.png");
		Render0Select->GetTransform()->SetLocalScale(Render0->GetTransform()->GetLocalScale() * 0.9f);
		Render0Select->GetTransform()->SetLocalPosition({ -350.f,0.f });
		Render0Select->Off();
	}
	{
		Render1 = CreateComponent<GameEngineUIRenderer>();
		Render1->CreateAnimation({ "OpenEpicText", "EpicText.png",0,5,0.1f,false });
		Render1->CreateAnimation({ "OpenNomalText", "NomalText.png",0,5,0.1f,false });
		Render1->GetTransform()->SetLocalScale(SheetScale);
		Render1->ChangeAnimation("OpenEpicText");		
		Render1->Off();
		Render1Select = CreateComponent<GameEngineUIRenderer>();
		Render1Select->SetTexture("OptionSelect.png");
		Render1Select->GetTransform()->SetLocalScale(Render0->GetTransform()->GetLocalScale() * 0.9f);		
		Render1Select->Off();
	}
	{
		Render2 = CreateComponent<GameEngineUIRenderer>();
		Render2->CreateAnimation({ "OpenEpicText", "EpicText.png",0,5,0.1f,false });
		Render2->CreateAnimation({ "OpenNomalText", "NomalText.png",0,5,0.1f,false });
		Render2->GetTransform()->SetLocalScale(SheetScale);
		Render2->ChangeAnimation("OpenEpicText");
		Render2->GetTransform()->SetLocalPosition({ 350.f,0.f });
		Render2->Off();
		Render2Select = CreateComponent<GameEngineUIRenderer>();
		Render2Select->SetTexture("OptionSelect.png");
		Render2Select->GetTransform()->SetLocalScale(Render0->GetTransform()->GetLocalScale() * 0.9f);
		Render2Select->GetTransform()->SetLocalPosition({ 350.f,0.f });
		Render2Select->Off();
	}
	Collision = CreateComponent<GameEngineCollision>();
	Collision->SetOrder(static_cast<int>(ColEnum::UIPannel));
	Collision->SetColType(ColType::AABBBOX2D);
	ColRender = CreateComponent<GameEngineUIRenderer>();
	ColRender->SetSprite("Button.png", 2);
	ColRender->Off();
	{
		FontRender0 = CreateComponent<GameEngineFontUIRenderer>();		
		FontRender0->SetFont("휴먼둥근헤드라인");
		FontRender0->SetScale({ 20.f });
		FontRender0->SetColor({ 1.f,1.f,1.f });
		FontRender0->GetTransform()->SetLocalPosition({ -350.f,0.f });
		FontRender0->GetTransform()->AddLocalPosition({ -100.f,10.f });
		FontRender0->Off();
	}
	{
		FontRender1 = CreateComponent<GameEngineFontUIRenderer>();		
		FontRender1->SetFont("휴먼둥근헤드라인");
		FontRender1->SetScale({ 20.f });
		FontRender1->SetColor({ 1.f,1.f,1.f });
		FontRender1->GetTransform()->SetLocalPosition({ 0,0});
		FontRender1->GetTransform()->AddLocalPosition({ -100.f,10.f });
		FontRender1->Off();
	}
	{
		FontRender2 = CreateComponent<GameEngineFontUIRenderer>();		
		FontRender2->SetFont("휴먼둥근헤드라인");
		FontRender2->SetScale({ 20.f });		
		FontRender2->SetColor({ 1.f,1.f,1.f });
		FontRender2->GetTransform()->SetLocalPosition({ 350.f,0.f });
		FontRender2->GetTransform()->AddLocalPosition({ -100.f,10.f });
		FontRender2->Off();
	}

	FucntionsInit();
	FSMInit();
}

// 이건 디버깅용도나 
void Optionsheet::Render(float _Delta)
{

}

void Optionsheet::FSMInit()
{
	FSM.CreateState(
		{ .Name = "OpenNormalSheet",
		.Start = [this]()
		{
			Selectednumber.resize(3);
			Selectednumber[0] = -1;
			Selectednumber[1] = -1;
			Selectednumber[2] = -1;
			Selectednumber[0]=GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(Functions.size()) - 1);
			while (1)
			{
				int num = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(Functions.size()) - 1);
				if (Selectednumber[0] != num)
				{
					Selectednumber[1] = num;
					break;
				}
			}
			while (1)
			{
				int num = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(Functions.size()) - 1);
				if (Selectednumber[0] != num)
				{
					if (Selectednumber[1] != num)
					{
						Selectednumber[2] = num;
						break;
					}
					
				}
			}
			 Render0->On();			 
			 Render1->On();			 
			 Render2->On();
			 
			 Render0->ChangeAnimation("OpenNomalText");
			 Render1->ChangeAnimation("OpenNomalText");
			 Render2->ChangeAnimation("OpenNomalText");
			

		},
		.Update = [this](float _DeltaTime)
		{
			if (Render0->IsAnimationEnd())
			{
		
				Render0Select->On();
				Render1Select->On();
				Render2Select->On();
				FontRender0->On();
				FontRender1->On();
				FontRender2->On();
				FontRender0->SetText(OptionsString[Selectednumber[0]]);
				FontRender1->SetText(OptionsString[Selectednumber[1]]);
				FontRender2->SetText(OptionsString[Selectednumber[2]]);
			}
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
			//1번선택지
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
					int num = Selectednumber[0];
					Functions[num]();
					FSM.ChangeState("Default");
				}
			}
			//2번선택지
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
					int num = Selectednumber[1];
					Functions[num]();
					FSM.ChangeState("Default");
				}
			}
			//3번선택지
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
					int num = Selectednumber[2];
					Functions[num]();
					FSM.ChangeState("Default");
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
			Render0Select->Off();
			Render1Select->Off();
			Render2Select->Off();
			FontRender0->Off();
			FontRender1->Off();
			FontRender2->Off();
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

void  Optionsheet::FucntionsInit()
{
	Functions.push_back([]()
		{
			Object::AddATK += 1;
		});
	OptionsString.push_back("모든 유닛 공격력 +1");
	Functions.push_back([]() 
		{
			Object::AddATK += 2;
		});
	OptionsString.push_back("모든 유닛 공격력 +2");
	
	Functions.push_back([]() 
		{
			Object::AddHp += 5;
		});
	OptionsString.push_back("모든 유닛 체력 +5");

	Functions.push_back([]()
		{
			Object::AddHp += 10;
		});
	OptionsString.push_back("모든 유닛 체력 +10");

	Functions.push_back([]() 
		{
			Unit::AddSpeed += 5.f;
		});
	OptionsString.push_back("모든 유닛 이동속도 + 5");
	Functions.push_back([]()
		{
			Unit::AddSpeed += 10.f;
		});
	OptionsString.push_back("모든 유닛 이동속도 +10");

	Functions.push_back([]() 
		{
			Object::AddShield += 1;
		});
	OptionsString.push_back("모든 유닛 방어 +1");
	Functions.push_back([]()
		{
			Object::AddShield += 2;
		});
	OptionsString.push_back("모든 유닛 방어 +2");
	Functions.push_back([]() 
		{
			Object::AddAttackSpeed += 0.05f;
		});
	OptionsString.push_back("모든 유닛 공격속도 +5");
	Functions.push_back([]()
		{
			Object::AddAttackSpeed += 0.1f;
		});
	OptionsString.push_back("모든 유닛 공격속도 +10");

	Functions.push_back([]() 
		{
			Ksword::AddATK += 2;
		});
	OptionsString.push_back("창병 공격 +2");
	Functions.push_back([]()
		{
			Karcher::AddATK += 2;
		});
	OptionsString.push_back("궁병 공격 +2");
	Functions.push_back([]()
		{
			Hero::AddATK += 5;
		});
	OptionsString.push_back("영웅 공격 +5");
	
	EpicFunctions.push_back([]() 
		{
			
		});
	EpicOptionsString.push_back("5레벨 유닛을 획득");
	
	EpicFunctions.push_back([]()
		{

		});
	EpicOptionsString.push_back("매 라운드 10%이자 획득");

	EpicFunctions.push_back([]()
		{

		});
	EpicOptionsString.push_back("유닛 합성 대성공 확률10%증가");
}