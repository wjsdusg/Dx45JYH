#include "PrecompileHeader.h"
#include "Tokugawa.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "DefenseMapEditor.h"
Tokugawa::Tokugawa()
{
}

Tokugawa::~Tokugawa()
{
}


void Tokugawa::Update(float _DeltaTime)
{
	Unit::Update(_DeltaTime);
	float4 sd = Render0->GetTransform()->GetLocalScale();
	float4 sdsd = Render0->GetTransform()->GetLocalPosition();
}

void Tokugawa::Start()
{



	if (nullptr == GameEngineSprite::Find("TokugawaDie"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Heros");
		NewDir.Move("Japan");
		NewDir.Move("Tokugawa");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TokugawaDie").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TokugawaDownAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TokugawaDownMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TokugawaDownStay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TokugawaLAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TokugawaLDown45Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TokugawaLDown45Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TokugawaLDown45Stay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TokugawaLMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TokugawaLStay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TokugawaLUp45Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TokugawaLUp45Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TokugawaLUp45Stay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TokugawaUpAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TokugawaUpMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("TokugawaUpStay").GetFullPath());
	}
	Render0 = CreateComponent<GameEngineSpriteRenderer>();



	Render0->CreateAnimation({ .AnimationName = "Die", .SpriteName = "TokugawaDie", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "DownAttack", .SpriteName = "TokugawaDownAttack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "DownMove", .SpriteName = "TokugawaDownMove", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "DownStay", .SpriteName = "TokugawaDownStay",.FrameInter = 0.2f, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LAttack", .SpriteName = "TokugawaLAttack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LDown45Attack", .SpriteName = "TokugawaLDown45Attack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LDown45Move", .SpriteName = "TokugawaLDown45Move", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LDown45Stay", .SpriteName = "TokugawaLDown45Stay",.FrameInter = 0.2f,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LMove", .SpriteName = "TokugawaLMove", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LStay", .SpriteName = "TokugawaLStay",.FrameInter = 0.2f, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LUp45Attack", .SpriteName = "TokugawaLUp45Attack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });;
	Render0->CreateAnimation({ .AnimationName = "LUp45Move", .SpriteName = "TokugawaLUp45Move", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LUp45Stay", .SpriteName = "TokugawaLUp45Stay",.FrameInter = 0.2f, .ScaleToTexture = true });;
	Render0->CreateAnimation({ .AnimationName = "UpAttack", .SpriteName = "TokugawaUpAttack",.FrameInter = AttackSpeed / 10, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "UpMove", .SpriteName = "TokugawaUpMove", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "UpStay", .SpriteName = "TokugawaUpStay",.FrameInter = 0.2f, .ScaleToTexture = true });;

	Render0->ChangeAnimation("LStay");

	GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(1, 1));
	MyTeam = Team::Mine;
	MyAttackType = AttackType::Near;

	Unit::Start();
	Hero::Start();
}

// 이건 디버깅용도나 
void Tokugawa::Render(float _Delta)
{

};
