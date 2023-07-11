#include "PrecompileHeader.h"
#include "SwordPirate.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

SwordPirate::SwordPirate()
{
}

SwordPirate::~SwordPirate()
{
}


void SwordPirate::Update(float _DeltaTime)
{
	Unit::Update(_DeltaTime);

}

void SwordPirate::Start()
{


	if (nullptr == GameEngineSprite::Find("SwordPirate.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Monster");
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("SwordPirate.png").GetFullPath(), 8, 17);

	}
	Render0 = CreateComponent<GameEngineSpriteRenderer>();

	Render0->GetTransform()->SetLocalScale({ 110.f,110.f,1.f });

	Render0->CreateAnimation({ "LDown45Stay", "SwordPirate.png",40,47 });
	Render0->CreateAnimation({ "LStay", "SwordPirate.png",48,55 });
	Render0->CreateAnimation({ "LUp45Stay", "SwordPirate.png",56,63 });
	Render0->CreateAnimation({ "UpStay", "SwordPirate.png",64,71 });
	Render0->CreateAnimation({ "DownStay", "SwordPirate.png",72,79 });

	Render0->CreateAnimation({ "LDown45Move", "SwordPirate.png",80,87 });
	Render0->CreateAnimation({ "LMove", "SwordPirate.png",88,95 });
	Render0->CreateAnimation({ "LUp45Move", "SwordPirate.png",96,103 });
	Render0->CreateAnimation({ "UpMove", "SwordPirate.png",104,111 });
	Render0->CreateAnimation({ "DownMove", "SwordPirate.png",112,119 });

	Render0->CreateAnimation({ "LDown45Attack", "SwordPirate.png",0,7,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "LAttack", "SwordPirate.png",8,15,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "LUp45Attack", "SwordPirate.png",16,23,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "UpAttack", "SwordPirate.png",24,31,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "DownAttack", "SwordPirate.png",32,39,AttackSpeed / 8.f });

	Render0->CreateAnimation({ "Die", "SwordPirate.png",120,128,0.1f,false });


	Render0->ChangeAnimation("LStay");

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform()->SetLocalScale({ 60.f,60.f,1.f });
	Collision->SetOrder(static_cast<int>(ColEnum::Enemy));
	Collision->SetColType(ColType::AABBBOX2D);

	Unit::Start();
	Minion::Start();

}

// 이건 디버깅용도나 
void SwordPirate::Render(float _Delta)
{



};
