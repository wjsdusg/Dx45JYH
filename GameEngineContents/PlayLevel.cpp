#include "PrecompileHeader.h"
#include "PlayLevel.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineButton.h>
#include <GameEngineCore/GameEngineFontRenderer.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineTileMapRenderer.h>
#include "GlobalValue.h"
#include "Mouse.h"
#include "Object.h"
#include "Map.h"
#include "DefenseMap.h"
#include "UIPannel.h"
#include "MiniMap.h"
#include "MapOverlay.h"
#include "Ksword.h"
#include "Karcher.h"
#include "TestObject.h"
#include "UIButton.h"
#include "Minion.h"
#include "Gonisi.h"
#include "Asako.h"
#include "Gato.h"
#include "Seisho.h"
#include "Tokugawa.h"
#include "Ugida.h"
#include "Wakizaka.h"

#include "MapEditor.h"
#include "DefenseMapEditor.h"
#include "Optionsheet.h"
#include "RuinObject.h"
#include "NormalObject1.h"
#include "TreasureBox.h"
#include "Barrack.h"
#include "GameManager.h"
#include "GotoDefenseMapZone.h"
std::shared_ptr<Mouse> NewMouse = nullptr;
std::shared_ptr<Player> Object0 = nullptr;
std::shared_ptr<TestObject> TestObject0 = nullptr;
std::shared_ptr<Map> Map1 = nullptr;
std::shared_ptr<UIPannel> NewUIPannel = nullptr;
std::shared_ptr<MiniMap> NewMiniMap = nullptr;

std::shared_ptr<MapOverlay> NewMapOverlay = nullptr;

std::shared_ptr<Object>NewObject = nullptr;

std::shared_ptr<DefenseMap> NewDefenseMap = nullptr;
std::shared_ptr<MapEditor> NewMapEditor = nullptr;
std::shared_ptr<GameEngineFontRenderer> FontRender = nullptr;
std::shared_ptr<UIButton> NewUIButton = nullptr;
std::shared_ptr<DefenseMapEditor> NewDefenseMapEditor = nullptr;
std::shared_ptr<Optionsheet> NewOptionsheet = nullptr;
std::shared_ptr<RuinObject> NewRuinObject = nullptr;
std::shared_ptr<NormalObject1> NewNormalObject1 = nullptr;
std::shared_ptr<TreasureBox> NewTreasureBox = nullptr;
std::shared_ptr<Barrack> NewBarrack = nullptr; 
std::shared_ptr<GameManager> NewGameManager = nullptr; 
std::shared_ptr<GotoDefenseMapZone> NewGotoDefenseMapZone = nullptr;
PlayLevel::PlayLevel()
{
	MainPlayLevel = this;
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
extern float4 TileScale;
PlayLevel* PlayLevel::MainPlayLevel = nullptr;
void PlayLevel::Update(float _DeltaTime)
{
	if (false == NewBarrack->DoorCollision->IsUpdate() && true == GameEngineInput::IsUp("F2"))
	{
		NewBarrack->DoorCollision->On();
		NewBarrack->DoorRender->On();
	}
	if (true == GameEngineInput::IsUp("G"))
	{
		NewBarrack->GotoDengeon();	
		//IsDebugSwitch();
	}
	if (true == GameEngineInput::IsUp("M"))
	{
		NewBarrack->CreateHero();
		
		//IsDebugSwitch();
	}
	{
		float4 Pos9 = MapOverlay::MainMapOverlay->GetTransform()->GetWorldPosition();

		

		{
			float4 Pos = NewRuinObject->GetTransform()->GetWorldPosition();
			if (MapOverlay::MainMapOverlay->TileMap->GetTIleIndex(Pos - Pos9) == 0)
			{
				NewRuinObject->Off();
			}
			else
			{
				if (false == NewRuinObject->IsUpdate())
				{
					NewRuinObject->On();

				}
			}
		}
		{
			float4 Pos = NewTreasureBox->GetTransform()->GetWorldPosition();
			if (MapOverlay::MainMapOverlay->TileMap->GetTIleIndex(Pos - Pos9) == 0)
			{
				NewTreasureBox->Off();
			}
			else
			{
				if (false == NewTreasureBox->IsUpdate())
				{
					NewTreasureBox->On();

				}
			}
		}
		{
			float4 Pos = NewNormalObject1->GetTransform()->GetWorldPosition();
			if (MapOverlay::MainMapOverlay->TileMap->GetTIleIndex(Pos - Pos9) == 0)
			{
				NewNormalObject1->Off();
			}
			else
			{
				if (false == NewNormalObject1->IsUpdate())
				{
					NewNormalObject1->On();

				}
			}
		}
		{
		float4 Pos = NewGotoDefenseMapZone->GetTransform()->GetWorldPosition();
		if (MapOverlay::MainMapOverlay->TileMap->GetTIleIndex(Pos - Pos9) == 0)
		{
			NewGotoDefenseMapZone->Off();
		}
		else
		{
			if (false == NewGotoDefenseMapZone->IsUpdate())
			{
				NewGotoDefenseMapZone->On();

			}
		}
		}
			/*
			

			 =*/
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
	//마우스 외각시 맵이동
	if (Field::DefenseMap == MyField)
	{
		{
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
							&& UIMouse.y <= -(GameEngineWindow::GetScreenSize().y / 2 - 40)
							)
						)
					)
				)
			{

				float4 Pos = GetMainCamera()->GetTransform()->GetLocalPosition() + GetTransform()->GetWorldLeftVector() * Speed * _DeltaTime;

				GetMainCamera()->GetTransform()->SetLocalPosition(Pos);
			}

			if (
				(
					true == GameEngineInput::IsPress("Right")
					||
					(
						UIMouse.x >= (GameEngineWindow::GetScreenSize().x / 2 - 20))
					&& (UIMouse.x <= (GameEngineWindow::GetScreenSize().x / 2))
					&& UIMouse.y >= -GameEngineWindow::GetScreenSize().y / 2
					)

				&& GetMainCamera()->GetTransform()->GetLocalPosition().x <= (MapSize.x / 2 - (GameEngineWindow::GetScreenSize().x / 2) - 40.f
					)
				)
			{
				float dfsf = (MapSize.x / 2 - (GameEngineWindow::GetScreenSize().x / 2));
				float4 Pos = GetMainCamera()->GetTransform()->GetLocalPosition() + GetTransform()->GetWorldRightVector() * Speed * _DeltaTime;

				GetMainCamera()->GetTransform()->SetLocalPosition(Pos);
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

				float4 Pos = GetMainCamera()->GetTransform()->GetLocalPosition() + GetTransform()->GetWorldUpVector() * Speed * _DeltaTime;

				GetMainCamera()->GetTransform()->SetLocalPosition(Pos);

			}
			if (
				true == GameEngineInput::IsPress("Down")
				&& GetMainCamera()->GetTransform()->GetLocalPosition().y >= -(MapSize.y / 2 - GameEngineWindow::GetScreenSize().y / 2)
				
				)
			{

				float4 Pos = GetMainCamera()->GetTransform()->GetLocalPosition() + GetTransform()->GetWorldDownVector() * Speed * _DeltaTime;
				GetMainCamera()->GetTransform()->SetLocalPosition(Pos);
			}
		}
	}
	else if (Field::DungeonMap == MyField)
	{
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
						&& UIMouse.y <= -(GameEngineWindow::GetScreenSize().y / 2 - 40)
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
				&& (
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
	}




	if (true == GameEngineInput::IsUp("Space"))
	{
		//GetMainCamera()->GetTransform()->SetLocalPosition(NewDefenseMap->GetTransform()->GetLocalPosition());
		//MyField = Field::DefenseMap;
	}
	{
		/*if (nullptr != NewMapEditor && true == NewMapEditor->IsUpdate() && true == GameEngineInput::IsUp("F1"))
		{
			NewMapEditor->FSM.ChangeState("IsMove");
		}
		if (nullptr != NewMapEditor && true == NewMapEditor->IsUpdate() && true == GameEngineInput::IsUp("F8"))
		{
			NewMapEditor->FSM.ChangeState("Default");
		}*/
		/*if (nullptr != NewMapEditor && true == NewMapEditor->IsUpdate() && true == GameEngineInput::IsUp("F2")) {
			{
				GameEngineSerializer Ser;
				NewMapEditor->Save(Ser);
				GameEngineDirectory NewDir2;
				NewDir2.MoveParentToDirectory("ContentsBin");
				NewDir2.Move("ContentsBin");
				GameEngineFile NewFile = GameEngineFile(NewDir2.GetPlusFileName("RespawnPosSave.data").GetFullPath());
				NewFile.SaveBin(Ser);
			}
		}*/
		/*if (nullptr != NewMapEditor && true == NewMapEditor->IsUpdate() && true == GameEngineInput::IsUp("F3")) {
			GameEngineDirectory NewDir2;
			NewDir2.MoveParentToDirectory("ContentsBin");
			NewDir2.Move("ContentsBin");
			GameEngineFile NewFile = GameEngineFile(NewDir2.GetPlusFileName("IsMoveSave444.data").GetFullPath());
			GameEngineSerializer Ser;
			NewFile.LoadBin(Ser);
			NewMapEditor->Load(Ser);
		}*/
	}
	/*if (nullptr != NewMapEditor && true == GameEngineInput::IsUp("F5"))
	{
		if (true == NewMapEditor->IsUpdate())
		{
			NewMapEditor->Off();
			NewDefenseMapEditor->On();
		}
		else
		{
			NewMapEditor->On();
			NewDefenseMapEditor->Off();
		}
	}*/
	{
		/*if (nullptr != NewDefenseMapEditor && true == NewDefenseMapEditor->IsUpdate() && true == GameEngineInput::IsUp("F1"))
		{
			NewDefenseMapEditor->FSM.ChangeState("IsMove");

		}
		if (nullptr != NewDefenseMapEditor && true == NewDefenseMapEditor->IsUpdate() && true == GameEngineInput::IsUp("F8"))
		{

			NewDefenseMapEditor->FSM.ChangeState("Default");
		}*/
		/*if (nullptr != NewDefenseMapEditor && true == NewDefenseMapEditor->IsUpdate() && true == GameEngineInput::IsUp("F2")) {
			{
				GameEngineSerializer Ser;
				NewDefenseMapEditor->Save(Ser);
				GameEngineDirectory NewDir2;
				NewDir2.MoveParentToDirectory("ContentsBin");
				NewDir2.Move("ContentsBin");
				GameEngineFile NewFile = GameEngineFile(NewDir2.GetPlusFileName("IsMoveSave.data").GetFullPath());
				NewFile.SaveBin(Ser);
			}
		}*/
		/*if (nullptr != NewDefenseMapEditor && true == NewDefenseMapEditor->IsUpdate() && true == GameEngineInput::IsUp("F3")) {
			GameEngineDirectory NewDir2;
			NewDir2.MoveParentToDirectory("ContentsBin");
			NewDir2.Move("ContentsBin");
			GameEngineFile NewFile = GameEngineFile(NewDir2.GetPlusFileName("DefenseMapIsMove.data").GetFullPath());
			GameEngineSerializer Ser;
			NewFile.LoadBin(Ser);
			NewDefenseMapEditor->Load(Ser);
		}*/
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
		NewDir.Move("Bgm");

		GameEngineSound::Load(NewDir.GetPlusFileName("Track02.mp3").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("Track05.mp3").GetFullPath());
		BgmPlayer= GameEngineSound::Play("Track02.mp3");
		BgmPlayer.SetLoop(5);
	}
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Test");
		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png",".Bmp",".Tga" });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Missile");
		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png",".Bmp",".Tga" });
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
		GameEngineInput::CreateKey("M", 'M');
		GameEngineInput::CreateKey("P", 'P');
		GameEngineInput::CreateKey("F1", VK_F1);
		GameEngineInput::CreateKey("F2", VK_F2);
		GameEngineInput::CreateKey("F3", VK_F3);
		GameEngineInput::CreateKey("F4", VK_F4);
		GameEngineInput::CreateKey("F5", VK_F5);
		GameEngineInput::CreateKey("F6", VK_F6);
		GameEngineInput::CreateKey("F7", VK_F7);
		GameEngineInput::CreateKey("F8", VK_F8);
	}
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });
	//std::shared_ptr<GameEngineCoreWindow> Window = GameEngineGUI::FindGUIWindowConvert<GameEngineCoreWindow>("CoreWindow");
	GameEngineFont::Load("휴먼둥근헤드라인");
	Map1 = CreateActor<Map>();

	NewUIPannel = CreateActor<UIPannel>();
	NewMiniMap = CreateActor<MiniMap>();
	
	MiniViewRatio = MiniMapSize / MapSize;
	NewMiniMap->GetTransform()->SetLocalPosition(NewUIPannel->GetTransform()->GetLocalPosition());
	NewMiniMap->GetTransform()->AddLocalPosition({ -458.f,-27.f });
	NewMapOverlay = CreateActor<MapOverlay>();
	NewMapOverlay->GetTransform()->SetLocalPosition(MapUpP);
	NewDefenseMap = CreateActor<DefenseMap>();
	

	NewMapEditor = CreateActor<MapEditor>();
	NewMapEditor->CreateTileEditor(180, 180, TileScale);
	GlobalValue::Collision = std::make_shared<JPSCollision>();
	GlobalValue::Collision->Create(180, 180);

	NewDefenseMapEditor = CreateActor<DefenseMapEditor>();
	NewDefenseMapEditor->CreateTileEditor(30, 30, TileScale);
	DefenseGlobalValue::Collision = std::make_shared<JPSCollision>();
	DefenseGlobalValue::Collision->Create(30, 30);
	//NewDefenseMapEditor->Off();
	NewUIButton = CreateActor<UIButton>();
	NewUIButton->GetTransform()->SetLocalPosition(NewUIPannel->GetTransform()->GetLocalPosition());
	NewOptionsheet = CreateActor<Optionsheet>();
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

	NewMouse = CreateActor<Mouse>();
	NewBarrack = CreateActor<Barrack>();
	



	NewRuinObject = CreateActor<RuinObject>();
	NewRuinObject->GetTransform()->SetWorldPosition(MapEditor::ConvertTileXYToPos(130 , 130));
	NewRuinObject->SetTileCollsion();

	NewNormalObject1 = CreateActor<NormalObject1>();
	NewNormalObject1->GetTransform()->SetWorldPosition(MapEditor::ConvertTileXYToPos(110, 110));
	NewNormalObject1->SetTileCollsion();

	NewTreasureBox = CreateActor<TreasureBox>();
	NewTreasureBox->GetTransform()->SetWorldPosition(MapEditor::ConvertTileXYToPos(120, 120));
	NewTreasureBox->SetTileCollsion();

	NewGotoDefenseMapZone = CreateActor<GotoDefenseMapZone>();
	NewGotoDefenseMapZone->GetTransform()->SetWorldPosition(MapEditor::ConvertTileXYToPos(72, 70));
	GetMainCamera()->SetSortType(0, SortType::ZSort);
	GetCamera(100)->SetSortType(0, SortType::ZSort);
	NewObject = CreateActor<Object>(1);

	{
		GameEngineDirectory NewDir2;
		NewDir2.MoveParentToDirectory("ContentsBin");
		NewDir2.Move("ContentsBin");
		GameEngineFile NewFile = GameEngineFile(NewDir2.GetPlusFileName("InsideMonsterTargetPos.data").GetFullPath());
		GameEngineSerializer Ser;
		NewFile.LoadBin(Ser);
		Minion::InSideTargetPosLoad(Ser);
	}
	{
		GameEngineDirectory NewDir2;
		NewDir2.MoveParentToDirectory("ContentsBin");
		NewDir2.Move("ContentsBin");
		GameEngineFile NewFile = GameEngineFile(NewDir2.GetPlusFileName("OutsideMonsterTargetPos.data").GetFullPath());
		GameEngineSerializer Ser;
		NewFile.LoadBin(Ser);
		Minion::OutSideTargetPosLoad(Ser);
	}

	{
		GameEngineDirectory NewDir2;
		NewDir2.MoveParentToDirectory("ContentsBin");
		NewDir2.Move("ContentsBin");
		GameEngineFile NewFile = GameEngineFile(NewDir2.GetPlusFileName("DefenseMapIsMove.data").GetFullPath());
		GameEngineSerializer Ser;
		NewFile.LoadBin(Ser);
		NewDefenseMapEditor->Load(Ser);
	}
	{
		GameEngineDirectory NewDir2;
		NewDir2.MoveParentToDirectory("ContentsBin");
		NewDir2.Move("ContentsBin");
		GameEngineFile NewFile = GameEngineFile(NewDir2.GetPlusFileName("UnitsCreatePos.data").GetFullPath());
		GameEngineSerializer Ser;
		NewFile.LoadBin(Ser);
		NewBarrack->SummonPosLoad(Ser);
	}

	if (nullptr != NewMapEditor) {
		GameEngineDirectory NewDir2;
		NewDir2.MoveParentToDirectory("ContentsBin");
		NewDir2.Move("ContentsBin");
		GameEngineFile NewFile = GameEngineFile(NewDir2.GetPlusFileName("IsMoveSave444.data").GetFullPath());
		GameEngineSerializer Ser;
		NewFile.LoadBin(Ser);
		NewMapEditor->Load(Ser);
	}
	{
		GameEngineDirectory NewDir2;
		NewDir2.MoveParentToDirectory("ContentsBin");
		NewDir2.Move("ContentsBin");
		GameEngineFile NewFile = GameEngineFile(NewDir2.GetPlusFileName("DefenseMapRespawnPos.data").GetFullPath());
		GameEngineSerializer Ser;
		NewFile.LoadBin(Ser);
		NewBarrack->DoorPosLoad(Ser);
	}
	{
		GameEngineDirectory NewDir2;
		NewDir2.MoveParentToDirectory("ContentsBin");
		NewDir2.Move("ContentsBin");
		GameEngineFile NewFile = GameEngineFile(NewDir2.GetPlusFileName("RespawnPosSave.data").GetFullPath());
		GameEngineSerializer Ser;
		NewFile.LoadBin(Ser);
		NewBarrack->RespawnPosLoad(Ser);
	}
	MyField = Field::DefenseMap;	
	NewGameManager = CreateActor<GameManager>();
	
	GetMainCamera()->GetTransform()->SetLocalPosition(NewDefenseMap->GetTransform()->GetLocalPosition());
}

void PlayLevel::LevelChangeStart()
{
	GameEngineLevel::LevelChangeStart();
	
}

void PlayLevel::LevelChangeEnd()
{
	GameEngineLevel::LevelChangeEnd();
	
}