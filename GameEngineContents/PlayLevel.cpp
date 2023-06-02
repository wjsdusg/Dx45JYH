#include "PrecompileHeader.h"
#include "PlayLevel.h"
#include "Player.h"
#include "TestObject.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineVideo.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "Map.h"
#include "UIPannel.h"
#include "MiniMap.h"
#include "Ksword.h"
std::shared_ptr<Player> Object0 = nullptr;
std::shared_ptr<TestObject> Object1 = nullptr;
std::shared_ptr<GameEngineSpriteRenderer> RenderTest = nullptr;
std::shared_ptr<Map> Map1 = nullptr;
std::shared_ptr<UIPannel> NewUIPannel = nullptr;
std::shared_ptr<MiniMap> NewMiniMap = nullptr;
std::shared_ptr<Ksword> NewKsword = nullptr;
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
	

}

void PlayLevel::Start()
{

	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Test");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png",".Bmp"});


		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}



	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });


	std::shared_ptr<GameEngineCoreWindow> Window = GameEngineGUI::FindGUIWindowConvert<GameEngineCoreWindow>("CoreWindow");
	Map1 = CreateActor<Map>(-30);
	Map1->GetTransform()->SetLocalScale({ 11520.f,5960.f, 1.f, 1.f });
	NewUIPannel = CreateActor<UIPannel>(-20);

	NewMiniMap = CreateActor<MiniMap>(0);
	MiniMap::MiniViewRatio = NewMiniMap->Render0->GetTransform()->GetLocalScale() / Map1->GetTransform()->GetLocalScale();
	NewMiniMap->GetTransform()->SetLocalPosition(NewUIPannel->GetTransform()->GetLocalPosition());
	NewMiniMap->GetTransform()->AddLocalPosition({ -490.f,-30.f });

	NewKsword = CreateActor<Ksword>(10);
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