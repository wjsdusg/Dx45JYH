#include "PrecompileHeader.h"
#include "Tiger.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

Tiger::Tiger()
{
}

Tiger::~Tiger()
{
}


void Tiger::Update(float _DeltaTime)
{
	Unit::Update(_DeltaTime);

}

void Tiger::Start()
{


	if (nullptr == GameEngineSprite::Find("Tiger.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Monster");
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Tiger.png").GetFullPath(), 8, 17);

	}
	Render0 = CreateComponent<GameEngineSpriteRenderer>();

	Render0->GetTransform()->SetLocalScale({ 120.f,110.f,1.f });

	Render0->CreateAnimation({ "LDown45Stay", "Tiger.png",40,47 });
	Render0->CreateAnimation({ "LStay", "Tiger.png",48,55 });
	Render0->CreateAnimation({ "LUp45Stay", "Tiger.png",56,63 });
	Render0->CreateAnimation({ "UpStay", "Tiger.png",64,71 });
	Render0->CreateAnimation({ "DownStay", "Tiger.png",72,79 });

	Render0->CreateAnimation({ "LDown45Move", "Tiger.png",80,87 });
	Render0->CreateAnimation({ "LMove", "Tiger.png",88,95 });
	Render0->CreateAnimation({ "LUp45Move", "Tiger.png",96,103 });
	Render0->CreateAnimation({ "UpMove", "Tiger.png",104,111 });
	Render0->CreateAnimation({ "DownMove", "Tiger.png",112,119 });

	Render0->CreateAnimation({ "LDown45Attack", "Tiger.png",0,7,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "LAttack", "Tiger.png",8,15,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "LUp45Attack", "Tiger.png",16,23,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "UpAttack", "Tiger.png",24,31,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "DownAttack", "Tiger.png",32,39,AttackSpeed / 8.f });

	Render0->CreateAnimation({ "Die", "Tiger.png",120,129,0.1f,false });


	Render0->ChangeAnimation("LStay");

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform()->SetLocalScale({ 60.f,60.f,1.f });
	Collision->SetOrder(static_cast<int>(ColEnum::Enemy));
	Collision->SetColType(ColType::AABBBOX2D);

	Unit::Start();
	Minion::Start();

}

// 이건 디버깅용도나 
void Tiger::Render(float _Delta)
{



};
