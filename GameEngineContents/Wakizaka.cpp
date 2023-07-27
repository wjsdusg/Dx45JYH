#include "PrecompileHeader.h"
#include "Wakizaka.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "DefenseMapEditor.h"
Wakizaka::Wakizaka()
{
}

Wakizaka::~Wakizaka()
{
}


void Wakizaka::Update(float _DeltaTime)
{
	Unit::Update(_DeltaTime);
	float4 sd = Render0->GetTransform()->GetLocalScale();
	float4 sdsd = Render0->GetTransform()->GetLocalPosition();
}

void Wakizaka::Start()
{



	if (nullptr == GameEngineSprite::Find("WakizakaDie"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Heros");
		NewDir.Move("Japan");
		NewDir.Move("Wakizaka");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("WakizakaDie").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("WakizakaDownAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("WakizakaDownMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("WakizakaDownStay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("WakizakaLAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("WakizakaLDown45Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("WakizakaLDown45Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("WakizakaLDown45Stay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("WakizakaLMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("WakizakaLStay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("WakizakaLUp45Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("WakizakaLUp45Move").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("WakizakaLUp45Stay").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("WakizakaUpAttack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("WakizakaUpMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("WakizakaUpStay").GetFullPath());
	}
	Render0 = CreateComponent<GameEngineSpriteRenderer>();



	Render0->CreateAnimation({ .AnimationName = "Die", .SpriteName = "WakizakaDie", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "DownAttack", .SpriteName = "WakizakaDownAttack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "DownMove", .SpriteName = "WakizakaDownMove", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "DownStay", .SpriteName = "WakizakaDownStay",.FrameInter = 0.2f, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LAttack", .SpriteName = "WakizakaLAttack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LDown45Attack", .SpriteName = "WakizakaLDown45Attack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LDown45Move", .SpriteName = "WakizakaLDown45Move", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LDown45Stay", .SpriteName = "WakizakaLDown45Stay",.FrameInter = 0.2f,.ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LMove", .SpriteName = "WakizakaLMove", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LStay", .SpriteName = "WakizakaLStay",.FrameInter = 0.2f, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LUp45Attack", .SpriteName = "WakizakaLUp45Attack",.FrameInter = AttackSpeed / 10,.ScaleToTexture = true });;
	Render0->CreateAnimation({ .AnimationName = "LUp45Move", .SpriteName = "WakizakaLUp45Move", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "LUp45Stay", .SpriteName = "WakizakaLUp45Stay",.FrameInter = 0.2f, .ScaleToTexture = true });;
	Render0->CreateAnimation({ .AnimationName = "UpAttack", .SpriteName = "WakizakaUpAttack",.FrameInter = AttackSpeed / 10, .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "UpMove", .SpriteName = "WakizakaUpMove", .ScaleToTexture = true });
	Render0->CreateAnimation({ .AnimationName = "UpStay", .SpriteName = "WakizakaUpStay",.FrameInter = 0.2f, .ScaleToTexture = true });;

	Render0->ChangeAnimation("LStay");

	GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(1, 1));
	MyTeam = Team::Mine;
	MyAttackType = AttackType::Near;

	Unit::Start();
	Hero::Start();
}

// 이건 디버깅용도나 
void Wakizaka::Render(float _Delta)
{

};
