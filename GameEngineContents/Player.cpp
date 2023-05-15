#include "PrecompileHeader.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineVideo.h>

Player::Player()
{
}

Player::~Player()
{
}


void Player::Update(float _DeltaTime)
{
	std::shared_ptr<GameEngineTexture> Ptr = GameEngineTexture::Find("AAAA.png");

	GameEnginePixelColor Pixel = Ptr->GetPixel(356, 329);

	float RotSpeed = 180.0f;

	float Speed = 200.0f;

	// Render0->GetTransform()->SetWorldRotation(float4::Zero);

	if (true == GameEngineInput::IsPress("PlayerSpeedBoost"))
	{
		Speed = 500.0f;
	}

	if (true == GameEngineInput::IsDown("PlayerMoveLeft"))
	{

		//{
		//	GameEngineDirectory NewDir;
		//	NewDir.MoveParentToDirectory("ContentResources");
		//	NewDir.Move("ContentResources");

		//	std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".avi", });

		//	for (size_t i = 0; i < File.size(); i++)
		//	{
		//		GameEngineVideo::Load(File[i].GetFullPath());
		//	}

		//	std::shared_ptr<GameEngineVideo> Video = GameEngineVideo::Find("TestVideo.avi");
		//	Video->Play();
		//}

		// Render0->GetTransform()->SetLocalNegativeScaleX();
	}
	else if (true == GameEngineInput::IsDown("PlayerMoveRight"))
	{
		// Render0->GetTransform()->SetLocalPositiveScaleX();
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
		// GetTransform()->AddLocalPosition(float4::Forward * Speed * _DeltaTime);
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

	float4 GetLocalScale = Render0->GetTransform()->GetLocalScale();
	float4 GetWorldScale = Render0->GetTransform()->GetWorldScale();

	float4 GetLocalRotation = Render0->GetTransform()->GetLocalRotation();
	float4 GetWorldRotation = Render0->GetTransform()->GetWorldRotation();

	float4 GetLocalPosition = Render0->GetTransform()->GetLocalPosition();
	float4 GetWorldPosition = Render0->GetTransform()->GetWorldPosition();

	float4 LocalPostion = GetTransform()->GetLocalPosition();

	GetLevel()->GetMainCamera()->GetTransform()->SetLocalPosition(LocalPostion + (float4::Back * 100.0f));

	//if (5.0f <= Render0->GetLiveTime())
	//{
	//	Render0->Off();
	//}
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


	// ���� �������� 1�� ������ ���°� ����.
	Render0 = CreateComponent<GameEngineSpriteRenderer>();
	// Render0->SetOrder(5);
	Render0->SetScaleToTexture("Test.png");

	TestColor = { 0.0f, 0.0f, 0.0f, 1.0f };
}

// �̰� �����뵵�� 
void Player::Render(float _Delta)
{
	// GetTransform()->AddLocalRotation({0.0f, 0.0f, 360.0f * _Delta});
};
