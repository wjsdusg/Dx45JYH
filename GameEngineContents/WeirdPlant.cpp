#include "PrecompileHeader.h"
#include "WeirdPlant.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

WeirdPlant::WeirdPlant()
{
}

WeirdPlant::~WeirdPlant()
{
}


void WeirdPlant::Update(float _DeltaTime)
{
	Unit::Update(_DeltaTime);

}

void WeirdPlant::Start()
{


	if (nullptr == GameEngineSprite::Find("WeirdPlant.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Monster");
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("WeirdPlant.png").GetFullPath(), 8, 17);

	}
	Render0 = CreateComponent<GameEngineSpriteRenderer>();

	Render0->GetTransform()->SetLocalScale({ 120.f,110.f,1.f });

	Render0->CreateAnimation({ "LDown45Stay", "WeirdPlant.png",40,47 });
	Render0->CreateAnimation({ "LStay", "WeirdPlant.png",48,55 });
	Render0->CreateAnimation({ "LUp45Stay", "WeirdPlant.png",56,63 });
	Render0->CreateAnimation({ "UpStay", "WeirdPlant.png",64,71 });
	Render0->CreateAnimation({ "DownStay", "WeirdPlant.png",72,79 });

	Render0->CreateAnimation({ "LDown45Move", "WeirdPlant.png",80,87 });
	Render0->CreateAnimation({ "LMove", "WeirdPlant.png",88,95 });
	Render0->CreateAnimation({ "LUp45Move", "WeirdPlant.png",96,103 });
	Render0->CreateAnimation({ "UpMove", "WeirdPlant.png",104,111 });
	Render0->CreateAnimation({ "DownMove", "WeirdPlant.png",112,119 });

	Render0->CreateAnimation({ "LDown45Attack", "WeirdPlant.png",0,7,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "LAttack", "WeirdPlant.png",8,15,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "LUp45Attack", "WeirdPlant.png",16,23,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "UpAttack", "WeirdPlant.png",24,31,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "DownAttack", "WeirdPlant.png",32,39,AttackSpeed / 8.f });

	Render0->CreateAnimation({ "Die", "WeirdPlant.png",120,129,0.1f,false });

	Render0->ChangeAnimation("LStay");

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform()->SetLocalScale({ 60.f,60.f,1.f });
	Collision->SetOrder(static_cast<int>(ColEnum::Enemy));
	Collision->SetColType(ColType::AABBBOX2D);

	Unit::Start();
	Minion::Start();

}

// 이건 디버깅용도나 
void WeirdPlant::Render(float _Delta)
{



};
