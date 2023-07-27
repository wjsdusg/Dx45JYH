#include "PrecompileHeader.h"
#include "Gato.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "DefenseMapEditor.h"
Gato::Gato()
{
}

Gato::~Gato()
{
}


void Gato::Update(float _DeltaTime)
{
	Unit::Update(_DeltaTime);
	float4 sd = Render0->GetTransform()->GetLocalScale();
	float4 sdsd = Render0->GetTransform()->GetLocalPosition();
}

void Gato::Start()
{



	if (nullptr == GameEngineSprite::Find("GatoDie"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Heros");
		NewDir.Move("Japan");
		NewDir.Move("Gato");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GatoDie").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GatoDownAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GatoDownMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GatoDownStay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GatoLAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GatoLDown45Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GatoLDown45Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GatoLDown45Stay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GatoLMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GatoLStay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GatoLUp45Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GatoLUp45Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GatoLUp45Stay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GatoUpAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GatoUpMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GatoUpStay").GetFullPath());
	}
	Render0 = CreateComponent<GameEngineSpriteRenderer>();


	Render0->CreateAnimation({ .AnimationName = "Die", .SpriteName = "GatoDie", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "DownAttack", .SpriteName = "GatoDownAttack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "DownMove", .SpriteName = "GatoDownMove", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "DownStay", .SpriteName = "GatoDownStay",.FrameInter = 0.2f, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LAttack", .SpriteName = "GatoLAttack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LDown45Attack", .SpriteName = "GatoLDown45Attack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LDown45Move", .SpriteName = "GatoLDown45Move", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LDown45Stay", .SpriteName = "GatoLDown45Stay",.FrameInter = 0.2f,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LMove", .SpriteName = "GatoLMove", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LStay", .SpriteName = "GatoLStay",.FrameInter = 0.2f, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LUp45Attack", .SpriteName = "GatoLUp45Attack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });;
	Render0->CreateAnimation({ .AnimationName = "LUp45Move", .SpriteName = "GatoLUp45Move", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LUp45Stay", .SpriteName = "GatoLUp45Stay",.FrameInter = 0.2f, .ScaleToTexture = true });;
	Render0->CreateAnimation({ .AnimationName = "UpAttack", .SpriteName = "GatoUpAttack",.FrameInter = AttackSpeed / 10, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "UpMove", .SpriteName = "GatoUpMove", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "UpStay", .SpriteName = "GatoUpStay",.FrameInter = 0.2f, .ScaleToTexture = true });;

	Render0->ChangeAnimation("LStay");
	GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(1, 1));
	MyTeam = Team::Mine;
	MyAttackType = AttackType::Near;
	Unit::Start();
	Hero::Start();
}

// 이건 디버깅용도나 
void Gato::Render(float _Delta)
{

};
