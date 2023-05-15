#include "PrecompileHeader.h"
#include "PlayLevel.h"
#include "Player.h"
#include "TestObject.h"
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineVideo.h>
#include <GameEngineCore/GameEngineCoreWindow.h>

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Update(float _DeltaTime)
{

}

void PlayLevel::PlayerCreate(/*Playlevel* this*/)
{
	std::shared_ptr<Player> Object = CreateActor<Player>(0);
}

void PlayLevel::Start()
{

	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });


		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}



	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });


	std::shared_ptr<GameEngineCoreWindow> Window = GameEngineGUI::FindGUIWindowConvert<GameEngineCoreWindow>("CoreWindow");

	{
		if (nullptr == Window)
		{
			MsgAssert("윈도우 테스트 코드 미작동");
		}

		Window->Test = std::bind(&PlayLevel::PlayerCreate, this);

		// std::shared_ptr<Player> Object = CreateActor<Player>(0);
	}


	{
		std::shared_ptr<TestObject> Object = CreateActor<TestObject>(-20);
		Object->GetTransform()->SetLocalScale({ 1000, 1000, 1000 });
		Object->GetTransform()->SetLocalPosition({ 0, 0, 100.0f });
	}


}
void PlayLevel::LevelChangeStart()
{
	GameEngineLevel::LevelChangeStart();
	int a = 0;
}

void PlayLevel::LevelChangeEnd()
{
	GameEngineLevel::LevelChangeEnd();
	int a = 0;
}