#include "PrecompileHeader.h"
#include "DefenseMapEditor.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineFontRenderer.h>
#include "GlobalValue.h"
#include <GameEngineBase/JPSCollision.h>
#include "Mouse.h"
#include "DefenseMap.h"
extern float4 TileScale;
extern float4 MapUpP;
float4 DefenseMapEditor::TileSizeH = float4::Zero;
std::vector<std::vector<DefenseTileInfo>> DefenseMapEditor::DefenseTileInfos;
std::vector<float4> DefenseMapEditor::RespawnPos;
DefenseMapEditor::DefenseMapEditor()
{
}

DefenseMapEditor::~DefenseMapEditor()
{
}

void DefenseMapEditor::Update(float _DeltaTime)
{
	float4 Pos = Mouse::NewMainMouse->Collision->GetTransform()->GetLocalPosition();
	float4 _Pos = ConvertPosToTileXY(Pos);
	Pos -= DefenseMap::MainDefenseMap->GetTransform()->GetWorldPosition();
	Pos.y-= DefenseMap::MainDefenseMap->Render0->GetTransform()->GetLocalScale().y / 2;
	
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
		std::string str3 = "MousePos-MapUpP " + Pos.ToString();;
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
		if (nullptr != GetDefenseTileInfo(Pos))
		{
			str3 = GetDefenseTileInfo(Pos)->Pos.ToString();
		}
		str2 += str3;
		std::string_view PostoTilePos = str2;
		FontRender2->SetText(PostoTilePos);
	}
	{

		
		std::string str2 = "X좌표: ";
		std::string str3 = std::to_string(x);
		str2 += str3;
		str3 = "  Y좌표: ";
		str2 += str3;
		str3 = std::to_string(y);
		str2 += str3;
		str3 = "\n Collison: ";
		str2 += str3;
		_Pos;
		bool sdaaa = DefenseGlobalValue::Collision->IsCollision(_Pos.ix(), _Pos.iy());
		if (true== sdaaa)
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
			FontRender0->SetFont("휴먼둥근헤드라인");
			FontRender0->SetScale({ 20.f });
			FontRender0->GetTransform()->SetLocalPosition({ -GameEngineWindow::GetScreenSize().x / 2, GameEngineWindow::GetScreenSize().y / 2 });
		}
		{
			FontRender1 = CreateComponent<GameEngineFontRenderer>();
			FontRender1->GetTransform()->SetParent(NewObject->GetTransform());
			FontRender1->SetFont("휴먼둥근헤드라인");
			FontRender1->SetScale({ 20.f });
			FontRender1->GetTransform()->SetLocalPosition({ -GameEngineWindow::GetScreenSize().x / 2, GameEngineWindow::GetScreenSize().y / 2 - 20 });
		}
		{
			FontRender2 = CreateComponent<GameEngineFontRenderer>();
			FontRender2->GetTransform()->SetParent(NewObject->GetTransform());
			FontRender2->SetFont("휴먼둥근헤드라인");
			FontRender2->SetScale({ 20.f });
			FontRender2->GetTransform()->SetLocalPosition({ -GameEngineWindow::GetScreenSize().x / 2, GameEngineWindow::GetScreenSize().y / 2 - 40 });
		}
		{
			FontRender3 = CreateComponent<GameEngineFontRenderer>();
			FontRender3->GetTransform()->SetParent(NewObject->GetTransform());
			FontRender3->SetFont("휴먼둥근헤드라인");
			FontRender3->SetScale({ 20.f });
			FontRender3->GetTransform()->SetLocalPosition({ -GameEngineWindow::GetScreenSize().x / 2, GameEngineWindow::GetScreenSize().y / 2 - 60 });
		}
	}
}

void DefenseMapEditor::CreateTileEditor(int _X, int _Y, const float4& _TileSize)
{
	TileSize = _TileSize;
	TileSize.z = 1.0f;
	TileSizeH = TileSize.half();

	MapCount.x = static_cast<float>(_X);
	MapCount.y = static_cast<float>(_Y);


	DefenseTileInfos.resize(_Y);
	for (size_t y = 0; y < DefenseTileInfos.size(); y++)
	{
		DefenseTileInfos[y].resize(_X);
	}
	int num = 0;

	for (size_t y = 0; y < DefenseTileInfos.size(); y++)
	{
		for (size_t x = 0; x < DefenseTileInfos[y].size(); x++)
		{
			float4 vPos;
			vPos.x = (x * TileSizeH.x) - (y * TileSizeH.x);
			vPos.y = -(x * TileSizeH.y) - (y * TileSizeH.y);
			vPos.y -= TileSizeH.y;
			vPos += DefenseMap::MainDefenseMap->GetTransform()->GetWorldPosition();
			vPos.y += DefenseMap::MainDefenseMap->Render0->GetTransform()->GetLocalScale().y / 2;

			DefenseTileInfos[y][x].Pos = vPos;
			DefenseTileInfos[y][x].Index = num;
			num++;
		}
	}
}

void DefenseMapEditor::Clear()
{
	DefenseTileInfos.clear();
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

	if (true == DefenseTileInfos.empty())
	{
		//MsgAssert("CreateTileMap을 먼저 호출해주셔야 합니다.");
		x = -1;
		y = -1;
		return -1;
	}

	// 인덱스 오버
	if (true == IsOver(X, Y))
	{
		//MsgAssert("타일맵 크기를 초과해 접근하려 했습니다");
		x = -1;
		y = -1;
		return -1;
	}
	x = X;
	y = Y;
	return DefenseTileInfos[Y][X].Index;
}

DefenseTileInfo* DefenseMapEditor::GetDefenseTileInfo(const float4& _Pos)
{
	int X = -1;
	int Y = -1;
	X = static_cast<int>((_Pos.x / TileSizeH.x + -_Pos.y / TileSizeH.y) / 2);
	Y = static_cast<int>((-_Pos.y / TileSizeH.y - (_Pos.x / TileSizeH.x)) / 2);

	if (true == DefenseTileInfos.empty())
	{

		return nullptr;
	}
	// 인덱스 오버
	if (true == IsOver(X, Y))
	{
		return nullptr;
	}
	return &DefenseTileInfos[Y][X];
}
float4 DefenseMapEditor::PosToTilePos(float4 _Pos)
{
	int X = -1;
	int Y = -1;

	X = static_cast<int>((_Pos.x / TileSizeH.x + -_Pos.y / TileSizeH.y) / 2);
	Y = static_cast<int>((-_Pos.y / TileSizeH.y - (_Pos.x / TileSizeH.x)) / 2);

	if (X >= 0 && Y >= 0 && X < MapCount.x && Y < MapCount.y)
	{
		return DefenseTileInfos[Y][X].Pos;
	}
	else
	{
		//MsgAssert("말도안됨");
		return { static_cast<float>(Y),static_cast<float>(X) };
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
				CheckPos.y -= DefenseMap::MainDefenseMap->Render0->GetTransform()->GetLocalScale().y / 2;
				if (nullptr != GetDefenseTileInfo(CheckPos))
				{
					GetDefenseTileInfo(CheckPos)->IsMove = false;
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
				if (false == GetDefenseTileInfo(CheckPos)->IsMove)
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
							GetDefenseTileInfo(CheckPos)->IsMove = true;
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
		_Ser.Write(MoveMarks[i]->GetTransform()->GetWorldPosition().ix());
		_Ser.Write(MoveMarks[i]->GetTransform()->GetWorldPosition().iy());
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
	int x;
	int y;
	for (int i = 0; i < SaveNum; i++)
	{
		_Ser.Read(x);
		_Ser.Read(y);
		
		float4 CheckPos = ConvertPosToTileXY({ static_cast<float>(x), static_cast<float>(y) });
		
		DefenseGlobalValue::Collision->SetAt(CheckPos.ix(), CheckPos.iy());

	}
	DefenseGlobalValue::JpsP.Init(DefenseGlobalValue::Collision);
}

void DefenseMapEditor::RespawnPosLoad(GameEngineSerializer& _Ser)
{
	_Ser.Read(SaveNum);
	int x;
	int y;
	RespawnPos.resize(SaveNum);
	for (int i = 0; i < SaveNum; i++)
	{

		_Ser.Read(x);
		_Ser.Read(y);

		float4 CheckPos = ConvertPosToTileXY({ static_cast<float>(x), static_cast<float>(y) });

		RespawnPos[i] = CheckPos;
	}
}

float4 DefenseMapEditor::ConvertPosToTileXY(float4 _Pos)
{
	float4 CheckPos = _Pos - DefenseMap::MainDefenseMap->GetTransform()->GetWorldPosition();
	CheckPos.y -= DefenseMap::MainDefenseMap->Render0->GetTransform()->GetLocalScale().y / 2;

	size_t X = -1;
	size_t Y = -1;
	X = static_cast<size_t>((CheckPos.x / TileSizeH.x + -CheckPos.y / TileSizeH.y) / 2.f);
	Y = static_cast<size_t>((-CheckPos.y / TileSizeH.y - (CheckPos.x / TileSizeH.x)) / 2.f);
	float4 Pos = { static_cast<float>(X) , static_cast<float>(Y) };
	return Pos;
}

float4 DefenseMapEditor::ConvertTileXYToPos(size_t _X, size_t _Y)
{
	if (0 > _X || 0 > _Y|| 30 <=_X|| 30 <= _Y)
	{
		return float4::Zero;
	}
	else
	{
		
		return DefenseTileInfos[_Y][_X].Pos;

	}
}

float4  DefenseMapEditor::ConvertPosToTilePos(float4 _Pos)
{
	float4 CheckPos = _Pos -DefenseMap::MainDefenseMap->GetTransform()->GetWorldPosition();
	CheckPos.y -= DefenseMap::MainDefenseMap->Render0->GetTransform()->GetLocalScale().y / 2;

	size_t X = -1;
	size_t Y = -1;
	X = static_cast<size_t>((CheckPos.x / TileSizeH.x + -CheckPos.y / TileSizeH.y) / 2.f);
	Y = static_cast<size_t>((-CheckPos.y / TileSizeH.y - (CheckPos.x / TileSizeH.x)) / 2.f);
	if (X < 0 || Y < 0)
	{
		int a = 0;
	}
	return DefenseTileInfos[Y][X].Pos;
}