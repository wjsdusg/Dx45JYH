#include "PrecompileHeader.h"
#include "Player.h"
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

Player::Player()
{
}

Player::~Player()
{
}


void Player::Update(float _DeltaTime)
{
	float RotSpeed = 10.0f;

	float Speed = 200.0f;
	
	std::vector<std::shared_ptr<GameEngineCollision>> ColTest;

	if (Collsion->CollisionAll(2000, ColType::SPHERE2D, ColType::SPHERE2D, ColTest), 0 != ColTest.size())
	{
		for (std::shared_ptr<GameEngineCollision> Col : ColTest)
		{
			Col->GetActor()->Death();
		}
		// Col->GetActor()->Death();
	}

}

void Player::Start()
{
	
	//{
//	GameEngineDirectory NewDir;
//	NewDir.MoveParentToDirectory("ContentResources");
//	NewDir.Move("ContentResources");

//	std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });


//	for (size_t i = 0; i < File.size(); i++)
//	{
//		GameEngineTexture::Load(File[i].GetFullPath());
//	}
//}


	if (nullptr == GameEngineSprite::Find("CHAc_Ground_Run"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");


		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PlayerRun").GetFullPath());

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Test\\TestAnimation.png").GetFullPath(), 3, 5);

	}

	{
		Collsion = CreateComponent<GameEngineCollision>();
		Collsion->GetTransform()->SetLocalScale({ 100.0f, 100.0f, 100.0f });
		Collsion->SetOrder(3000);
	}



	Render0 = CreateComponent<GameEngineSpriteRenderer>();
	
	Render0->SetScaleToTexture("Test.png");
	

	Render0->SetScaleRatio(5.0f);

	
}

// 이건 디버깅용도나 
void Player::Render(float _Delta)
{
	// GetTransform()->AddLocalRotation({0.0f, 0.0f, 360.0f * _Delta});
};
