#include "PrecompileHeader.h"
#include "PlayLevel.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineVideo.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineButton.h>
#include "Map.h"
#include "UIPannel.h"
#include "MiniMap.h"
#include "Ksword.h"
std::shared_ptr<Player> Object0 = nullptr;


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
extern float4 MovePointLeftOnLine(float4 _PrePos, float _Speed, float _DeltaTime);
extern float4 MovePointRightOnLine(float4 _PrePos, float _Speed, float _DeltaTime);
extern void MovePointToLine(float4& _PrePos);

void PlayLevel::Update(float _DeltaTime)
{
	
	{
		std::shared_ptr<GameEngineCamera> Camera = GetCamera(100);

		// 랜더러 
		float4x4 ViewPort = Camera->GetViewPort();
		float4x4 Proj = Camera->GetProjection();
		float4x4 View = Camera->GetView();

		Mouse = GameEngineInput::GetMousePosition();

		Mouse *= ViewPort.InverseReturn();
		Mouse *= Proj.InverseReturn();
		Mouse *= View.InverseReturn();
	}

	//y>= a*x+b 이면 x,y점이 닿거나 위에있다.
	float Speed = 1000.f;

	if (
		true == GameEngineInput::IsPress("Left")
		&& GetMainCamera()->GetTransform()->GetLocalPosition().x >= -(MapSize.x / 2 - (GameEngineWindow::GetScreenSize().x / 2))
		||
		(
			(
				Mouse.x >= -(GameEngineWindow::GetScreenSize().x / 2)) 
			&& (Mouse.x <= -(GameEngineWindow::GetScreenSize().x / 2 - 20))
			&& Mouse.y >= -(GameEngineWindow::GetScreenSize().y/2-NewMiniMap->Render0->GetTransform()->GetLocalScale().y)
			)
		)
	{
		if (true == CheckPointOnUpLine(MapUpP, MapLeftP, GetMainCamera()->GetTransform()->GetLocalPosition()))
		{
			float4 Pos = MovePointLeftOnLine(GetMainCamera()->GetTransform()->GetLocalPosition(), Speed, _DeltaTime);
			OutlineCheck(Pos);
			GetMainCamera()->GetTransform()->SetLocalPosition(Pos);
		}
		else if (true == CheckPointOnDownLine(MapDownP, MapLeftP, GetMainCamera()->GetTransform()->GetLocalPosition()))
		{
			float4 Pos = MovePointLeftOnLine(GetMainCamera()->GetTransform()->GetLocalPosition(), Speed, _DeltaTime);
			OutlineCheck(Pos);
			GetMainCamera()->GetTransform()->SetLocalPosition(Pos);
		}
		else
		{
			float4 Pos = GetMainCamera()->GetTransform()->GetLocalPosition() + GetTransform()->GetWorldLeftVector() * Speed * _DeltaTime;
			OutlineCheck(Pos);
			GetMainCamera()->GetTransform()->SetLocalPosition(Pos);


		}
	}
	if (
		true == GameEngineInput::IsPress("Right")
		&& GetMainCamera()->GetTransform()->GetLocalPosition().x >= -(MapSize.x / 2 - (GameEngineWindow::GetScreenSize().x / 2))
		||
		(
			(
				Mouse.x >= (GameEngineWindow::GetScreenSize().x / 2 - 20)) 
			&& (Mouse.x <= (GameEngineWindow::GetScreenSize().x / 2))
			)
		)
	{
		if (true == CheckPointOnUpLine(MapUpP, MapRightP, GetMainCamera()->GetTransform()->GetLocalPosition()))
		{
			float4 Pos = MovePointRightOnLine(GetMainCamera()->GetTransform()->GetLocalPosition(), Speed, _DeltaTime);
			OutlineCheck(Pos);
			GetMainCamera()->GetTransform()->SetLocalPosition(Pos);
		}
		else if (true == CheckPointOnDownLine(MapDownP, MapRightP, GetMainCamera()->GetTransform()->GetLocalPosition()))
		{
			float4 Pos = MovePointRightOnLine(GetMainCamera()->GetTransform()->GetLocalPosition(), Speed, _DeltaTime);
			OutlineCheck(Pos);
			GetMainCamera()->GetTransform()->SetLocalPosition(Pos);
		}
		else
		{
			float4 Pos = GetMainCamera()->GetTransform()->GetLocalPosition() + GetTransform()->GetWorldRightVector() * Speed * _DeltaTime;
			OutlineCheck(Pos);
			GetMainCamera()->GetTransform()->SetLocalPosition(Pos);

		}
	}
	if (
		true == GameEngineInput::IsPress("Up")
		&& GetMainCamera()->GetTransform()->GetLocalPosition().y <= (MapSize.y / 2 - (GameEngineWindow::GetScreenSize().y / 2))
		||
		(
			Mouse.y >= (GameEngineWindow::GetScreenSize().y / 2 - 20)
			&& Mouse.y <= (GameEngineWindow::GetScreenSize().y / 2)
			)

		)
	{
		if (true == CheckPointOnUpLine(MapUpP, MapRightP, GetMainCamera()->GetTransform()->GetLocalPosition()))
		{

			float4 Pos = MovePointLeftOnLine(GetMainCamera()->GetTransform()->GetLocalPosition(), Speed, _DeltaTime);
			OutlineCheck(Pos);
			GetMainCamera()->GetTransform()->SetLocalPosition(Pos);
		}
		else if (true == CheckPointOnUpLine(MapUpP, MapLeftP, GetMainCamera()->GetTransform()->GetLocalPosition()))
		{
			float4 Pos = MovePointRightOnLine(GetMainCamera()->GetTransform()->GetLocalPosition(), Speed, _DeltaTime);
			OutlineCheck(Pos);
			GetMainCamera()->GetTransform()->SetLocalPosition(Pos);
		}
		else
		{
			float4 Pos = GetMainCamera()->GetTransform()->GetLocalPosition() + GetTransform()->GetWorldUpVector() * Speed * _DeltaTime;
			OutlineCheck(Pos);
			GetMainCamera()->GetTransform()->SetLocalPosition(Pos);


		}

		//GetMainCamera()->GetTransform()->AddLocalPosition(float4::AngleToDirection2DToDeg(180.f) * Speed * _DeltaTime);
	}
	if (
		true == GameEngineInput::IsPress("Down")
		&& GetMainCamera()->GetTransform()->GetLocalPosition().y >= -(MapSize.y / 2 - GameEngineWindow::GetScreenSize().y / 2)
		||
		(
			Mouse.y <= -(GameEngineWindow::GetScreenSize().y / 2 - 20)
			&& Mouse.y >= -(GameEngineWindow::GetScreenSize().y / 2)
			&& Mouse.x >= -(GameEngineWindow::GetScreenSize().x / 2 - NewMiniMap->Render0->GetTransform()->GetLocalScale().x)
			)
		)
	{
		if (true == CheckPointOnDownLine(MapDownP, MapRightP, GetMainCamera()->GetTransform()->GetLocalPosition()))
		{

			float4 Pos = MovePointLeftOnLine(GetMainCamera()->GetTransform()->GetLocalPosition(), Speed, _DeltaTime);
			OutlineCheck(Pos);
			GetMainCamera()->GetTransform()->SetLocalPosition(Pos);
		}
		else if (true == CheckPointOnDownLine(MapDownP, MapLeftP, GetMainCamera()->GetTransform()->GetLocalPosition()))
		{
			float4 Pos = MovePointRightOnLine(GetMainCamera()->GetTransform()->GetLocalPosition(), Speed, _DeltaTime);
			OutlineCheck(Pos);
			GetMainCamera()->GetTransform()->SetLocalPosition(Pos);
		}
		else
		{
			float4 Pos = GetMainCamera()->GetTransform()->GetLocalPosition() + GetTransform()->GetWorldDownVector() * Speed * _DeltaTime;
			OutlineCheck(Pos);
			GetMainCamera()->GetTransform()->SetLocalPosition(Pos);



		}
	}

	//if(true==GetMainCamera()->GetTransform()->GetLocalPosition())

	float4 Pos =  Mouse;
}

void PlayLevel::OutlineCheck(float4& _Pos)
{
	if (_Pos.y >= (MapSize.y / 2 - (GameEngineWindow::GetScreenSize().y / 2)))
	{
		_Pos.y = (MapSize.y / 2 - (GameEngineWindow::GetScreenSize().y / 2));
		_Pos.x = 0.f;
	}
	if (_Pos.y <= -(MapSize.y / 2 - (GameEngineWindow::GetScreenSize().y / 2)))
	{
		_Pos.y = -(MapSize.y / 2 - (GameEngineWindow::GetScreenSize().y / 2));
		_Pos.x = 0.f;
	}
	if (_Pos.x <= -(MapSize.x / 2 - (GameEngineWindow::GetScreenSize().x / 2)))
	{
		_Pos.x = -(MapSize.x / 2 - (GameEngineWindow::GetScreenSize().x / 2));
		_Pos.y = 0.f;
	}
	if (_Pos.x >= (MapSize.x / 2 - (GameEngineWindow::GetScreenSize().x / 2)))
	{
		_Pos.x = (MapSize.x / 2 - (GameEngineWindow::GetScreenSize().x / 2));
		_Pos.y = 0.f;
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

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png",".Bmp" });


		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	{
		GameEngineInput::CreateKey("Left", VK_LEFT);
		GameEngineInput::CreateKey("Right", VK_RIGHT);
		GameEngineInput::CreateKey("Up", VK_UP);
		GameEngineInput::CreateKey("Down", VK_DOWN);
	}

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });


	//std::shared_ptr<GameEngineCoreWindow> Window = GameEngineGUI::FindGUIWindowConvert<GameEngineCoreWindow>("CoreWindow");

	Map1 = CreateActor<Map>(-30);


	NewUIPannel = CreateActor<UIPannel>();
	NewMiniMap = CreateActor<MiniMap>();


	MiniViewRatio = MiniMapSize / MapSize;
	NewMiniMap->GetTransform()->SetLocalPosition(NewUIPannel->GetTransform()->GetLocalPosition());
	NewMiniMap->GetTransform()->AddLocalPosition({ -490.f,-30.f });

	{
		std::shared_ptr<GameEngineButton> Button = CreateActor<GameEngineButton>();
		Button->GetTransform()->SetLocalPosition(NewMiniMap->GetTransform()->GetLocalPosition());
		Button->GetTransform()->SetLocalScale(NewMiniMap->Render0->GetTransform()->GetLocalScale());
		Button->GetTransform()->AddLocalPosition({ 0,0,1.f });
		Button->SetEvent([this]()
			{
			
				float4 Pos = this->Mouse - NewMiniMap->GetTransform()->GetLocalPosition();
				Pos.z = 0.f;
			/*	NewMiniMap->Render1->GetTransform()->SetLocalPosition(Pos);

				float4 MPos = NewMiniMap->Render1->GetTransform()->GetLocalPosition() * 1 / MiniViewRatio;*/
				float4 MPos = Pos * 1 / MiniViewRatio;
				MPos.z = 0.f;
				if (true == CheckPointOnUpLine(MapUpP, MapRightP, MPos))
				{
					MovePointToLine(MPos);
					OutlineCheck(MPos);
					NewMiniMap->Render1->GetTransform()->SetLocalPosition(MPos);
					GetMainCamera()->GetTransform()->SetLocalPosition(MPos);
					
				}
				else if (true == CheckPointOnUpLine(MapUpP, MapLeftP, MPos))
				{
					MovePointToLine(MPos);
					OutlineCheck(MPos);
					NewMiniMap->Render1->GetTransform()->SetLocalPosition(MPos);
					GetMainCamera()->GetTransform()->SetLocalPosition(MPos);
				}
				else if (true == CheckPointOnDownLine(MapDownP, MapRightP, MPos))
				{
					MovePointToLine(MPos);
					OutlineCheck(MPos);
					NewMiniMap->Render1->GetTransform()->SetLocalPosition(MPos);
					GetMainCamera()->GetTransform()->SetLocalPosition(MPos);
				}
				else if (true == CheckPointOnDownLine(MapDownP, MapLeftP, MPos))
				{
					MovePointToLine(MPos);
					OutlineCheck(MPos);
					NewMiniMap->Render1->GetTransform()->SetLocalPosition(MPos);
					GetMainCamera()->GetTransform()->SetLocalPosition(MPos);
				}
				else
				{
					GetMainCamera()->GetTransform()->SetLocalPosition(MPos);
				}
				
				
			});
	}
	NewKsword = CreateActor<Ksword>(10);
	GetMainCamera()->SetSortType(0, SortType::ZSort);
	GetCamera(100)->SetSortType(0, SortType::ZSort);
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