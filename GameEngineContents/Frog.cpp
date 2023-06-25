#include "PrecompileHeader.h"
#include "Frog.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

Frog::Frog()
{
}

Frog::~Frog()
{
}


void Frog::Update(float _DeltaTime)
{
	Unit::Update(_DeltaTime);

}

void Frog::Start()
{


	
	if (nullptr == GameEngineSprite::Find("frog.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Monster");
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("frog.png").GetFullPath(), 8, 17);
	}
	Render0 = CreateComponent<GameEngineSpriteRenderer>();

	Render0->GetTransform()->SetLocalScale({ 100.f,100.f,1.f });
	
	Render0->CreateAnimation({ "LDown45Stay", "Frog.png",40,47 });
	Render0->CreateAnimation({ "LStay", "Frog.png",48,55 });
	Render0->CreateAnimation({ "LUp45Stay", "Frog.png",56,63 });
	Render0->CreateAnimation({ "UpStay", "Frog.png",64,71 });
	Render0->CreateAnimation({ "DownStay", "Frog.png",72,79 });

	Render0->CreateAnimation({ "LDown45Move", "Frog.png",80,87 });
	Render0->CreateAnimation({ "LMove", "Frog.png",88,95 });
	Render0->CreateAnimation({ "LUp45Move", "Frog.png",96,103 });
	Render0->CreateAnimation({ "UpMove", "Frog.png",104,111 });
	Render0->CreateAnimation({ "DownMove", "Frog.png",112,119 });

	Render0->CreateAnimation({ "LDown45Attack", "Frog.png",0,7,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "LAttack", "Frog.png",8,15,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "LUp45Attack", "Frog.png",16,23,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "UpAttack", "Frog.png",24,31,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "DownAttack", "Frog.png",32,39,AttackSpeed / 8.f });

	Render0->CreateAnimation({ "Die", "Frog.png",120,130 });

	Render0->ChangeAnimation("LStay");
	
	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform()->SetLocalScale({ 40.f,40.f,1.f });
	Collision->SetOrder(static_cast<int>(ColEnum::Enemy));
	Collision->SetColType(ColType::AABBBOX2D);
			
	Unit::Start();
	Minion::Start();
}

// 이건 디버깅용도나 
void Frog::Render(float _Delta)
{

};
