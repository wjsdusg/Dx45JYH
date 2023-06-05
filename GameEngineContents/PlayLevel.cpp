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

extern float4 MapSize;
extern float4 MiniMapSize;
extern float4 MiniViewRatio;
extern float4 MapRightP;
extern float4 MapLeftP;
extern float4 MapUpP;
extern float4 MapDownP;
extern  bool CheckPointOnUpLine(float4 Point1, float4 Point2, float4 CheckPoint);
extern  bool CheckPointOnDownLine(float4 Point1, float4 Point2, float4 CheckPoint);
extern float4 MovePointLeftOnLine(float4 _PrePos,float _Speed, float _DeltaTime);
extern float4 MovePointRightOnLine(float4 _PrePos, float _Speed, float _DeltaTime);

void PlayLevel::Update(float _DeltaTime)
{

	float dis = MapRightP.XYDistance(MapUpP);
	float rcos = MapRightP.x / dis;
	float deg2 = acosf(rcos) * GameEngineMath::RadToDeg;

	float a = (MapUpP.y - MapRightP.y) / (MapUpP.x - MapRightP.y);
	float b = MapRightP.y - a * MapRightP.y;
	//y>= a*x+b 이면 x,y점이 닿거나 위에있다.
	float Speed = 1000.f;

	if (true == GameEngineInput::IsPress("Left") && GetMainCamera()->GetTransform()->GetLocalPosition().x >= -(MapSize.x / 2 - (GameEngineWindow::GetScreenSize().x / 2)))
	{
		if (true == CheckPointOnUpLine(MapUpP, MapLeftP, GetMainCamera()->GetTransform()->GetLocalPosition()))
		{
			float4 Pos = MovePointLeftOnLine(GetMainCamera()->GetTransform()->GetLocalPosition(), Speed, _DeltaTime);

			GetMainCamera()->GetTransform()->SetLocalPosition(Pos);
		}
		else if (true == CheckPointOnDownLine(MapDownP, MapLeftP, GetMainCamera()->GetTransform()->GetLocalPosition()))
		{
			float4 Pos = MovePointLeftOnLine(GetMainCamera()->GetTransform()->GetLocalPosition(), Speed, _DeltaTime);

			GetMainCamera()->GetTransform()->SetLocalPosition(Pos);
		}
		else 
		{
			GetMainCamera()->GetTransform()->AddLocalPosition(GetTransform()->GetWorldLeftVector() * Speed * _DeltaTime);

		}
	}
	if (true == GameEngineInput::IsPress("Right") && GetMainCamera()->GetTransform()->GetLocalPosition().x >= -(MapSize.x / 2 - (GameEngineWindow::GetScreenSize().x / 2)))
	{
		if (true == CheckPointOnUpLine(MapUpP, MapRightP, GetMainCamera()->GetTransform()->GetLocalPosition()))
		{
			float4 Pos = MovePointRightOnLine(GetMainCamera()->GetTransform()->GetLocalPosition(), Speed, _DeltaTime);

			GetMainCamera()->GetTransform()->SetLocalPosition(Pos);
		}
		else if (true == CheckPointOnDownLine(MapDownP, MapRightP, GetMainCamera()->GetTransform()->GetLocalPosition()))
		{
			float4 Pos = MovePointRightOnLine(GetMainCamera()->GetTransform()->GetLocalPosition(), Speed, _DeltaTime);

			GetMainCamera()->GetTransform()->SetLocalPosition(Pos);
		}
		else
		{
			GetMainCamera()->GetTransform()->AddLocalPosition(GetTransform()->GetWorldRightVector() * Speed * _DeltaTime);

		}
	}
	if (true == GameEngineInput::IsPress("Up")&& GetMainCamera()->GetTransform()->GetLocalPosition().y <= (MapSize.y / 2 - (GameEngineWindow::GetScreenSize().y / 2)))
	{
		if (true == CheckPointOnUpLine(MapUpP, MapRightP, GetMainCamera()->GetTransform()->GetLocalPosition()))
		{
			
			float4 Pos =MovePointLeftOnLine(GetMainCamera()->GetTransform()->GetLocalPosition(), Speed, _DeltaTime);
			
			GetMainCamera()->GetTransform()->SetLocalPosition(Pos);
		}
		else if (true == CheckPointOnUpLine(MapUpP, MapLeftP, GetMainCamera()->GetTransform()->GetLocalPosition()))
		{
			float4 Pos = MovePointRightOnLine(GetMainCamera()->GetTransform()->GetLocalPosition(), Speed, _DeltaTime);
			GetMainCamera()->GetTransform()->SetLocalPosition(Pos);
		}
		else
		{
			GetMainCamera()->GetTransform()->AddLocalPosition(GetTransform()->GetWorldUpVector() * Speed * _DeltaTime);

		}

		//GetMainCamera()->GetTransform()->AddLocalPosition(float4::AngleToDirection2DToDeg(180.f) * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("Down")&& GetMainCamera()->GetTransform()->GetLocalPosition().y>= -(MapSize.y/2-GameEngineWindow::GetScreenSize().y/2))
	{
		if (true == CheckPointOnDownLine(MapDownP, MapRightP, GetMainCamera()->GetTransform()->GetLocalPosition()))
		{

			float4 Pos = MovePointLeftOnLine(GetMainCamera()->GetTransform()->GetLocalPosition(), Speed, _DeltaTime);

			GetMainCamera()->GetTransform()->SetLocalPosition(Pos);
		}
		else if (true == CheckPointOnDownLine(MapDownP, MapLeftP, GetMainCamera()->GetTransform()->GetLocalPosition()))
		{
			float4 Pos = MovePointRightOnLine(GetMainCamera()->GetTransform()->GetLocalPosition(), Speed, _DeltaTime);
			GetMainCamera()->GetTransform()->SetLocalPosition(Pos);
		}
		else
		{
			GetMainCamera()->GetTransform()->AddLocalPosition(GetTransform()->GetWorldDownVector() * Speed * _DeltaTime);

		}
	}
	
	//if(true==GetMainCamera()->GetTransform()->GetLocalPosition())
	
	if (GetMainCamera()->GetTransform()->GetLocalPosition().y > (MapSize.y / 2 - (GameEngineWindow::GetScreenSize().y / 2)))
	{
		GetMainCamera()->GetTransform()->SetLocalPosition({ GetMainCamera()->GetTransform()->GetLocalPosition().x,(MapSize.y / 2 - (GameEngineWindow::GetScreenSize().y / 2))});
	}
	if (GetMainCamera()->GetTransform()->GetLocalPosition().x < -(MapSize.x / 2 - (GameEngineWindow::GetScreenSize().x / 2)))
	{
		GetMainCamera()->GetTransform()->SetLocalPosition({ -((MapSize.x / 2)-(GameEngineWindow::GetScreenSize().x / 2)),GetMainCamera()->GetTransform()->GetLocalPosition().y });
	}
	if (GetMainCamera()->GetTransform()->GetLocalPosition().x >(MapSize.x / 2 - (GameEngineWindow::GetScreenSize().x / 2)))
	{
		GetMainCamera()->GetTransform()->SetLocalPosition({ ((MapSize.x / 2) - (GameEngineWindow::GetScreenSize().x / 2)),GetMainCamera()->GetTransform()->GetLocalPosition().y });
	}
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


	NewUIPannel = CreateActor<UIPannel>(-20);

	NewMiniMap = CreateActor<MiniMap>(0);

	MiniViewRatio = MiniMapSize / MapSize;
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