#include "PrecompileHeader.h"
#include "NormalObject1.h"
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

NormalObject1::NormalObject1()
{
}

NormalObject1::~NormalObject1()
{
}


void NormalObject1::Update(float _DeltaTime)
{
	Building::Update(_DeltaTime);
	
	float4 Pos = GetTransform()->GetLocalPosition();
	float4 Pos2 = Render0->GetTransform()->GetLocalPosition();
	Collision->GetTransform()->SetLocalScale(Render0->GetTransform()->GetLocalScale());
	/*std::string str3 = MapEditor::ConvertPosToTileXY(ShortTargetPos).ToString();
	std::string str4 =std::to_string(TestDistance);
	str3 += "\n";
	str3 += str4;
	FontRender0->SetText(str3);*/
}
//
void NormalObject1::Start()
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
	if (nullptr == GameEngineSprite::Find("Arm1.tga"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Building");
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Arm0.tga").GetFullPath(), 1, 1);
	}

	Render0 = CreateComponent<GameEngineSpriteRenderer>();
	
	Render0->CreateAnimation({ "Stay", "Arm0.tga",0,0,0.1f,true,true });
	Render0->CreateAnimation({ "Die", "exp11.png",0,18,0.1f,false,true });
	//Render0->SetScaleRatio(1.5f);
	Collision = CreateComponent<GameEngineCollision>();
	Collision->SetColType(ColType::AABBBOX2D);
	Collision->SetOrder(static_cast<int>(ColEnum::Unit));

	MyTeam = Team::Enemy;
	MyBuildingType = BuildingType::NotUnit;


	Building::Start();

	
}

// 이건 디버깅용도나 
void NormalObject1::Render(float _Delta)
{

};
