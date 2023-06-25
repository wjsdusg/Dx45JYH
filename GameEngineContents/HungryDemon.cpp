#include "PrecompileHeader.h"
#include "HungryDemon.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

HungryDemon::HungryDemon()
{
}

HungryDemon::~HungryDemon()
{
}


void HungryDemon::Update(float _DeltaTime)
{
	Unit::Update(_DeltaTime);

}

void HungryDemon::Start()
{


	if (nullptr == GameEngineSprite::Find("HungryDemon.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Monster");
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("HungryDemon.png").GetFullPath(), 8, 17);

	}
	Render0 = CreateComponent<GameEngineSpriteRenderer>();

	Render0->GetTransform()->SetLocalScale({ 110.f,110.f,1.f });

	Render0->CreateAnimation({ "LDown45Stay", "HungryDemon.png",40,47 });
	Render0->CreateAnimation({ "LStay", "HungryDemon.png",48,55 });
	Render0->CreateAnimation({ "LUp45Stay", "HungryDemon.png",56,63 });
	Render0->CreateAnimation({ "UpStay", "HungryDemon.png",64,71 });
	Render0->CreateAnimation({ "DownStay", "HungryDemon.png",72,79 });

	Render0->CreateAnimation({ "LDown45Move", "HungryDemon.png",80,87 });
	Render0->CreateAnimation({ "LMove", "HungryDemon.png",88,95 });
	Render0->CreateAnimation({ "LUp45Move", "HungryDemon.png",96,103 });
	Render0->CreateAnimation({ "UpMove", "HungryDemon.png",104,111 });
	Render0->CreateAnimation({ "DownMove", "HungryDemon.png",112,119 });

	Render0->CreateAnimation({ "LDown45Attack", "HungryDemon.png",0,7,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "LAttack", "HungryDemon.png",8,15,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "LUp45Attack", "HungryDemon.png",16,23,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "UpAttack", "HungryDemon.png",24,31,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "DownAttack", "HungryDemon.png",32,39,AttackSpeed / 8.f });

	Render0->CreateAnimation({ "Die", "HungryDemon.png",120,130 });


	Render0->ChangeAnimation("LStay");

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform()->SetLocalScale({ 60.f,60.f,1.f });
	Collision->SetOrder(static_cast<int>(ColEnum::Enemy));
	Collision->SetColType(ColType::AABBBOX2D);

	Unit::Start();
	Minion::Start();

}

// 이건 디버깅용도나 
void HungryDemon::Render(float _Delta)
{



};
