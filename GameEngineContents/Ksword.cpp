#include "PrecompileHeader.h"
#include "Ksword.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineFontRenderer.h>
#include "ContentsEnum.h"
#include "MapOverlay.h"
#include "MapEditor.h"
#include "DefenseMapEditor.h"
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
	if (MyTeam == Team::Enemy)
	{
		//std::string str3 = "��";
		//str3 += "\n";
		std::string str3;
		std::string str4 = std::to_string(CurHp);
		str3 += str4;
		str3 += "/";
		str4= std::to_string(HP);
		str3 += str4;
		
		FontRender0->SetText(str3);
	}
	
	
	
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
	Render0 = CreateComponent<GameEngineSpriteRenderer>();	
	Render0->CreateAnimation({ "LDown45Stay", "swordk.png",128,137,0.15f,true,true});
	Render0->CreateAnimation({ "LStay", "swordk.png",138,147,0.15f,true,true});
	Render0->CreateAnimation({ "LUp45Stay", "swordk.png",148,157,0.15f,true,true});
	Render0->CreateAnimation({ "UpStay", "swordk.png",158,167,0.15f,true,true});
	Render0->CreateAnimation({ "DownStay", "swordk.png",168,177,0.15f,true,true});
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
	GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(1, 1));	
	MyTeam = Team::Mine;
	MyAttackType = AttackType::Near;
	Unit::Start();
	
	{
		FontRender0 = CreateComponent<GameEngineFontRenderer>();		
		FontRender0->SetFont("�޸յձ�������");
		FontRender0->SetScale({ 20.f });
		FontRender0->GetTransform()->SetLocalPosition({0,20.f});
	}
}

// �̰� �����뵵�� 
void Ksword::Render(float _Delta)
{

};
