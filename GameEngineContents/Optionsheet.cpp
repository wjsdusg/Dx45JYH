#include "PrecompileHeader.h"
#include "Optionsheet.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineFontUIRenderer.h>
#include "ContentsEnum.h"
#include "Unit.h"
#include "Object.h"
#include "Hero.h"
#include "Karcher.h"
#include "Ksword.h"

int Optionsheet::Count = 0;
Optionsheet::Optionsheet()
{
}

Optionsheet::~Optionsheet()
{
}


void Optionsheet::Update(float _DeltaTime)
{

	if (Render0->IsAnimationEnd())
	{
		
		Render0Select->On();
		Render1Select->On();
		Render2Select->On();
		/*std::string str3 = MapEditor::ConvertPosToTileXY(ShortTargetPos).ToString();
		std::string str4 =std::to_string(TestDistance);
		str3 += "\n";
		str3 += str4;*/		
		FontRender0->SetText(OptionsString[0]);
	}
	/*if (GameEngineInput::IsUp("EngineMouseLeft"))
	{
		Render1->Off();
		Render1Select->Off();
	}*/
	float4 asdadssds =Render0->GetTransform()->GetWorldPosition();
	//Render0->GetTransform()->AddLocalPosition({ 1.f, 1.f });
	float4 asdads = FontRender0->GetTransform()->GetWorldPosition();
	float4 asdads2 = FontRender0->GetTransform()->GetWorldScale();
	Render0->GetTransform()->SetLocalPosition({ -350.f,0.f });
	FontRender0->GetTransform()->SetLocalPosition({ 0.f,0.f });
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
		Render0->GetTransform()->SetLocalScale(SheetScale);
		Render0->ChangeAnimation("OpenEpicText");
		Render0->GetTransform()->SetLocalPosition({ -350.f,0.f });
		Render0Select = CreateComponent<GameEngineUIRenderer>();
		Render0Select->SetTexture("OptionSelect.png");
		Render0Select->GetTransform()->SetLocalScale(Render0->GetTransform()->GetLocalScale() * 0.9f);
		Render0Select->GetTransform()->SetLocalPosition({ -350.f,0.f });
		Render0Select->Off();
	}
	{
		Render1 = CreateComponent<GameEngineUIRenderer>();
		Render1->CreateAnimation({ "OpenEpicText", "EpicText.png",0,5,0.1f,false });
		Render1->GetTransform()->SetLocalScale(SheetScale);
		Render1->ChangeAnimation("OpenEpicText");		
		Render1Select = CreateComponent<GameEngineUIRenderer>();
		Render1Select->SetTexture("OptionSelect.png");
		Render1Select->GetTransform()->SetLocalScale(Render0->GetTransform()->GetLocalScale() * 0.9f);		
		Render1Select->Off();
	}
	{
		Render2 = CreateComponent<GameEngineUIRenderer>();
		Render2->CreateAnimation({ "OpenEpicText", "EpicText.png",0,5,0.1f,false });
		Render2->GetTransform()->SetLocalScale(SheetScale);
		Render2->ChangeAnimation("OpenEpicText");
		Render2->GetTransform()->SetLocalPosition({ 350.f,0.f });
		Render2Select = CreateComponent<GameEngineUIRenderer>();
		Render2Select->SetTexture("OptionSelect.png");
		Render2Select->GetTransform()->SetLocalScale(Render0->GetTransform()->GetLocalScale() * 0.9f);
		Render2Select->GetTransform()->SetLocalPosition({ 350.f,0.f });
		Render2Select->Off();
	}
	Collision = CreateComponent<GameEngineCollision>();
	Collision->SetOrder(static_cast<int>(ColEnum::Optionsheet));
	Collision->SetColType(ColType::AABBBOX2D);
	FucntionsInit();
	
	GameEngineRandom::MainRandom.RandomInt(0,Functions.size()-1);
	
	{
		FontRender0 = CreateComponent<GameEngineFontUIRenderer>();
		FontRender0->GetTransform()->SetParent(Render0->GetTransform());
		FontRender0->SetFont("휴먼둥근헤드라인");
		FontRender0->SetScale({ 20.f });
		FontRender0->SetColor({ 1.f,1.f,1.f });
		
	}
	{
		FontRender1 = CreateComponent<GameEngineFontUIRenderer>();
		FontRender1->GetTransform()->SetParent(Render1->GetTransform());
		FontRender1->SetFont("휴먼둥근헤드라인");
		FontRender1->SetScale({ 20.f });
		//FontRender1->GetTransform()->SetLocalPosition({ 1.f,1.f });
	}
	{
		FontRender2 = CreateComponent<GameEngineFontUIRenderer>();
		FontRender2->GetTransform()->SetParent(Render2->GetTransform());
		FontRender2->SetFont("휴먼둥근헤드라인");
		FontRender2->SetScale({ 20.f });
		FontRender2->GetTransform()->SetLocalPosition({ 1.f,1.f });
	}
}

// 이건 디버깅용도나 
void Optionsheet::Render(float _Delta)
{

}

void Optionsheet::FSMInit()
{

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