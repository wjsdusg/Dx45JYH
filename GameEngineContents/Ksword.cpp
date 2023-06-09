#include "PrecompileHeader.h"
#include "Ksword.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineVideo.h>
#include <GameEngineCore/GameEngineSprite.h>
#include "TestObject.h"
extern float4 MainMouse;
extern  float CalAngle1To2(float4 _Pos1, float4 _Pos2);
Ksword::Ksword()
{
}

Ksword::~Ksword()
{
}


void Ksword::Update(float _DeltaTime)
{
	MouseData.SPHERE.Center = MainMouse.DirectFloat3;
	MouseData.SPHERE.Radius = 0.0f;

	

	if (true == GameEngineTransform::AABB2DToSpehre2D(Render0->GetTransform()->GetCollisionData(), MouseData))
	{
		
		if (true == GameEngineInput::IsUp("EngineMouseLeft"))
		{
			IsClick = true;
			if (nullptr == SelectionCircle)
			{
				SelectionCircle = CreateComponent<GameEngineSpriteRenderer>();
				//SelectionCircle->GetTransform()->SetLocalPosition({ 0,-20.f,1.f });
				
				SelectionCircle->GetTransform()->SetLocalScale({ 10.f,10.f });								
			}
		}
	}
	if (true == GameEngineInput::IsUp("EngineMouseRight")&&true==IsClick)
	{
		MousePickPos = MainMouse;
		IsMove = true;
	}
	float aa = abs(MousePickPos.Size() - GetTransform()->GetLocalPosition().Size());
	float gg = MousePickPos.XYDistance(GetTransform()->GetLocalPosition());
	if (MousePickPos.XYDistance(GetTransform()->GetLocalPosition()) <= 1.f)
	{
		IsMove = false;
	}
	if (true==IsMove )
	{
		
		//GetTransform()->SetLocalPosition(MovePointTowardsTarget(GetTransform()->GetLocalPosition(), MousePickPos, Speed, _DeltaTime));

		GetTransform()->AddLocalPosition(MovePointTowardsTarget(GetTransform()->GetLocalPosition(), MousePickPos, Speed, _DeltaTime));
	}
		
}

void Ksword::Start()
{	
	GetTransform()->SetLocalPosition({ 0.f,-200.f });
	//MousePickPos = GetTransform()->GetLocalPosition();
	if (nullptr == GameEngineSprite::Find("kword"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("kword").GetFullPath());
	}
	Render0 = CreateComponent<GameEngineSpriteRenderer>();
	
	Render0->GetTransform()->SetLocalScale({ 40.f,40.f });
	Render0->CreateAnimation({ .AnimationName = "Run", .SpriteName = "kword", .ScaleToTexture = false });
	Render0->ChangeAnimation("Run");		
}

// 이건 디버깅용도나 
void Ksword::Render(float _Delta)
{

};
