#include "PrecompileHeader.h"
#include "Ksword.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineFontRenderer.h>
#include "ContentsEnum.h"
#include "MapOverlay.h"
#include "MapEditor.h"
extern float4 MainMouse;
extern  float CalAngle1To2(float4 _Pos1, float4 _Pos2);
int Ksword::AddHp = 0;
int Ksword::AddATK = 0;
int Ksword::AddShield = 0;
Ksword::Ksword()
{
}

Ksword::~Ksword()
{
}


void Ksword::Update(float _DeltaTime)
{
	Unit::Update(_DeltaTime);
	
	/*std::string str3 = MapEditor::ConvertPosToTileXY(ShortTargetPos).ToString();
	std::string str4 =std::to_string(TestDistance);
	str3 += "\n";
	str3 += str4;
	FontRender0->SetText(str3);*/
}
//
void Ksword::Start()
{	
	if (nullptr == GameEngineSprite::Find("swordk.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Unit");
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("swordk.png").GetFullPath(), 16, 12);
	}
	
	GetTransform()->AddLocalPosition({ 0.f,-200.f });
	//MousePickPos = GetTransform()->GetLocalPosition();
	
	Render0 = CreateComponent<GameEngineSpriteRenderer>();
	
	Render0->CreateAnimation({ "LDown45Stay", "swordk.png",128,137,0.1f,true,true});
	Render0->CreateAnimation({ "LStay", "swordk.png",138,147,0.1f,true,true});
	Render0->CreateAnimation({ "LUp45Stay", "swordk.png",148,157,0.1f,true,true});
	Render0->CreateAnimation({ "UpStay", "swordk.png",158,167,0.1f,true,true});
	Render0->CreateAnimation({ "DownStay", "swordk.png",168,177,0.1f,true,true});
	Render0->CreateAnimation({ "LDown45Move", "swordk.png",0,7,0.1f,true,true});
	Render0->CreateAnimation({ "LMove", "swordk.png",8,15 ,0.1f,true,true});
	Render0->CreateAnimation({ "LUp45Move", "swordk.png",16,23,0.1f,true,true});
	Render0->CreateAnimation({ "UpMove", "swordk.png",24,31,0.1f,true,true});
	Render0->CreateAnimation({ "DownMove", "swordk.png",32,39,0.1f,true,true});
	Render0->CreateAnimation({ "LDown45Attack", "swordk.png",48,55,AttackSpeed / 8.f,true,true });
	Render0->CreateAnimation({ "LAttack", "swordk.png",56,63,AttackSpeed / 8.f,true,true });
	Render0->CreateAnimation({ "LUp45Attack", "swordk.png",64,71,AttackSpeed / 8.f,true,true });
	Render0->CreateAnimation({ "UpAttack", "swordk.png",72,79,AttackSpeed / 8.f,true,true });
	Render0->CreateAnimation({ "DownAttack", "swordk.png",80,87,AttackSpeed / 8.f,true,true });
	Render0->CreateAnimation({ "Die", "swordk.png",40,47,0.1f,false,true});
	
	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform()->SetLocalScale({ 40.f,40.f,1.f });
	Collision->SetOrder(static_cast<int>(ColEnum::Unit));
	/*FOVCollision = CreateComponent<GameEngineCollision>();
	FOVCollision->GetTransform()->SetLocalScale({ FightFOV,0,1.f });
	FOVCollision->SetColType(ColType::SPHERE2D);
	FOVCollision->SetOrder(static_cast<int>(ColEnum::UnitFOV));*/
		
	MyTeam = Team::Mine;

	Unit::Start();
	//Speed = 500.f;
	{
		FontRender0 = CreateComponent<GameEngineFontRenderer>();
		//FontRender0->GetTransform()->SetParent(NewObject->GetTransform());
		FontRender0->SetFont("휴먼둥근헤드라인");
		FontRender0->SetScale({ 20.f });
		FontRender0->GetTransform()->SetLocalPosition({0,20.f});
	}
}

// 이건 디버깅용도나 
void Ksword::Render(float _Delta)
{

};
