#include "PrecompileHeader.h"
#include "DefenseMapEditor.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineFontRenderer.h>
#include "DefenseMap.h"
#include "Mouse.h"
#include "Frog.h"
extern float4 TileScale;

DefenseMapEditor::DefenseMapEditor()
{

}

DefenseMapEditor::~DefenseMapEditor()
{
}

void DefenseMapEditor::Update(float _DeltaTime)
{
	float4 Pos = Mouse::NewMainMouse->Collision->GetTransform()->GetLocalPosition();
	Pos -= DefenseMap::MainDefenseMap->GetTransform()->GetWorldPosition();
	Pos.y -= DefenseMap::MainDefenseMap->Render0->GetTransform()->GetLocalScale().y / 2;
	if (true == Render0->IsUpdate())
	{
		float4 sd = PosToTilePos(Pos);
		Render0->GetTransform()->SetWorldPosition(sd);
	}
	FSM.Update(_DeltaTime);
	NewObject->GetTransform()->SetLocalPosition(GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition());

	if (0 < MoveMarks.size())
	{
		for (int i = 0; i < MoveMarks.size(); i++)
		{
			GameEngineDebug::DrawBox(GetLevel()->GetMainCamera().get(), MoveMarks[i]->GetTransform());
		}
	}
	{		
		
		std::string str3 = "MousePos" /*- DefenseMapPosition()*/ + Mouse::NewMainMouse->Collision->GetTransform()->GetLocalPosition().ToString();//Pos.ToString();;
		std::string_view MouseConvertTile = str3;
		FontRender0->SetText(MouseConvertTile);
	}
	{
		std::string str2 = "TileIndex: ";
		std::string str3 = std::to_string(GetTIleIndex(Pos));
		str2 += str3;
		std::string_view Index = str2;
		FontRender1->SetText(Index);
	}
	{
		std::string str2 = "PostoTilePos: ";
		std::string str3 = {};
		if (nullptr != GetDTileInfo(Pos))
		{
			str3 = GetDTileInfo(Pos)->Pos.ToString();
		}
		str2 += str3;
		std::string_view PostoTilePos = str2;
		FontRender2->SetText(PostoTilePos);
	}
	{
		std::string str2 = "XÁÂÇ¥: ";
		std::string str3 = std::to_string(x);
		str2 += str3;
		str3 = "  YÁÂÇ¥: ";
		str2 += str3;
		str3 = std::to_string(y);
		str2 += str3;
		str3 = "\n Ismove: ";
		str2 += str3;
		if (nullptr != GetDTileInfo(Pos) && true == GetDTileInfo(Pos)->IsMove)
		{
			str3 = "T";
		}
		else
		{
			str3 = "F";
		}
		str2 += str3;
		std::string_view Index = str2;
		FontRender3->SetText(Index);
	}

	if (5.0f < GetLiveTime())
	{
		for (std::pair<const __int64, std::list<MonsterData>>& Pair : MonsterWave)
		{
			TileXY MTileXY;
			MTileXY.XY = Pair.first;

			if (0 == Pair.second.size())
			{
				continue;
			}

			std::list<MonsterData>::iterator DataIter = Pair.second.begin();

			MonsterData MonsterIndex = *DataIter;

			CreateMonster(DTileInfos[MTileXY.Y][MTileXY.X].Pos, MonsterIndex);

			Pair.second.pop_front();
		}

		ResetLiveTime();
	}

}

void DefenseMapEditor::Start()
{
	if (nullptr == GameEngineSprite::Find("FOGWAR.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("FOGWAR.png").GetFullPath(), 3, 1);
	}
	Render0 = CreateComponent<GameEngineSpriteRenderer>();
	Render0->GetTransform()->SetLocalScale(TileScale);
	Render0->CreateAnimation({ "CurrentPos", "FOGWAR.png",0,1 });
	Render0->ChangeAnimation("CurrentPos");
	Render0->Off();
	FSMInit();
	NewObject = CreateComponent<GameEngineComponent>();

	{
		{
			FontRender0 = CreateComponent<GameEngineFontRenderer>();
			FontRender0->GetTransform()->SetParent(NewObject->GetTransform());
			FontRender0->SetFont("ÈÞ¸ÕµÕ±ÙÇìµå¶óÀÎ");
			FontRender0->SetScale({ 20.f });
			FontRender0->GetTransform()->SetLocalPosition({ -GameEngineWindow::GetScreenSize().x / 2, GameEngineWindow::GetScreenSize().y / 2 });
		}
		{
			FontRender1 = CreateComponent<GameEngineFontRenderer>();
			FontRender1->GetTransform()->SetParent(NewObject->GetTransform());
			FontRender1->SetFont("ÈÞ¸ÕµÕ±ÙÇìµå¶óÀÎ");
			FontRender1->SetScale({ 20.f });
			FontRender1->GetTransform()->SetLocalPosition({ -GameEngineWindow::GetScreenSize().x / 2, GameEngineWindow::GetScreenSize().y / 2 - 20 });
		}
		{
			FontRender2 = CreateComponent<GameEngineFontRenderer>();
			FontRender2->GetTransform()->SetParent(NewObject->GetTransform());
			FontRender2->SetFont("ÈÞ¸ÕµÕ±ÙÇìµå¶óÀÎ");
			FontRender2->SetScale({ 20.f });
			FontRender2->GetTransform()->SetLocalPosition({ -GameEngineWindow::GetScreenSize().x / 2, GameEngineWindow::GetScreenSize().y / 2 - 40 });
		}
		{
			FontRender3 = CreateComponent<GameEngineFontRenderer>();
			FontRender3->GetTransform()->SetParent(NewObject->GetTransform());
			FontRender3->SetFont("ÈÞ¸ÕµÕ±ÙÇìµå¶óÀÎ");
			FontRender3->SetScale({ 20.f });
			FontRender3->GetTransform()->SetLocalPosition({ -GameEngineWindow::GetScreenSize().x / 2, GameEngineWindow::GetScreenSize().y / 2 - 60 });
		}
	}
	TileXY StartTile;
	StartTile.X = 1;
	StartTile.Y = 3;
	for (size_t i = 0; i < 30; i++)
	{
		MonsterWave[StartTile.XY].push_back({0});
	}
}

void DefenseMapEditor::CreateMonster(float4 _Pos, MonsterData _MonsterIndex)
{
	std::shared_ptr<Frog> NewFrog = nullptr;
	switch (_MonsterIndex.Type)
	{
	case 0:		
		NewFrog=GetLevel()->CreateActor<Frog>();
		NewFrog->GetTransform()->SetWorldPosition(_Pos);
		break;

	default:		
		break;
	}
}

void DefenseMapEditor::CreateTileEditor(int _X, int _Y, const float4& _TileSize)
{
	TileSize = _TileSize;
	TileSize.z = 1.0f;
	TileSizeH = TileSize.half();

	MapCount.x = static_cast<float>(_X);
	MapCount.y = static_cast<float>(_Y);

	DTileInfos.resize(_Y);
	for (size_t y = 0; y < DTileInfos.size(); y++)
	{
		DTileInfos[y].resize(_X);
	}
	int num = 0;
	int X = -1;
	int Y = -1;
	for (size_t y = 0; y < DTileInfos.size(); y++)
	{
		for (size_t x = 0; x < DTileInfos[y].size(); x++)
		{
			float4 vPos;
			vPos.x = (x * TileSizeH.x) - (y * TileSizeH.x);
			vPos.y = -(x * TileSizeH.y) - (y * TileSizeH.y);
			vPos.y -= TileSizeH.y;
			vPos.y += DefenseMap::MainDefenseMap->GetTransform()->GetWorldPosition().y;
			vPos.x += DefenseMap::MainDefenseMap->GetTransform()->GetWorldPosition().x;
			vPos.y += DefenseMap::MainDefenseMap->Render0->GetTransform()->GetLocalScale().y / 2;
			DTileInfos[y][x].Pos = vPos;
			DTileInfos[y][x].Index = num;
			num++;
		}
	}
}

void DefenseMapEditor::Clear()
{
	DTileInfos.clear();
}

bool DefenseMapEditor::IsOver(int _X, int _Y) const
{
	if (0 > _X || MapCount.ix() <= _X)
	{
		return true;
	}

	if (0 > _Y || MapCount.iy() <= _Y)
	{
		return true;
	}

	return false;
}

size_t DefenseMapEditor::GetTIleIndex(const float4& _Pos)
{
	int X = -1;
	int Y = -1;
	X = static_cast<int>((_Pos.x / TileSizeH.x + -_Pos.y / TileSizeH.y) / 2);
	Y = static_cast<int>((-_Pos.y / TileSizeH.y - (_Pos.x / TileSizeH.x)) / 2);

	if (true == DTileInfos.empty())
	{		
		x = -1;
		y = -1;
		return -1;
	}

	// ÀÎµ¦½º ¿À¹ö
	if (true == IsOver(X, Y))
	{		
		x = -1;
		y = -1;
		return -1;
	}
	x = X;
	y = Y;
	return DTileInfos[Y][X].Index;
}

DTileInfo* DefenseMapEditor::GetDTileInfo(const float4& _Pos)
{
	int X = -1;
	int Y = -1;
	X = static_cast<int>((_Pos.x / TileSizeH.x + -_Pos.y / TileSizeH.y) / 2);
	Y = static_cast<int>((-_Pos.y / TileSizeH.y - (_Pos.x / TileSizeH.x)) / 2);

	if (true == DTileInfos.empty())
	{
		return nullptr;
	}
	// ÀÎµ¦½º ¿À¹ö
	if (true == IsOver(X, Y))
	{
		return nullptr;
	}
	return &DTileInfos[Y][X];
}
float4 DefenseMapEditor::PosToTilePos(float4 _Pos)
{
	int X = -1;
	int Y = -1;

	X = static_cast<int>((_Pos.x / TileSizeH.x + -_Pos.y / TileSizeH.y) / 2);
	Y = static_cast<int>((-_Pos.y / TileSizeH.y - (_Pos.x / TileSizeH.x)) / 2);

	if (X >= 0 && Y >= 0 && X < 30 && Y < 30)
	{
		return DTileInfos[Y][X].Pos;
	}
	else
	{
		return { static_cast<float>(Y),static_cast<float>(Y) };
	}


}

void DefenseMapEditor::FSMInit()
{
	FSM.CreateState(
		{ .Name = "IsMove",
		.Start = [this]()
		{
			Render0->On();
		},
		.Update = [this](float _DeltaTime)
		{
			if (GameEngineInput::IsUp("EngineMouseLeft"))
			{
				float4 Pos = Mouse::NewMainMouse->Collision->GetTransform()->GetLocalPosition();
				float4 CheckPos = Pos - DefenseMap::MainDefenseMap->GetTransform()->GetWorldPosition();
				CheckPos.y-= DefenseMap::MainDefenseMap->Render0->GetTransform()->GetLocalScale().y / 2;
				if (nullptr != GetDTileInfo(CheckPos))
				{
					GetDTileInfo(CheckPos)->IsMove = false;
					std::shared_ptr<GameEngineComponent> NewComponent = CreateComponent<GameEngineComponent>();
					NewComponent->GetTransform()->SetWorldPosition(PosToTilePos(CheckPos));
					NewComponent->GetTransform()->SetLocalScale({ 5.f,5.f,1.f });
					MoveMarks.push_back(NewComponent);
				}
			}

			if (GameEngineInput::IsUp("EngineMouseRight"))
			{
				float4 Pos = Mouse::NewMainMouse->Collision->GetTransform()->GetLocalPosition();
				float4 CheckPos = Pos - DefenseMap::MainDefenseMap->GetTransform()->GetWorldPosition();
				CheckPos.y -= DefenseMap::MainDefenseMap->Render0->GetTransform()->GetLocalScale().y / 2;
				if (false == GetDTileInfo(CheckPos)->IsMove)
				{
					float4 Tran = PosToTilePos(CheckPos);
					int Count = 0;
					for (int i = 0; i < MoveMarks.size(); i++)
					{
						if (Tran == MoveMarks[i]->GetTransform()->GetWorldPosition())
						{
							MoveMarks[i]->Death();
							MoveMarks[i] = nullptr;
							MoveMarks.erase(MoveMarks.begin() + Count);
							GetDTileInfo(CheckPos)->IsMove = true;
							break;
						}
						Count++;
					}
				}
			}
		},
		.End = [this]() 
		{
			Render0->Off();
		}
		}
	);
	FSM.CreateState(
		{ .Name = "Default",
		.Start = [this]() {},
		.Update = [this](float _DeltaTime) {}
		,
		.End = []() {}
		}
	);
	FSM.ChangeState("Default");
}


void DefenseMapEditor::Render(float _Delta)
{

}
void DefenseMapEditor::Save(GameEngineSerializer& _Ser)
{
	SaveNum = static_cast<int>(MoveMarks.size());
	_Ser.Write(SaveNum);
	for (int i = 0; i < MoveMarks.size(); i++)
	{
		MoveMarks[i]->GetTransform()->GetWorldPosition();
		MoveMarks[i]->GetTransform()->GetLocalScale();
		_Ser.Write(MoveMarks[i]->GetTransform()->GetWorldPosition().ix());
		_Ser.Write(MoveMarks[i]->GetTransform()->GetWorldPosition().iy());
		//_Ser.Write(MoveMarks[i]->GetTransform()->GetLocalScale().ix());
		//_Ser.Write(MoveMarks[i]->GetTransform()->GetLocalScale().iy());
		//_Ser.Write(MoveMarks[i]->GetTransform()->GetLocalScale().iz());
	}
}
void DefenseMapEditor::Load(GameEngineSerializer& _Ser)
{
	for (int i = 0; i < MoveMarks.size(); i++)
	{
		MoveMarks[i]->Death();
	}
	MoveMarks.clear();

	_Ser.Read(SaveNum);
	MoveMarks.resize(SaveNum);

	for (int i = 0; i < SaveNum; i++)
	{
		std::shared_ptr<class GameEngineComponent> NewComponent = CreateComponent<GameEngineComponent>();
		int x;
		int y;
		//int z;
		_Ser.Read(x);
		_Ser.Read(y);
		NewComponent->GetTransform()->SetWorldPosition({ static_cast<float>(x),static_cast<float>(y) });
		//_Ser.Read(x);
		//_Ser.Read(y);
		//_Ser.Read(z);
		NewComponent->GetTransform()->SetLocalScale({ 5.f,5.f,1.f});
		MoveMarks[i] = NewComponent;
		float4 CheckPos = NewComponent->GetTransform()->GetWorldPosition() - DefenseMap::MainDefenseMap->GetTransform()->GetWorldPosition();
		CheckPos.y -= DefenseMap::MainDefenseMap->Render0->GetTransform()->GetLocalScale().y / 2;
		GetDTileInfo(CheckPos)->IsMove = false;
		//_Ser.Read(static_cast<int>(Pos.x));


	}


}