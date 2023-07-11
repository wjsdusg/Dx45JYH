#include "PrecompileHeader.h"
#include "Onghwa.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

Onghwa::Onghwa()
{
}

Onghwa::~Onghwa()
{
}


void Onghwa::Update(float _DeltaTime)
{
	Unit::Update(_DeltaTime);

}

void Onghwa::Start()
{


	if (nullptr == GameEngineSprite::Find("Onghwa.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Monster");
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Onghwa.png").GetFullPath(), 8, 17);

	}
	Render0 = CreateComponent<GameEngineSpriteRenderer>();

	Render0->GetTransform()->SetLocalScale({ 110.f,110.f,1.f });

	Render0->CreateAnimation({ "LDown45Stay", "Onghwa.png",40,47 });
	Render0->CreateAnimation({ "LStay", "Onghwa.png",48,55 });
	Render0->CreateAnimation({ "LUp45Stay", "Onghwa.png",56,63 });
	Render0->CreateAnimation({ "UpStay", "Onghwa.png",64,71 });
	Render0->CreateAnimation({ "DownStay", "Onghwa.png",72,79 });

	Render0->CreateAnimation({ "LDown45Move", "Onghwa.png",80,87 });
	Render0->CreateAnimation({ "LMove", "Onghwa.png",88,95 });
	Render0->CreateAnimation({ "LUp45Move", "Onghwa.png",96,103 });
	Render0->CreateAnimation({ "UpMove", "Onghwa.png",104,111 });
	Render0->CreateAnimation({ "DownMove", "Onghwa.png",112,119 });

	Render0->CreateAnimation({ "LDown45Attack", "Onghwa.png",0,7,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "LAttack", "Onghwa.png",8,15,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "LUp45Attack", "Onghwa.png",16,23,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "UpAttack", "Onghwa.png",24,31,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "DownAttack", "Onghwa.png",32,39,AttackSpeed / 8.f });

	Render0->CreateAnimation({ "Die", "Onghwa.png",120,134,0.1f,false });


	Render0->ChangeAnimation("LStay");

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform()->SetLocalScale({ 60.f,60.f,1.f });
	Collision->SetOrder(static_cast<int>(ColEnum::Enemy));
	Collision->SetColType(ColType::AABBBOX2D);

	Unit::Start();
	Minion::Start();

}

// 이건 디버깅용도나 
void Onghwa::Render(float _Delta)
{



};
