#include "PrecompileHeader.h"
#include "Snowwoman.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

Snowwoman::Snowwoman()
{
}

Snowwoman::~Snowwoman()
{
}


void Snowwoman::Update(float _DeltaTime)
{
	Minion::Update(_DeltaTime);

}

void Snowwoman::Start()
{


	if (nullptr == GameEngineSprite::Find("Snowwoman.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Monster");
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Snowwoman.png").GetFullPath(), 12,16);

	}
	Render0 = CreateComponent<GameEngineSpriteRenderer>();

	Render0->GetTransform()->SetLocalScale({ 140.f,140.f,1.f });

	Render0->CreateAnimation({ "LDown45Stay", "Snowwoman.png",84,93 });
	Render0->CreateAnimation({ "LStay", "Snowwoman.png",94,103 });
	Render0->CreateAnimation({ "LUp45Stay", "Snowwoman.png",104,113 });
	Render0->CreateAnimation({ "UpStay", "Snowwoman.png",114,123 });
	Render0->CreateAnimation({ "DownStay", "Snowwoman.png",124,133 });

	Render0->CreateAnimation({ "LDown45Move", "Snowwoman.png",134,143 });
	Render0->CreateAnimation({ "LMove", "Snowwoman.png",144,153 });
	Render0->CreateAnimation({ "LUp45Move", "Snowwoman.png",154,163 });
	Render0->CreateAnimation({ "UpMove", "Snowwoman.png",164,173 });
	Render0->CreateAnimation({ "DownMove", "Snowwoman.png",174,183 });

	Render0->CreateAnimation({ "LDown45Attack", "Snowwoman.png",0,12,AttackSpeed / 13.f });
	Render0->CreateAnimation({ "LAttack", "Snowwoman.png",13,25,AttackSpeed / 13.f });
	Render0->CreateAnimation({ "LUp45Attack", "Snowwoman.png",26,38,AttackSpeed / 13.f });
	Render0->CreateAnimation({ "UpAttack", "Snowwoman.png",39,51,AttackSpeed / 13.f });
	Render0->CreateAnimation({ "DownAttack", "Snowwoman.png",52,64,AttackSpeed / 13.f });

	Render0->CreateAnimation({ "Die", "Snowwoman.png",65,83,0.1f,false });


	Render0->ChangeAnimation("LStay");

	Minion::Start();

}

// 이건 디버깅용도나 
void Snowwoman::Render(float _Delta)
{



};
