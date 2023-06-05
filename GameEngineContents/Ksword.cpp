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

Ksword::Ksword()
{
}

Ksword::~Ksword()
{
}


void Ksword::Update(float _DeltaTime)
{


	std::vector<std::shared_ptr<GameEngineCollision>> ColTest;



}

void Ksword::Start()
{
	if (nullptr == GameEngineSprite::Find("kword"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");

		// TestAnimation.png

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("kword").GetFullPath());
	
	
	}

	Render0 = CreateComponent<GameEngineSpriteRenderer>();

	Render0->CreateAnimation({ .AnimationName = "Run", .SpriteName = "kword", .ScaleToTexture = true });
		
	
	Render0->SetScaleRatio(2.0f);
	Render0->ChangeAnimation("Run");
	//Render0->GetTransform()->SetLocalScale({ (GameEngineWindow::GetScreenSize().x ), (GameEngineWindow::GetScreenSize().y ), 0.f, 0.f });


}

// 이건 디버깅용도나 
void Ksword::Render(float _Delta)
{

};
