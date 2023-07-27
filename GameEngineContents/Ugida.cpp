#include "PrecompileHeader.h"
#include "Ugida.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "DefenseMapEditor.h"
Ugida::Ugida()
{
}

Ugida::~Ugida()
{
}


void Ugida::Update(float _DeltaTime)
{
	Unit::Update(_DeltaTime);
	float4 sd = Render0->GetTransform()->GetLocalScale();
	float4 sdsd = Render0->GetTransform()->GetLocalPosition();
}

void Ugida::Start()
{



	if (nullptr == GameEngineSprite::Find("UgidaDie"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Heros");
		NewDir.Move("Japan");
		NewDir.Move("Ugida");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("UgidaDie").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("UgidaDownAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("UgidaDownMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("UgidaDownStay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("UgidaLAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("UgidaLDown45Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("UgidaLDown45Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("UgidaLDown45Stay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("UgidaLMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("UgidaLStay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("UgidaLUp45Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("UgidaLUp45Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("UgidaLUp45Stay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("UgidaUpAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("UgidaUpMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("UgidaUpStay").GetFullPath());
	}
	Render0 = CreateComponent<GameEngineSpriteRenderer>();



	Render0->CreateAnimation({ .AnimationName = "Die", .SpriteName = "UgidaDie", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "DownAttack", .SpriteName = "UgidaDownAttack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "DownMove", .SpriteName = "UgidaDownMove", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "DownStay", .SpriteName = "UgidaDownStay",.FrameInter = 0.2f, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LAttack", .SpriteName = "UgidaLAttack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LDown45Attack", .SpriteName = "UgidaLDown45Attack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LDown45Move", .SpriteName = "UgidaLDown45Move", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LDown45Stay", .SpriteName = "UgidaLDown45Stay",.FrameInter = 0.2f,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LMove", .SpriteName = "UgidaLMove", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LStay", .SpriteName = "UgidaLStay",.FrameInter = 0.2f, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LUp45Attack", .SpriteName = "UgidaLUp45Attack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });;
	Render0->CreateAnimation({ .AnimationName = "LUp45Move", .SpriteName = "UgidaLUp45Move", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LUp45Stay", .SpriteName = "UgidaLUp45Stay",.FrameInter = 0.2f, .ScaleToTexture = true });;
	Render0->CreateAnimation({ .AnimationName = "UpAttack", .SpriteName = "UgidaUpAttack",.FrameInter = AttackSpeed / 10, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "UpMove", .SpriteName = "UgidaUpMove", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "UpStay", .SpriteName = "UgidaUpStay",.FrameInter = 0.2f, .ScaleToTexture = true });;

	Render0->ChangeAnimation("LStay");

	GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(1, 1));
	MyTeam = Team::Mine;
	MyAttackType = AttackType::Near;

	Unit::Start();
	Hero::Start();
}

// 이건 디버깅용도나 
void Ugida::Render(float _Delta)
{

};
