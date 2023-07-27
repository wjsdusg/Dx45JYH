#include "PrecompileHeader.h"
#include "Gonisi.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "DefenseMapEditor.h"
Gonisi::Gonisi()
{
}

Gonisi::~Gonisi()
{
}


void Gonisi::Update(float _DeltaTime)
{
	Unit::Update(_DeltaTime);
	float4 sd = Render0->GetTransform()->GetLocalScale();
	float4 sdsd = Render0->GetTransform()->GetLocalPosition();
}

void Gonisi::Start()
{



	if (nullptr == GameEngineSprite::Find("GonisiDie"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Heros");
		NewDir.Move("Japan");
		NewDir.Move("Gonisi");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GonisiDie").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GonisiDownAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GonisiDownMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GonisiDownStay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GonisiLAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GonisiLDown45Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GonisiLDown45Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GonisiLDown45Stay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GonisiLMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GonisiLStay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GonisiLUp45Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GonisiLUp45Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GonisiLUp45Stay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GonisiUpAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GonisiUpMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("GonisiUpStay").GetFullPath());
	}
	Render0 = CreateComponent<GameEngineSpriteRenderer>();

	

	Render0->CreateAnimation({ .AnimationName = "Die", .SpriteName = "GonisiDie", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "DownAttack", .SpriteName = "GonisiDownAttack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "DownMove", .SpriteName = "GonisiDownMove", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "DownStay", .SpriteName = "GonisiDownStay",.FrameInter =0.2f, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LAttack", .SpriteName = "GonisiLAttack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LDown45Attack", .SpriteName = "GonisiLDown45Attack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LDown45Move", .SpriteName = "GonisiLDown45Move", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LDown45Stay", .SpriteName = "GonisiLDown45Stay",.FrameInter = 0.2f,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LMove", .SpriteName = "GonisiLMove", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LStay", .SpriteName = "GonisiLStay",.FrameInter = 0.2f, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LUp45Attack", .SpriteName = "GonisiLUp45Attack",.FrameInter = AttackSpeed/10,.ScaleToTexture = true });;
	Render0->CreateAnimation({ .AnimationName = "LUp45Move", .SpriteName = "GonisiLUp45Move", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LUp45Stay", .SpriteName = "GonisiLUp45Stay",.FrameInter = 0.2f, .ScaleToTexture = true });;
	Render0->CreateAnimation({ .AnimationName = "UpAttack", .SpriteName = "GonisiUpAttack",.FrameInter = AttackSpeed / 10, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "UpMove", .SpriteName = "GonisiUpMove", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "UpStay", .SpriteName = "GonisiUpStay",.FrameInter = 0.2f, .ScaleToTexture = true });;

	Render0->ChangeAnimation("LStay");
	
	GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(1, 1));
	MyTeam = Team::Mine;
	MyAttackType = AttackType::Near;
	
	Unit::Start();
	Hero::Start();
}

// �̰� �����뵵�� 
void Gonisi::Render(float _Delta)
{

};
