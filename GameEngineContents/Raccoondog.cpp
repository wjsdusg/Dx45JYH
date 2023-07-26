#include "PrecompileHeader.h"
#include "Raccoondog.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

Raccoondog::Raccoondog()
{
}

Raccoondog::~Raccoondog()
{
}


void Raccoondog::Update(float _DeltaTime)
{
	Minion::Update(_DeltaTime);

}

void Raccoondog::Start()
{


	if (nullptr == GameEngineSprite::Find("Raccoondog.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Monster");
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Raccoondog.png").GetFullPath(), 12, 14);

	}
	Render0 = CreateComponent<GameEngineSpriteRenderer>();

	Render0->GetTransform()->SetLocalScale({ 110.f,110.f,1.f });

	Render0->CreateAnimation({ "LDown45Stay", "Raccoondog.png",72,79 });
	Render0->CreateAnimation({ "LStay", "Raccoondog.png",80,87 });
	Render0->CreateAnimation({ "LUp45Stay", "Raccoondog.png",88,95 });
	Render0->CreateAnimation({ "UpStay", "Raccoondog.png",96,103 });
	Render0->CreateAnimation({ "DownStay", "Raccoondog.png",104,111 });

	Render0->CreateAnimation({ "LDown45Move", "Raccoondog.png",112,121 });
	Render0->CreateAnimation({ "LMove", "Raccoondog.png",122,131 });
	Render0->CreateAnimation({ "LUp45Move", "Raccoondog.png",132,141 });
	Render0->CreateAnimation({ "UpMove", "Raccoondog.png",142,151 });
	Render0->CreateAnimation({ "DownMove", "Raccoondog.png",152,161 });

	Render0->CreateAnimation({ "LDown45Attack", "Raccoondog.png",0,11,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "LAttack", "Raccoondog.png",12,23,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "LUp45Attack", "Raccoondog.png",24,35,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "UpAttack", "Raccoondog.png",36,47,AttackSpeed / 8.f });
	Render0->CreateAnimation({ "DownAttack", "Raccoondog.png",48,59,AttackSpeed / 8.f });

	Render0->CreateAnimation({ "Die", "Raccoondog.png",60,71,0.1f,false });


	Render0->ChangeAnimation("LStay");

	
	Minion::Start();

}

// 이건 디버깅용도나 
void Raccoondog::Render(float _Delta)
{



};
