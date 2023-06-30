#include "PrecompileHeader.h"
#include "Mouse.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
#include "Unit.h"
Mouse* Mouse::NewMainMouse;
extern float4 MainMouse;
Mouse::Mouse()
{
	NewMainMouse = this;
}

Mouse::~Mouse()
{
}


void Mouse::Update(float _DeltaTime)
{
	{
		std::shared_ptr<GameEngineCamera> Camera = GetLevel()->GetCamera(100);

		// 랜더러 
		float4x4 ViewPort = Camera->GetViewPort();
		float4x4 Proj = Camera->GetProjection();
		float4x4 View = Camera->GetView();
		
		float4 Pos = float4::Zero;
		Pos = GameEngineInput::GetMousePosition();
		Pos *= ViewPort.InverseReturn();
		Pos *= Proj.InverseReturn();
		Pos *= View.InverseReturn();
		
		Pos.x += Render0->GetTransform()->GetLocalScale().x/2;
		Pos.y -= Render0->GetTransform()->GetLocalScale().y/2;
		Pos.z = -1.f;
		Render0->GetTransform()->SetLocalPosition(Pos);
	}
	{
		std::shared_ptr<GameEngineCamera> Camera = GetLevel()->GetMainCamera();

		// 랜더러 
		float4x4 ViewPort = Camera->GetViewPort();
		float4x4 Proj = Camera->GetProjection();
		float4x4 View = Camera->GetView();

		float4 Pos = float4::Zero;
		Pos = GameEngineInput::GetMousePosition();
		Pos *= ViewPort.InverseReturn();
		Pos *= Proj.InverseReturn();
		Pos *= View.InverseReturn();
		Collision->GetTransform()->SetLocalPosition(Pos);
		
	}
	MouseData.SPHERE.Center = MainMouse.DirectFloat3;
	MouseData.SPHERE.Radius = 0.0f;

	float MinDIstance = 1000.f;
	
	
	std::vector<std::shared_ptr<GameEngineCollision>> ColTest;
	if (Collision->CollisionAll(static_cast<int>(ColEnum::Unit), ColTest, ColType::SPHERE2D, ColType::AABBBOX2D), 0 != ColTest.size())
	{
		if (AnimationEnd == false)
		{
			Render0->ChangeAnimation("MyTeamCusor");
			AnimationEnd = true;
		}		
		if (true == GameEngineInput::IsUp("EngineMouseLeft"))
		{
			if (nullptr != CopyUnit && true == CopyUnit->GetIsClick() && DoubleClickTimer < 0.5f)
			{
				std::vector<std::shared_ptr<Unit>> Units = Unit::GetUnits();
				for (auto Start = Units.begin(); Start != Units.end(); Start++)
				{
					(*Start)->SetIsClick(true);
				}
			}
			else
			{
				for (std::shared_ptr<GameEngineCollision> Col : ColTest)
				{
					std::shared_ptr<Unit> NewUnit = Col->GetActor()->DynamicThis<Unit>();
					if (nullptr == NewUnit)
					{
						continue;
					}
					if (MinDIstance > GetTransform()->GetLocalPosition().XYDistance(NewUnit->GetTransform()->GetLocalPosition()))
					{
						MinDIstance = GetTransform()->GetLocalPosition().XYDistance(NewUnit->GetTransform()->GetLocalPosition());
						CopyUnit = NewUnit;
					}
				}
				if (nullptr != CopyUnit)
				{
					std::vector<std::shared_ptr<Unit>> Units = Unit::GetUnits();
					for (auto Start = Units.begin(); Start != Units.end(); Start++)
					{
						(*Start)->SetIsClick(false);
					}
					CopyUnit->SetIsClick(true);
					DoubleClickTimer = 0.f;
				}
			}
		}			
	}
	else
	{
		
		Render0->ChangeAnimation("Default");
	}
	if (nullptr!= CopyUnit&&CopyUnit->GetIsClick() == true)
	{
		DoubleClickTimer += _DeltaTime;
	}
	if(false==Collision->CollisionAll(static_cast<int>(ColEnum::Unit), ColTest, ColType::SPHERE2D, ColType::AABBBOX2D)&& true == GameEngineInput::IsUp("EngineMouseLeft"))
	{
		if (nullptr != CopyUnit)
		{
			
			std::vector<std::shared_ptr<Unit>> Units = Unit::GetUnits();
			for (auto Start = Units.begin(); Start != Units.end(); Start++)
			{
				(*Start)->SetIsClick(false);
			}
			CopyUnit = nullptr;
		}

	}

	if (Render0->IsAnimationEnd())
	{
		AnimationEnd = false;
	}
	if (true == MouseMarkRender->IsAnimationEnd())
	{
		MouseMarkRender->Off();		
	}
}

void Mouse::Start()
{
	//GameEngineInput::MouseCursorOff();

	if (nullptr == GameEngineSprite::Find("movemark.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Mouse");
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("movemark.png").GetFullPath(), 14, 1);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("mouse.png").GetFullPath(),20,10);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("eventmark.png").GetFullPath(), 10,10);
	}
	Render0 = CreateComponent<GameEngineUIRenderer>(1);
	MouseMarkRender = CreateComponent<GameEngineSpriteRenderer>();
	Render0->GetTransform()->SetLocalScale({ 40.f,40.f,1.f });

	MouseMarkRender->CreateAnimation({ "Mark", "movemark.png",1,13,0.05f,false });
	MouseMarkRender->ChangeAnimation("Mark");

	Render0->CreateAnimation({ "LDown45Move", "mouse.png",21,21 });
	Render0->CreateAnimation({ "LMove", "mouse.png",22,22 });
	Render0->CreateAnimation({ "LUp45Move", "mouse.png",23,23 });
	Render0->CreateAnimation({ "UpMove", "mouse.png",24,24 });
	Render0->CreateAnimation({ "DownMove", "mouse.png",20,20 });
	Render0->CreateAnimation({ "RDown45Move", "mouse.png",27,27 });
	Render0->CreateAnimation({ "RMove", "mouse.png",26,26 });
	Render0->CreateAnimation({ "RUp45Move", "mouse.png",25,25 });

	Render0->CreateAnimation({ "MyTeamCusor", "mouse.png",0,3, });
	Render0->CreateAnimation({ "EnemyCursor", "eventmark.png",0,3, });
	Render0->CreateAnimation({ "AClick", "mouse.png",60,60 });
	Render0->CreateAnimation({ "Default", "mouse.png",80,80 });
	Render0->CreateAnimation({ "DefaultClcik", "mouse.png",80,81,});
	Render0->CreateAnimation({ "MClick", "mouse.png",100,100 });
	Render0->ChangeAnimation("Default");

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform()->SetLocalScale({ 1.f,1.f,1.f });
	Collision->SetOrder(static_cast<int>(ColEnum::Mouse));
	
}

void Mouse::GetMoveMark(float4 _Pos)
{
	MouseMarkRender->On();
	MouseMarkRender->ChangeAnimation("Mark");
	MouseMarkRender->GetTransform()->SetLocalScale({ 40.f,40.f,1.f });
	MouseMarkRender->GetTransform()->SetWorldPosition(_Pos);
	
}

void Mouse::Render(float _DeltaTime)
{

}