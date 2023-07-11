#include "PrecompileHeader.h"
#include "Gangsi.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

Gangsi::Gangsi()
{
}

Gangsi::~Gangsi()
{
}


void Gangsi::Update(float _DeltaTime)
{
	Unit::Update(_DeltaTime);

}

void Gangsi::Start()
{


	if (nullptr == GameEngineSprite::Find("Gangsi1.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Monster");
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Gangsi1.png").GetFullPath(), 8, 5);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Gangsi2.png").GetFullPath(), 13, 5);
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Gangsi3.png").GetFullPath(), 4, 3);
	}
	Render0 = CreateComponent<GameEngineSpriteRenderer>();
	//y값이 x보다크면 x플립이아니라 y플립이된다.
	Render0->GetTransform()->SetLocalScale({ 110.f,110.f,1.f });

	Render0->CreateAnimation({ "LDown45Stay", "Gangsi2.png",0,0 });
	Render0->CreateAnimation({ "LStay", "Gangsi2.png",13,13 });
	Render0->CreateAnimation({ "LUp45Stay", "Gangsi2.png",26,26 });
	Render0->CreateAnimation({ "UpStay", "Gangsi2.png",39,39 });
	Render0->CreateAnimation({ "DownStay", "Gangsi2.png",52,52 });

	Render0->CreateAnimation({ "LDown45Move", "Gangsi1.png",0,7 });
	Render0->CreateAnimation({ "LMove", "Gangsi1.png",8,15 });
	Render0->CreateAnimation({ "LUp45Move", "Gangsi1.png",16,23 });
	Render0->CreateAnimation({ "UpMove", "Gangsi1.png",24,31 });
	Render0->CreateAnimation({ "DownMove", "Gangsi1.png",32,39 });

	Render0->CreateAnimation({ "LDown45Attack", "Gangsi2.png",0,12,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "LAttack", "Gangsi2.png",13,25,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "LUp45Attack", "Gangsi2.png",26,38,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "UpAttack", "Gangsi2.png",39,51,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "DownAttack", "Gangsi2.png",52,64,AttackSpeed / 8.f });

	Render0->CreateAnimation({ "Die", "Gangsi3.png",0,11,0.1f,false });
	

	Render0->ChangeAnimation("LStay");
	
	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform()->SetLocalScale({ 40.f,60.f,1.f });
	Collision->SetOrder(static_cast<int>(ColEnum::Enemy));
	Collision->SetColType(ColType::AABBBOX2D);

	Unit::Start();
	Minion::Start();
		
}

// 이건 디버깅용도나 
void Gangsi::Render(float _Delta)
{
	


};
