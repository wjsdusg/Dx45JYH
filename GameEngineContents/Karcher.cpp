#include "PrecompileHeader.h"
#include "Karcher.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "ContentsEnum.h"
#include "MapOverlay.h"
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
	GameEngineDebug::DrawBox(GetLevel()->GetMainCamera().get(), TestComponent->GetTransform());
}

void Karcher::Start()
{
	

	GetTransform()->AddLocalPosition({ 0.f,-200.f });
	//MousePickPos = GetTransform()->GetLocalPosition();
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

	Render0->GetTransform()->SetLocalScale({ 60.f,60.f,1.f });
	//Render0->CreateAnimation({ .AnimationName = "Move", .SpriteName = "archerk.png", .ScaleToTexture = false });
	Render0->CreateAnimation({ "LDown45Stay", "archerk.png",0,7});
	Render0->CreateAnimation({ "LStay", "archerk.png",8,15});
	Render0->CreateAnimation({ "LUp45Stay", "archerk.png",16,23});
	Render0->CreateAnimation({ "UpStay", "archerk.png",24,31});
	Render0->CreateAnimation({ "DownStay", "archerk.png",32,39});

	Render0->CreateAnimation({ "LDown45Move", "archerk.png",80,87});
	Render0->CreateAnimation({ "LMove", "archerk.png",88,95});
	Render0->CreateAnimation({ "LUp45Move", "archerk.png",96,103});
	Render0->CreateAnimation({ "UpMove", "archerk.png",104,111});
	Render0->CreateAnimation({ "DownMove", "archerk.png",112,119});

	Render0->CreateAnimation({ "LDown45Attack", "archerk.png",120,127,AttackSpeed/8.f});
	Render0->CreateAnimation({ "LAttack", "archerk.png",128,135,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "LUp45Attack", "archerk.png",136,143,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "UpAttack", "archerk.png",144,151,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "DownAttack", "archerk.png",152,159,AttackSpeed / 8.f });
	
	Render0->CreateAnimation({ "Die", "archerk.png",160,167});

	Render0->ChangeAnimation("LStay");
	
	/*Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform()->SetLocalScale({ 40.f,40.f,1.f });
	Collision->SetOrder(static_cast<int>(ColEnum::Unit));*/

	/*FOVCollision = CreateComponent<GameEngineCollision>();
	FOVCollision->GetTransform()->SetLocalScale({ 400,400,1.f });
	FOVCollision->SetOrder(static_cast<int>(ColEnum::UnitFOV));*/

	Unit::Start();
	MyTeam = Team::Mine;
	
	TestComponent = CreateComponent<GameEngineComponent>();
	TestComponent->GetTransform()->SetWorldPosition({ 60,0,0 });
	TestComponent->GetTransform()->SetLocalScale({ 3,3 });
	
}

// 이건 디버깅용도나 
void Karcher::Render(float _Delta)
{

};
