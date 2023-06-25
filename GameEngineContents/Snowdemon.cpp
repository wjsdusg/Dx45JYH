#include "PrecompileHeader.h"
#include "Snowdemon.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

Snowdemon::Snowdemon()
{
}

Snowdemon::~Snowdemon()
{
}


void Snowdemon::Update(float _DeltaTime)
{
	Unit::Update(_DeltaTime);

}

void Snowdemon::Start()
{


	if (nullptr == GameEngineSprite::Find("Snowdemon.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Monster");
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Snowdemon.png").GetFullPath(), 28, 6);

	}
	Render0 = CreateComponent<GameEngineSpriteRenderer>();

	Render0->GetTransform()->SetLocalScale({ 160.f,160.f,1.f });

	Render0->CreateAnimation({ "LDown45Stay", "Snowdemon.png",50,57 });
	Render0->CreateAnimation({ "LStay", "Snowdemon.png",58,65 });
	Render0->CreateAnimation({ "LUp45Stay", "Snowdemon.png",66,73 });
	Render0->CreateAnimation({ "UpStay", "Snowdemon.png",74,81 });
	Render0->CreateAnimation({ "DownStay", "Snowdemon.png",82,89 });

	Render0->CreateAnimation({ "LDown45Move", "Snowdemon.png",90,97 });
	Render0->CreateAnimation({ "LMove", "Snowdemon.png",98,105 });
	Render0->CreateAnimation({ "LUp45Move", "Snowdemon.png",106,113 });
	Render0->CreateAnimation({ "UpMove", "Snowdemon.png",114,121 });
	Render0->CreateAnimation({ "DownMove", "Snowdemon.png",122,129 });

	Render0->CreateAnimation({ "LDown45Attack", "Snowdemon.png",0,9,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "LAttack", "Snowdemon.png",10,19,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "LUp45Attack", "Snowdemon.png",20,29,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "UpAttack", "Snowdemon.png",30,39,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "DownAttack", "Snowdemon.png",40,49,AttackSpeed / 8.f });

	Render0->CreateAnimation({ "Die", "Snowdemon.png",130,142 });


	Render0->ChangeAnimation("LStay");

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform()->SetLocalScale({ 80.f,80.f,1.f });
	Collision->SetOrder(static_cast<int>(ColEnum::Enemy));
	Collision->SetColType(ColType::AABBBOX2D);

	Unit::Start();
	Minion::Start();

}

// 이건 디버깅용도나 
void Snowdemon::Render(float _Delta)
{



};
