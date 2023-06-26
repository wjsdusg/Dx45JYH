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
#include "Object.h"
#include "Map.h"
#include "UIPannel.h"
#include "MiniMap.h"
#include "MapOverlay.h"
#include "Ksword.h"
#include "DragBox.h"
#include "Karcher.h"
#include "Monster_01.h"
#include "Frog.h"
#include "Gangsi.h"
#include "Gatpha.h"
#include "HungryDemon.h"
#include "Onghwa.h"
#include "Raccoondog.h"
#include "Snowdemon.h"
#include "Snowwoman.h"
#include "Starfish.h"
#include "Tiger.h"
#include "WeirdPlant.h"
#include "SwordPirate.h"
#include "TestObject.h"

#include "Gonisi.h"
#include "Asako.h"
#include "Gato.h"
#include "Seisho.h"
#include "Tokugawa.h"
#include "Ugida.h"
#include "Wakizaka.h"

std::shared_ptr<Player> Object0 = nullptr;
std::shared_ptr<TestObject> TestObject0 = nullptr;
std::shared_ptr<DragBox> NewDragBox = nullptr;
std::shared_ptr<Map> Map1 = nullptr;
std::shared_ptr<UIPannel> NewUIPannel = nullptr;
std::shared_ptr<MiniMap> NewMiniMap = nullptr;
std::shared_ptr<Ksword> NewKsword = nullptr;
std::shared_ptr<Ksword> NewKsword2 = nullptr;
std::shared_ptr<MapOverlay> NewMapOverlay = nullptr;
std::shared_ptr<Karcher>NewKarcher = nullptr;
std::shared_ptr<Object>NewObject = nullptr;
std::shared_ptr<Monster_01>NewMonster = nullptr;
std::shared_ptr<Frog>NewForg = nullptr;

std::shared_ptr<Gangsi> NewGangsi = nullptr;
std::shared_ptr<Gatpha> NewGatpha = nullptr;
std::shared_ptr<HungryDemon> NewHungryDemon = nullptr;
std::shared_ptr<Onghwa> NewOnghwa = nullptr;
std::shared_ptr<Raccoondog> NewRaccoondog = nullptr;
std::shared_ptr<Snowdemon> NewSnowdemon = nullptr;
std::shared_ptr<Snowwoman> NewSnowwoman = nullptr;
//std::shared_ptr<Starfish> NewStarfish = nullptr;
std::shared_ptr<Tiger> NewTiger = nullptr;
std::shared_ptr<WeirdPlant> NewWeirdPlant = nullptr;
std::shared_ptr<SwordPirate> NewSwordPirate = nullptr;

std::shared_ptr<Gonisi> NewGonisi = nullptr;
std::shared_ptr<Asako> NewAsako = nullptr;
std::shared_ptr<Gato> NewGato = nullptr;
std::shared_ptr<Seisho> NeSeisho = nullptr;
std::shared_ptr<Tokugawa> NewTokugawa = nullptr;
std::shared_ptr<Ugida> NewUgida = nullptr;
std::shared_ptr<Wakizaka> NewWakizaka = nullptr;


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
extern int CalculateSideRhombusCount();
extern int gcd(int a, int b);
extern float4 UIMouse;
extern float4 MainMouse;
void PlayLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsUp("G"))
	{
		
		NewMonster->Death();
		IsDebugSwitch();
	}
	{
		std::shared_ptr<GameEngineCamera> Camera = GetCamera(100);

		// 랜더러 
		float4x4 ViewPort = Camera->GetViewPort();
		float4x4 Proj = Camera->GetProjection();
		float4x4 View = Camera->GetView();

		UIMouse = GameEngineInput::GetMousePosition();

		UIMouse *= ViewPort.InverseReturn();
		UIMouse *= Proj.InverseReturn();
		UIMouse *= View.InverseReturn();
	}
	{
		{
			std::shared_ptr<GameEngineCamera> Camera = GetMainCamera();

			// 랜더러 
			float4x4 ViewPort = Camera->GetViewPort();
			float4x4 Proj = Camera->GetProjection();
			float4x4 View = Camera->GetView();

			MainMouse = GameEngineInput::GetMousePosition();

			MainMouse *= ViewPort.InverseReturn();
			MainMouse *= Proj.InverseReturn();
			MainMouse *= View.InverseReturn();
		}
	}
	//y>= a*x+b 이면 x,y점이 닿거나 위에있다.
	float Speed = 1000.f;

	if (
		true == GameEngineInput::IsPress("Left")
		&& GetMainCamera()->GetTransform()->GetLocalPosition().x >= -(MapSize.x / 2 - (GameEngineWindow::GetScreenSize().x / 2))
		||
		(
			(
				UIMouse.x >= -(GameEngineWindow::GetScreenSize().x / 2))
			&& (UIMouse.x <= -(GameEngineWindow::GetScreenSize().x / 2 - 20))
			&& (
				UIMouse.y >= -(GameEngineWindow::GetScreenSize().y / 2 - NewMiniMap->Render0->GetTransform()->GetLocalScale().y)
				|| 
					(
					UIMouse.y >= -(GameEngineWindow::GetScreenSize().y / 2)
					&& UIMouse.y <= -(GameEngineWindow::GetScreenSize().y / 2-40)
					)
				)
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
				UIMouse.x >= (GameEngineWindow::GetScreenSize().x / 2 - 20))
			&& (UIMouse.x <= (GameEngineWindow::GetScreenSize().x / 2))
			&& UIMouse.y >= -GameEngineWindow::GetScreenSize().y / 2
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
			UIMouse.y >= (GameEngineWindow::GetScreenSize().y / 2 - 20)
			&& UIMouse.y <= (GameEngineWindow::GetScreenSize().y / 2)
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
			UIMouse.y <= -(GameEngineWindow::GetScreenSize().y / 2 - 20)
			&& UIMouse.y >= -(GameEngineWindow::GetScreenSize().y / 2)
			&&(
				UIMouse.x >= -(GameEngineWindow::GetScreenSize().x / 2 - NewMiniMap->Render0->GetTransform()->GetLocalScale().x)
				||
				(
					UIMouse.x >= -(GameEngineWindow::GetScreenSize().x / 2)
					&& UIMouse.x <= -(GameEngineWindow::GetScreenSize().x / 2 - 60)
					)
				)
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
	{
		
		if (nullptr!= NewDragBox &&true == NewDragBox->IsDeath())
		{
			NewDragBox = nullptr;
		}
		if (true == GameEngineInput::IsPress("EngineMouseLeft"))
		{
			if (nullptr == NewDragBox)
			{
				NewDragBox = CreateActor<DragBox>();
				NewDragBox->SetMousePos(MainMouse);
			}
			NewDragBox->SetMouseMovePos(MainMouse);
		}
		if (true == GameEngineInput::IsUp("EngineMouseLeft"))
		{
			if (nullptr != NewDragBox)
			{
				NewDragBox->AllCollision();
				
				/*NewDragBox->Death();
				NewDragBox = nullptr;*/
			}
		}
	}
	
	if (true == GameEngineInput::IsUp("Space"))
	{
		GetMainCamera()->GetTransform()->SetLocalPosition({ 0,0 });
	}
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
		GameEngineInput::CreateKey("Space", VK_SPACE);
		GameEngineInput::CreateKey("G", 'G');
		GameEngineInput::CreateKey("A", 'A');
		GameEngineInput::CreateKey("S", 'S');
		GameEngineInput::CreateKey("H", 'H');
	}
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });
	//std::shared_ptr<GameEngineCoreWindow> Window = GameEngineGUI::FindGUIWindowConvert<GameEngineCoreWindow>("CoreWindow");
	Map1 = CreateActor<Map>();
	//Map1->Off();
	NewUIPannel = CreateActor<UIPannel>();
	NewMiniMap = CreateActor<MiniMap>();

	MiniViewRatio = MiniMapSize / MapSize;
	NewMiniMap->GetTransform()->SetLocalPosition(NewUIPannel->GetTransform()->GetLocalPosition());
	NewMiniMap->GetTransform()->AddLocalPosition({ -458.f,-27.f });
	NewMapOverlay = CreateActor<MapOverlay>();
	

	float4 _Pos2 = MapUpP;
	_Pos2.y -= 50.f;
	
	NewMapOverlay->GetTransform()->SetLocalPosition(_Pos2);
	
	{
		std::shared_ptr<GameEngineButton> Button = CreateActor<GameEngineButton>();
		Button->GetTransform()->SetLocalPosition(NewMiniMap->GetTransform()->GetLocalPosition());
		Button->GetTransform()->SetLocalScale(NewMiniMap->Render0->GetTransform()->GetLocalScale());
		Button->GetTransform()->AddLocalPosition({ 0,0,1.f });
		Button->SetEvent([this]()
			{

				float4 Pos = UIMouse - NewMiniMap->GetTransform()->GetLocalPosition();
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
	//NewKsword = CreateActor<Ksword>();
	NewKsword2 = CreateActor<Ksword>();
	NewKsword2->GetTransform()->SetLocalPosition({ -200.f,-100 });
	//NewKarcher = CreateActor<Karcher>();
	//NewKarcher->GetTransform()->SetLocalPosition({ 100.f,100.f });
	GetMainCamera()->SetSortType(0, SortType::ZSort);
	GetCamera(100)->SetSortType(0, SortType::ZSort);
	
	NewMonster =CreateActor<Monster_01>();
	NewObject = CreateActor<Object>(1);
	
	NewForg = CreateActor<Frog>();
	NewForg->GetTransform()->SetLocalPosition({ -100.f,-100 });
	NewGangsi = CreateActor<Gangsi>();
	NewGangsi->GetTransform()->SetLocalPosition({ -50.f,-100 });
	NewGatpha = CreateActor<Gatpha>();
	NewGatpha->GetTransform()->SetLocalPosition({ 0,-100 });
	NewHungryDemon = CreateActor<HungryDemon>();
	NewHungryDemon->GetTransform()->SetLocalPosition({ 50,-100 });
	NewOnghwa = CreateActor<Onghwa>();
	NewOnghwa->GetTransform()->SetLocalPosition({ 100,-100 });
	NewRaccoondog = CreateActor<Raccoondog>();
	NewRaccoondog->GetTransform()->SetLocalPosition({ 150,-100 });
	NewSnowdemon = CreateActor<Snowdemon>();
	NewSnowdemon->GetTransform()->SetLocalPosition({ 200,-100 });
	NewSnowwoman = CreateActor<Snowwoman>();
	NewSnowwoman->GetTransform()->SetLocalPosition({ 250,-100 });
	NewSwordPirate = CreateActor<SwordPirate>();
	NewSwordPirate->GetTransform()->SetLocalPosition({ 300,-100 });
	NewTiger = CreateActor<Tiger>();
	NewTiger->GetTransform()->SetLocalPosition({ 350,-100 });
	NewWeirdPlant = CreateActor<WeirdPlant>();
	NewWeirdPlant->GetTransform()->SetLocalPosition({ 400,-100 });

	NewGonisi = CreateActor<Gonisi>();
	NewGonisi->GetTransform()->SetLocalPosition({ 450,-400 });
	NewAsako = CreateActor<Asako>();
	NewAsako->GetTransform()->SetLocalPosition({ 450,-350 });
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