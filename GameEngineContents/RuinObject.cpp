#include "PrecompileHeader.h"
#include "RuinObject.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineFontRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "ContentsEnum.h"
#include "MapOverlay.h"
#include "MapEditor.h"
#include "Ksword.h"
#include "Karcher.h"
extern float4 MainMouse;
extern  float CalAngle1To2(float4 _Pos1, float4 _Pos2);

RuinObject::RuinObject()
{
}

RuinObject::~RuinObject()
{
}

bool check = false;
void RuinObject::Update(float _DeltaTime)
{
	Building::Update(_DeltaTime);
	if (GetLiveTime() > 2.f&&check==false)
	{
		//FSM.ChangeState("Die");
		ArrEnemyunit();
		check = true;
	}
	float4 Pos = GetTransform()->GetLocalPosition();
	float4 Pos2 =Render0->GetTransform()->GetLocalPosition();
	Collision->GetTransform()->SetLocalScale(Render0->GetTransform()->GetLocalScale());
	/*std::string str3 = MapEditor::ConvertPosToTileXY(ShortTargetPos).ToString();
	std::string str4 =std::to_string(TestDistance);
	str3 += "\n";
	str3 += str4;
	FontRender0->SetText(str3);*/
}
//
void RuinObject::Start()
{
	if (nullptr == GameEngineSprite::Find("exp11.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Boom");
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("exp11.png").GetFullPath(), 5, 4);
	}
	if (nullptr == GameEngineSprite::Find("RUINobject0.tga"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Building");
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("RUINobject0.tga").GetFullPath(), 1, 1);
	}

	Render0 = CreateComponent<GameEngineSpriteRenderer>();
	//Render0->SetTexture("RUINobject0.tga");
	//Render0->GetTransform()->SetLocalScale({ 100.f,100.f });
	Render0->CreateAnimation({ "Stay", "RUINobject0.tga",0,0,0.1f,true,true });	
	Render0->CreateAnimation({ "Die", "exp11.png",0,18,0.1f,false,true });
	Render0->SetScaleRatio(1.5f);
	Collision = CreateComponent<GameEngineCollision>();
	//float4 sdsd = Render0->GetTransform()->GetLocalScale();
	
	Collision->SetColType(ColType::AABBBOX2D);
	Collision->SetOrder(static_cast<int>(ColEnum::Building));
	

	MyTeam = Team::Enemy;
	MyBuildingType = BuildingType::IncludeUnit;

	//Speed = 500.f;
	{
		FontRender0 = CreateComponent<GameEngineFontRenderer>();
		//FontRender0->GetTransform()->SetParent(NewObject->GetTransform());
		FontRender0->SetFont("휴먼둥근헤드라인");
		FontRender0->SetScale({ 20.f });
		FontRender0->GetTransform()->SetLocalPosition({ 0,20.f });
	}
	Building::Start();
	
	EnemyNum = GameEngineRandom::MainRandom.RandomInt(4, 6);
	EnemyUnits.resize(EnemyNum);
	for (int i = 0; i < EnemyNum; i++)
	{
		EnemyUnits[i] = GetLevel()->CreateActor<Ksword>();
		EnemyUnits[i]->Off();
	}
}

// 이건 디버깅용도나 
void RuinObject::Render(float _Delta)
{

};
