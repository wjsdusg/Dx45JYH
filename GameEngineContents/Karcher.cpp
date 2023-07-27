#include "PrecompileHeader.h"
#include "Karcher.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "ContentsEnum.h"
#include "MapOverlay.h"
#include "DefenseMapEditor.h"
extern float4 MainMouse;
extern  float CalAngle1To2(float4 _Pos1, float4 _Pos2);
int Karcher::AddHp = 0;
int Karcher::AddATK = 0;
int Karcher::AddShield = 0;
Karcher::Karcher()
{
}

Karcher::~Karcher()
{
}


void Karcher::Update(float _DeltaTime)
{
	Unit::Update(_DeltaTime);
	
}

void Karcher::Start()
{	
	if (nullptr == GameEngineSprite::Find("archerk.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Unit");
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("archerk.png").GetFullPath(), 16, 11);
	}
	
	Render0 = CreateComponent<GameEngineSpriteRenderer>();

	
	Render0->CreateAnimation({ "LDown45Stay", "archerk.png",0,7,0.1f,true,true });
	Render0->CreateAnimation({ "LStay", "archerk.png",8,15,0.1f,true,true });
	Render0->CreateAnimation({ "LUp45Stay", "archerk.png",16,23,0.1f,true,true });
	Render0->CreateAnimation({ "UpStay", "archerk.png",24,31,0.1f,true,true });
	Render0->CreateAnimation({ "DownStay", "archerk.png",32,39,0.1f,true,true });
	Render0->CreateAnimation({ "LDown45Move", "archerk.png",80,87,0.1f,true,true });
	Render0->CreateAnimation({ "LMove", "archerk.png",88,95,0.1f,true,true });
	Render0->CreateAnimation({ "LUp45Move", "archerk.png",96,103,0.1f,true,true });
	Render0->CreateAnimation({ "UpMove", "archerk.png",104,111,0.1f,true,true });
	Render0->CreateAnimation({ "DownMove", "archerk.png",112,119,0.1f,true,true });
	Render0->CreateAnimation({ "LDown45Attack", "archerk.png",120,127,AttackSpeed / 8.f,true,true });
	Render0->CreateAnimation({ "LAttack", "archerk.png",128,135,AttackSpeed / 8.f ,true,true });
	Render0->CreateAnimation({ "LUp45Attack", "archerk.png",136,143,AttackSpeed / 8.f,true,true });
	Render0->CreateAnimation({ "UpAttack", "archerk.png",144,151,AttackSpeed / 8.f ,true,true });
	Render0->CreateAnimation({ "DownAttack", "archerk.png",152,159,AttackSpeed / 8.f ,true,true });
	Render0->CreateAnimation({ "Die", "archerk.png",160,167,0.1f,false,true });
	GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(1, 1));
	MissileRender = CreateComponent<GameEngineSpriteRenderer>();
	MissileRender->SetTexture("arrow.tga");
	MissileRender->SetScaleToTexture("arrow.tga");
	MissileRender->Off();

	MyTeam = Team::Mine;
	MyAttackType = AttackType::Far;
	
	Unit::Start();
	
	
}

// 이건 디버깅용도나 
void Karcher::Render(float _Delta)
{

};
