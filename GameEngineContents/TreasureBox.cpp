#include "PrecompileHeader.h"
#include "TreasureBox.h"
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

TreasureBox::TreasureBox()
{
}

TreasureBox::~TreasureBox()
{
}


void TreasureBox::Update(float _DeltaTime)
{
	Building::Update(_DeltaTime);

	float4 Pos = GetTransform()->GetLocalPosition();
	float4 Pos2 = Render0->GetTransform()->GetLocalPosition();
	Collision->GetTransform()->SetLocalScale(Render0->GetTransform()->GetLocalScale());
	std::string str3 = std::to_string(Gage);	
	FontRender0->SetText(str3);
	if (nullptr != Collision->Collision(static_cast<int>(ColEnum::Unit), ColType::AABBBOX2D, ColType::AABBBOX2D)&&false==IsOpen)
	{
		
		 RealGage  += _DeltaTime;
		 if (0.03 <= RealGage)
		 {
			 Gage += 1;
			 RealGage = 0;
		 }
		 if (100 <= Gage)
		 {
			 Gage = 100;
			 IsOpen = true;
			 FSM.ChangeState("Die");
		 }
	}
	else
	{
		Gage = 0;
	}
}
//
void TreasureBox::Start()
{
	if (nullptr == GameEngineSprite::Find("boxC0.tga"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Building");
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("boxC0.tga").GetFullPath(), 1, 1);
	}

	if (nullptr == GameEngineSprite::Find("boxCopen"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Building");
		
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("boxCopen").GetFullPath());
		
	}
	

	Render0 = CreateComponent<GameEngineSpriteRenderer>();
	Render0->CreateAnimation({ .AnimationName = "Die", .SpriteName = "boxCopen",.FrameInter = 0.2f,.Loop = false,.ScaleToTexture = true ,});
	Render0->CreateAnimation({ "Stay", "boxC0.tga",0,0,10.f,true,true });
	Render0->SetFlipX();
	//Render0->SetScaleRatio(1.5f);
	Collision = CreateComponent<GameEngineCollision>();
	Collision->SetColType(ColType::AABBBOX2D);
	Collision->SetOrder(static_cast<int>(ColEnum::Treasure));

	


	Building::Start();


}

// 이건 디버깅용도나 
void TreasureBox::Render(float _Delta)
{

};
