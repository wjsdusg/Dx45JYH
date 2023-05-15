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

	// Render0->GetTransform()->SetWorldRotation(float4::Zero);

	if (true == GameEngineInput::IsPress("PlayerSpeedBoost"))
	{
		Speed = 500.0f;
	}

	if (true == GameEngineInput::IsDown("PlayerMoveLeft"))
	{
		GetTransform()->SetLocalNegativeScaleX();
	}
	else if (true == GameEngineInput::IsDown("PlayerMoveRight"))
	{
		GetTransform()->SetLocalPositiveScaleX();
	}

	if (true == GameEngineInput::IsPress("PlayerMoveLeft"))
	{
		GetTransform()->AddLocalPosition(float4::Left * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("PlayerMoveRight"))
	{
		GetTransform()->AddLocalPosition(float4::Right * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("PlayerMoveUp"))
	{
		GetTransform()->AddLocalPosition(float4::Up * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("PlayerMoveDown"))
	{
		GetTransform()->AddLocalPosition(float4::Down * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("PlayerMoveForward"))
	{
		GetTransform()->AddLocalPosition(GetTransform()->GetLocalForwardVector() * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("PlayerMoveBack"))
	{
		GetTransform()->AddLocalPosition(float4::Back * Speed * _DeltaTime);
	}

	if (true == GameEngineInput::IsPress("PlayerRotY+"))
	{
		GetTransform()->AddLocalRotation({ 0.0f, RotSpeed * _DeltaTime, 0.0f });
	}
	if (true == GameEngineInput::IsPress("PlayerRotY-"))
	{
		GetTransform()->AddLocalRotation({ 0.0f, -RotSpeed * _DeltaTime, 0.0f });
	}
	if (true == GameEngineInput::IsPress("PlayerRotZ+"))
	{
		GetTransform()->AddLocalRotation({ 0.0f, 0.0f, RotSpeed * _DeltaTime });
	}
	if (true == GameEngineInput::IsPress("PlayerRotZ-"))
	{
		GetTransform()->AddLocalRotation({ 0.0f, 0.0f, -RotSpeed * _DeltaTime });
	}
	if (true == GameEngineInput::IsPress("PlayerRotX+"))
	{
		GetTransform()->AddLocalRotation({ RotSpeed * _DeltaTime, 0.0f, 0.0f });
	}
	if (true == GameEngineInput::IsPress("PlayerRotX-"))
	{
		GetTransform()->AddLocalRotation({ -RotSpeed * _DeltaTime, 0.0f, 0.0f });
	}

	float ScaleSpeed = 10.0f;

	if (true == GameEngineInput::IsPress("PlayerScaleY+"))
	{
		GetTransform()->AddLocalScale({ 0.0f, ScaleSpeed * _DeltaTime, 0.0f });
	}
	if (true == GameEngineInput::IsPress("PlayerScaleY-"))
	{
		GetTransform()->AddLocalScale({ 0.0f, -ScaleSpeed * _DeltaTime, 0.0f });
	}
	if (true == GameEngineInput::IsPress("PlayerScaleZ+"))
	{
		GetTransform()->AddLocalScale({ 0.0f, 0.0f, ScaleSpeed * _DeltaTime });
	}
	if (true == GameEngineInput::IsPress("PlayerScaleZ-"))
	{
		GetTransform()->AddLocalScale({ 0.0f, 0.0f, -ScaleSpeed * _DeltaTime });
	}
	if (true == GameEngineInput::IsPress("PlayerScaleX+"))
	{
		GetTransform()->AddLocalScale({ ScaleSpeed * _DeltaTime, 0.0f, 0.0f });
	}
	if (true == GameEngineInput::IsPress("PlayerScaleX-"))
	{
		GetTransform()->AddLocalScale({ -ScaleSpeed * _DeltaTime, 0.0f, 0.0f });
	}

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
	if (false == GameEngineInput::IsKey("PlayerMoveLeft"))
	{
		GameEngineInput::CreateKey("PlayerMoveLeft", 'A');
		GameEngineInput::CreateKey("PlayerMoveRight", 'D');
		GameEngineInput::CreateKey("PlayerMoveUp", 'Q');
		GameEngineInput::CreateKey("PlayerMoveDown", 'E');
		GameEngineInput::CreateKey("PlayerMoveForward", 'W');
		GameEngineInput::CreateKey("PlayerMoveBack", 'S');

		GameEngineInput::CreateKey("PlayerScaleY+", 'Y');
		GameEngineInput::CreateKey("PlayerScaleY-", 'U');
		GameEngineInput::CreateKey("PlayerScaleZ+", 'H');
		GameEngineInput::CreateKey("PlayerScaleZ-", 'J');
		GameEngineInput::CreateKey("PlayerScaleX+", 'N');
		GameEngineInput::CreateKey("PlayerScaleX-", 'M');


		GameEngineInput::CreateKey("PlayerRotY+", VK_NUMPAD1);
		GameEngineInput::CreateKey("PlayerRotY-", VK_NUMPAD2);
		GameEngineInput::CreateKey("PlayerRotZ+", VK_NUMPAD4);
		GameEngineInput::CreateKey("PlayerRotZ-", VK_NUMPAD5);
		GameEngineInput::CreateKey("PlayerRotX+", VK_NUMPAD7);
		GameEngineInput::CreateKey("PlayerRotX-", VK_NUMPAD8);
		GameEngineInput::CreateKey("PlayerSpeedBoost", VK_LSHIFT);
	}
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

		// TestAnimation.png

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("PlayerRun").GetFullPath());

		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Test\\TestAnimation.png").GetFullPath(), 3, 5);

		// std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
	}

	{
		Collsion = CreateComponent<GameEngineCollision>();
		Collsion->GetTransform()->SetLocalScale({ 100.0f, 100.0f, 100.0f });
		Collsion->SetOrder(3000);
	}



	// 나는 스케일을 1로 고정해 놓는게 좋다.
	Render0 = CreateComponent<GameEngineSpriteRenderer>();
	// Render0->SetOrder(5);
	Render0->SetScaleToTexture("Test.png");
	// Render0->CreateAnimation({ "Run", "PlayerRun", 0.01f, -1, -1, true, true });

	Render0->CreateAnimation({ .AnimationName = "Run", .SpriteName = "PlayerRun", .ScaleToTexture = true });
	Render0->CreateAnimation({ "Win", "TestAnimation.png", 0, 5, 0.1f, true, true });

	Render0->SetAnimationStartEvent("Win", 5, [this]
		{
			//std::shared_ptr<TestObject> Actor = GetLevel()->CreateActor<TestObject>();
			//Actor->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
			//Actor->GetTransform()->SetLocalScale({100.0f, 100.0f, 1.0f});
		});

	Render0->SetScaleRatio(5.0f);

	Render0->ChangeAnimation("Win");

	TestColor = { 0.0f, 0.0f, 0.0f, 1.0f };
}

// 이건 디버깅용도나 
void Player::Render(float _Delta)
{
	// GetTransform()->AddLocalRotation({0.0f, 0.0f, 360.0f * _Delta});
};
