#include "PrecompileHeader.h"
#include "Gatpha.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

Gatpha::Gatpha()
{
}

Gatpha::~Gatpha()
{
}


void Gatpha::Update(float _DeltaTime)
{
	Unit::Update(_DeltaTime);

}

void Gatpha::Start()
{


	if (nullptr == GameEngineSprite::Find("Gatpha.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Monster");
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Gatpha.png").GetFullPath(), 8, 17);
		
	}
	Render0 = CreateComponent<GameEngineSpriteRenderer>();
	
	Render0->GetTransform()->SetLocalScale({ 110.f,110.f,1.f });

	Render0->CreateAnimation({ "LDown45Stay", "Gatpha.png",40,47 });
	Render0->CreateAnimation({ "LStay", "Gatpha.png",48,55 });
	Render0->CreateAnimation({ "LUp45Stay", "Gatpha.png",56,63 });
	Render0->CreateAnimation({ "UpStay", "Gatpha.png",64,71 });
	Render0->CreateAnimation({ "DownStay", "Gatpha.png",72,79 });

	Render0->CreateAnimation({ "LDown45Move", "Gatpha.png",80,87 });
	Render0->CreateAnimation({ "LMove", "Gatpha.png",88,95 });
	Render0->CreateAnimation({ "LUp45Move", "Gatpha.png",96,103 });
	Render0->CreateAnimation({ "UpMove", "Gatpha.png",104,111 });
	Render0->CreateAnimation({ "DownMove", "Gatpha.png",112,119 });

	Render0->CreateAnimation({ "LDown45Attack", "Gatpha.png",0,7,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "LAttack", "Gatpha.png",8,15,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "LUp45Attack", "Gatpha.png",16,23,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "UpAttack", "Gatpha.png",24,31,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "DownAttack", "Gatpha.png",32,39,AttackSpeed / 8.f });

	Render0->CreateAnimation({ "Die", "Gatpha.png",120,133,0.1f,false });


	Render0->ChangeAnimation("LStay");

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform()->SetLocalScale({ 60.f,60.f,1.f });
	Collision->SetOrder(static_cast<int>(ColEnum::Enemy));
	Collision->SetColType(ColType::AABBBOX2D);

	Unit::Start();
	Minion::Start();

}

// 이건 디버깅용도나 
void Gatpha::Render(float _Delta)
{



};
