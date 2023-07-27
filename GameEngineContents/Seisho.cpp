#include "PrecompileHeader.h"
#include "Seisho.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "DefenseMapEditor.h"
Seisho::Seisho()
{
}

Seisho::~Seisho()
{
}


void Seisho::Update(float _DeltaTime)
{
	Unit::Update(_DeltaTime);
	float4 sd = Render0->GetTransform()->GetLocalScale();
	float4 sdsd = Render0->GetTransform()->GetLocalPosition();
}

void Seisho::Start()
{



	if (nullptr == GameEngineSprite::Find("SeishoDie"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Heros");
		NewDir.Move("Japan");
		NewDir.Move("Seisho");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SeishoDie").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SeishoDownAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SeishoDownMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SeishoDownStay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SeishoLAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SeishoLDown45Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SeishoLDown45Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SeishoLDown45Stay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SeishoLMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SeishoLStay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SeishoLUp45Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SeishoLUp45Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SeishoLUp45Stay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SeishoUpAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SeishoUpMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SeishoUpStay").GetFullPath());
	}
	Render0 = CreateComponent<GameEngineSpriteRenderer>();



	Render0->CreateAnimation({ .AnimationName = "Die", .SpriteName = "SeishoDie", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "DownAttack", .SpriteName = "SeishoDownAttack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "DownMove", .SpriteName = "SeishoDownMove", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "DownStay", .SpriteName = "SeishoDownStay",.FrameInter = 0.2f, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LAttack", .SpriteName = "SeishoLAttack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LDown45Attack", .SpriteName = "SeishoLDown45Attack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LDown45Move", .SpriteName = "SeishoLDown45Move", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LDown45Stay", .SpriteName = "SeishoLDown45Stay",.FrameInter = 0.2f,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LMove", .SpriteName = "SeishoLMove", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LStay", .SpriteName = "SeishoLStay",.FrameInter = 0.2f, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LUp45Attack", .SpriteName = "SeishoLUp45Attack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });;
	Render0->CreateAnimation({ .AnimationName = "LUp45Move", .SpriteName = "SeishoLUp45Move", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LUp45Stay", .SpriteName = "SeishoLUp45Stay",.FrameInter = 0.2f, .ScaleToTexture = true });;
	Render0->CreateAnimation({ .AnimationName = "UpAttack", .SpriteName = "SeishoUpAttack",.FrameInter = AttackSpeed / 10, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "UpMove", .SpriteName = "SeishoUpMove", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "UpStay", .SpriteName = "SeishoUpStay",.FrameInter = 0.2f, .ScaleToTexture = true });;

	Render0->ChangeAnimation("LStay");

	GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(1, 1));
	MyTeam = Team::Mine;
	MyAttackType = AttackType::Near;

	Unit::Start();
	Hero::Start();
}

// 이건 디버깅용도나 
void Seisho::Render(float _Delta)
{

};
