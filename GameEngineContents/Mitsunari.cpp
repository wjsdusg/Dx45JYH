#include "PrecompileHeader.h"
#include "Mitsunari.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "DefenseMapEditor.h"
Mitsunari::Mitsunari()
{
}

Mitsunari::~Mitsunari()
{
}


void Mitsunari::Update(float _DeltaTime)
{
	Unit::Update(_DeltaTime);
	float4 sd = Render0->GetTransform()->GetLocalScale();
	float4 sdsd = Render0->GetTransform()->GetLocalPosition();
}

void Mitsunari::Start()
{



	if (nullptr == GameEngineSprite::Find("MitsunariDie"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Heros");
		NewDir.Move("Japan");
		NewDir.Move("Mitsunari");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("MitsunariDie").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("MitsunariDownAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("MitsunariDownMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("MitsunariDownStay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("MitsunariLAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("MitsunariLDown45Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("MitsunariLDown45Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("MitsunariLDown45Stay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("MitsunariLMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("MitsunariLStay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("MitsunariLUp45Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("MitsunariLUp45Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("MitsunariLUp45Stay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("MitsunariUpAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("MitsunariUpMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("MitsunariUpStay").GetFullPath());
	}
	Render0 = CreateComponent<GameEngineSpriteRenderer>();



	Render0->CreateAnimation({ .AnimationName = "Die", .SpriteName = "MitsunariDie", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "DownAttack", .SpriteName = "MitsunariDownAttack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "DownMove", .SpriteName = "MitsunariDownMove", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "DownStay", .SpriteName = "MitsunariDownStay",.FrameInter = 0.2f, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LAttack", .SpriteName = "MitsunariLAttack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LDown45Attack", .SpriteName = "MitsunariLDown45Attack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LDown45Move", .SpriteName = "MitsunariLDown45Move", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LDown45Stay", .SpriteName = "MitsunariLDown45Stay",.FrameInter = 0.2f,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LMove", .SpriteName = "MitsunariLMove", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LStay", .SpriteName = "MitsunariLStay",.FrameInter = 0.2f, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LUp45Attack", .SpriteName = "MitsunariLUp45Attack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });;
	Render0->CreateAnimation({ .AnimationName = "LUp45Move", .SpriteName = "MitsunariLUp45Move", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LUp45Stay", .SpriteName = "MitsunariLUp45Stay",.FrameInter = 0.2f, .ScaleToTexture = true });;
	Render0->CreateAnimation({ .AnimationName = "UpAttack", .SpriteName = "MitsunariUpAttack",.FrameInter = AttackSpeed / 10, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "UpMove", .SpriteName = "MitsunariUpMove", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "UpStay", .SpriteName = "MitsunariUpStay",.FrameInter = 0.2f, .ScaleToTexture = true });;

	Render0->ChangeAnimation("LStay");

	GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(1, 1));
	MyTeam = Team::Mine;
	MyAttackType = AttackType::Near;

	Unit::Start();
	Hero::Start();
}

// 이건 디버깅용도나 
void Mitsunari::Render(float _Delta)
{

};
