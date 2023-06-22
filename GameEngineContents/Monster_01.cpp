#include "PrecompileHeader.h"
#include "Monster_01.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "ContentsEnum.h"
#include "MapOverlay.h"
extern float4 MainMouse;
extern  float CalAngle1To2(float4 _Pos1, float4 _Pos2);
Monster_01::Monster_01()
{
}

Monster_01::~Monster_01()
{
}


void Monster_01::Update(float _DeltaTime)
{
	Unit::Update(_DeltaTime);

}

void Monster_01::Start()
{


	GetTransform()->AddLocalPosition({ 0.f,50.f });
	//MousePickPos = GetTransform()->GetLocalPosition();
	if (nullptr == GameEngineSprite::Find("Monster_01.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Unit");
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Monster_01.png").GetFullPath(), 8, 18);
	}
	Render0 = CreateComponent<GameEngineSpriteRenderer>();

	Render0->GetTransform()->SetLocalScale({ 160.f,160.f,1.f });
	//Render0->CreateAnimation({ .AnimationName = "Move", .SpriteName = "Monster_01.png", .ScaleToTexture = false });
	Render0->CreateAnimation({ "LDown45Stay", "Monster_01.png",57,64 });
	Render0->CreateAnimation({ "LStay", "Monster_01.png",65,72 });
	Render0->CreateAnimation({ "LUp45Stay", "Monster_01.png",73,80 });
	Render0->CreateAnimation({ "UpStay", "Monster_01.png",81,88 });
	Render0->CreateAnimation({ "DownStay", "Monster_01.png",89,96 });

	Render0->CreateAnimation({ "LDown45Move", "Monster_01.png",97,104 });
	Render0->CreateAnimation({ "LMove", "Monster_01.png",105,112 });
	Render0->CreateAnimation({ "LUp45Move", "Monster_01.png",113,120 });
	Render0->CreateAnimation({ "UpMove", "Monster_01.png",121,128 });
	Render0->CreateAnimation({ "DownMove", "Monster_01.png",129,136 });

	Render0->CreateAnimation({ "LDown45Attack", "Monster_01.png",32,39 });
	Render0->CreateAnimation({ "LAttack", "Monster_01.png",0,7 });
	Render0->CreateAnimation({ "LUp45Attack", "Monster_01.png",8,15 });
	Render0->CreateAnimation({ "UpAttack", "Monster_01.png",15,23 });
	Render0->CreateAnimation({ "DownAttack", "Monster_01.png",32,39 });

	Render0->CreateAnimation({ "Die", "Monster_01.png",40,56 });

	Render0->ChangeAnimation("LStay");
	//MainRenderer->CreateAnimation({ "Win", "TestAnimation.png", 0, 5, 0.1f, true, true });
	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform()->SetLocalScale({ 80.f,80.f,1.f });
	Collision->SetOrder(static_cast<int>(ColEnum::Monster));

	Unit::Start();
	MyTeam = Team::Enemy;

	GetTransform()->SetLocalPosition({ -300.f,-300.f });
}

// 이건 디버깅용도나 
void Monster_01::Render(float _Delta)
{

};
