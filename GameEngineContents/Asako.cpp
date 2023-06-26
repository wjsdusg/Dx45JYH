#include "PrecompileHeader.h"
#include "Asako.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

Asako::Asako()
{
}

Asako::~Asako()
{
}


void Asako::Update(float _DeltaTime)
{
	Unit::Update(_DeltaTime);
	
}

void Asako::Start()
{



	if (nullptr == GameEngineSprite::Find("AsakoDie"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Heros");
		NewDir.Move("Japan");
		NewDir.Move("Asako");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AsakoDie").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AsakoDownAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AsakoDownMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AsakoDownStay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AsakoLAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AsakoLDown45Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AsakoLDown45Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AsakoLDown45Stay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AsakoLMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AsakoLStay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AsakoLUp45Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AsakoLUp45Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AsakoLUp45Stay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AsakoUpAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AsakoUpMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AsakoUpStay").GetFullPath());
	}
	Render0 = CreateComponent<GameEngineSpriteRenderer>();



	Render0->CreateAnimation({ .AnimationName = "Die", .SpriteName = "AsakoDie", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "DownAttack", .SpriteName = "AsakoDownAttack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "DownMove", .SpriteName = "AsakoDownMove", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "DownStay", .SpriteName = "AsakoDownStay",.FrameInter = 0.2f, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LAttack", .SpriteName = "AsakoLAttack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LDown45Attack", .SpriteName = "AsakoLDown45Attack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LDown45Move", .SpriteName = "AsakoLDown45Move", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LDown45Stay", .SpriteName = "AsakoLDown45Stay",.FrameInter = 0.2f,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LMove", .SpriteName = "AsakoLMove", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LStay", .SpriteName = "AsakoLStay",.FrameInter = 0.2f, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LUp45Attack", .SpriteName = "AsakoLUp45Attack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });;
	Render0->CreateAnimation({ .AnimationName = "LUp45Move", .SpriteName = "AsakoLUp45Move", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LUp45Stay", .SpriteName = "AsakoLUp45Stay",.FrameInter = 0.2f, .ScaleToTexture = true });;
	Render0->CreateAnimation({ .AnimationName = "UpAttack", .SpriteName = "AsakoUpAttack",.FrameInter = AttackSpeed / 10, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "UpMove", .SpriteName = "AsakoUpMove", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "UpStay", .SpriteName = "AsakoUpStay",.FrameInter = 0.2f, .ScaleToTexture = true });;

	Render0->ChangeAnimation("LStay");

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform()->SetLocalScale({ 40.f,40.f,1.f });
	Collision->SetOrder(static_cast<int>(ColEnum::Unit));

	FOVCollision = CreateComponent<GameEngineCollision>();
	FOVCollision->GetTransform()->SetLocalScale({ 400,400,1.f });
	FOVCollision->SetOrder(static_cast<int>(ColEnum::UnitFOV));


	
	Unit::Start();
	Hero::Start();
}

// 이건 디버깅용도나 
void Asako::Render(float _Delta)
{

};
