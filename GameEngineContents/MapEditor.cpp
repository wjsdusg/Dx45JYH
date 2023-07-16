#include "PrecompileHeader.h"
#include "MapEditor.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineFontRenderer.h>
#include "GlobalValue.h"
#include <GameEngineBase/JPSCollision.h>

#include "Mouse.h"
extern float4 TileScale;
extern float4 MapUpP;
float4 MapEditor::TileSizeH=float4::Zero;
std::vector<std::vector<TileInfo>> MapEditor::TileInfos;
MapEditor::MapEditor()
{
}

MapEditor::~MapEditor()
{
}

void MapEditor::Update(float _DeltaTime)
{
	float4 Pos= Mouse::NewMainMouse->Collision->GetTransform()->GetLocalPosition();
	float4 _Pos = ConvertPosToTileXY(Pos);
	Pos -= MapUpP;
	if (true==Render0->IsUpdate())
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
		//Pos -= MapUpP;
		std::string str3 = "MousePos-MapUpP " + Pos.ToString();;
		std::string_view MouseConvertTile = str3;
		FontRender0->SetText(MouseConvertTile);
	}
	{
		std::string str2 = "TileIndex: ";
		std::string str3 = std::to_string(GetTIleIndex(Pos));
		str2 += str3;
		std::string_view Index =str2;
		FontRender1->SetText(Index);
	}
	{		
		std::string str2 = "PostoTilePos: ";
		std::string str3 = {};
		if (nullptr != GetTIleInfo(Pos))
		{
			str3 = GetTIleInfo(Pos)->Pos.ToString();
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
		bool sdaaa = GlobalValue::Collision->IsCollision(_Pos.ix(), _Pos.iy());
		if (/*nullptr!= GetTIleInfo(Pos)&&true == GetTIleInfo(Pos)->IsMove*/GlobalValue::Collision->IsCollision(_Pos.ix(), _Pos.iy()))
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

void MapEditor::Start()
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

void MapEditor::CreateTileEditor(int _X, int _Y, const float4& _TileSize)
{
	TileSize = _TileSize;
	TileSize.z = 1.0f;
	TileSizeH = TileSize.half();

	MapCount.x = static_cast<float>(_X);
	MapCount.y = static_cast<float>(_Y);

	//GlobalValue::AStart.SetPathData({ 10, 10 }, -1);

	TileInfos.resize(_Y);
	for (size_t y = 0; y < TileInfos.size(); y++)
	{
		TileInfos[y].resize(_X);
	}
	int num = 0;
	
	for (size_t y = 0; y < TileInfos.size(); y++)
	{
		for (size_t x = 0; x < TileInfos[y].size(); x++)
		{
			float4 vPos;
			vPos.x = (x * TileSizeH.x) - (y * TileSizeH.x);
			vPos.y = -(x * TileSizeH.y) - (y * TileSizeH.y);
			vPos.y -= TileSizeH.y;
			vPos.y += MapUpP.y;		

			TileInfos[y][x].Pos = vPos;
			TileInfos[y][x].Index = num;
			num++;
		}
	}
}

void MapEditor::Clear()
{
	TileInfos.clear();
}

bool MapEditor::IsOver(int _X, int _Y) const
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

size_t MapEditor::GetTIleIndex(const float4& _Pos)
{
	int X = -1;
	int Y = -1;
	X = static_cast<int>((_Pos.x / TileSizeH.x + -_Pos.y / TileSizeH.y) / 2);
	Y = static_cast<int>((-_Pos.y / TileSizeH.y - (_Pos.x / TileSizeH.x)) / 2);
	
	if (true == TileInfos.empty())
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
	return TileInfos[Y][X].Index;
}

TileInfo* MapEditor::GetTIleInfo(const float4& _Pos)
{
	int X = -1;
	int Y = -1;
	X = static_cast<int>((_Pos.x / TileSizeH.x + -_Pos.y / TileSizeH.y) / 2);
	Y = static_cast<int>((-_Pos.y / TileSizeH.y - (_Pos.x / TileSizeH.x)) / 2);

	if (true == TileInfos.empty())
	{
		
		return nullptr;
	}
	// 인덱스 오버
	if (true == IsOver(X, Y))
	{		
		return nullptr;
	}
	return &TileInfos[Y][X];
}
float4 MapEditor::PosToTilePos(float4 _Pos)
{
	int X = -1;
	int Y = -1;
	
	X = static_cast<int>((_Pos.x / TileSizeH.x + -_Pos.y / TileSizeH.y) / 2);
	Y = static_cast<int>((-_Pos.y / TileSizeH.y - (_Pos.x / TileSizeH.x)) / 2);
	
	if (X >= 0 && Y >= 0&&X<180&&Y<180)
	{
		return TileInfos[Y][X].Pos;
	}
	else
	{
		return { static_cast<float>(Y),static_cast<float>(Y)};
	}


}

void MapEditor::FSMInit()
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
				float4 CheckPos= Pos - MapUpP;
				if (nullptr != GetTIleInfo(CheckPos))
				{
					GetTIleInfo(CheckPos)->IsMove = false;					
					std::shared_ptr<GameEngineComponent> NewComponent = CreateComponent<GameEngineComponent>();
					NewComponent->GetTransform()->SetWorldPosition(PosToTilePos(CheckPos));
					NewComponent->GetTransform()->SetLocalScale({ 5.f,5.f,1.f });
					MoveMarks.push_back(NewComponent);
				}
			}

			if (GameEngineInput::IsUp("EngineMouseRight"))
			{
				float4 Pos = Mouse::NewMainMouse->Collision->GetTransform()->GetLocalPosition();
				float4 CheckPos = Pos - MapUpP;
				if (false == GetTIleInfo(CheckPos)->IsMove)
				{					
					float4 Tran = PosToTilePos(CheckPos);
					int Count = 0;
					for (int i = 0; i < MoveMarks.size(); i++)
					{
						if (Tran == MoveMarks[i]->GetTransform()->GetWorldPosition())
						{
							MoveMarks[i]->Death();
							MoveMarks[i]=nullptr;
							MoveMarks.erase(MoveMarks.begin()+Count);
							GetTIleInfo(CheckPos)->IsMove = true;
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
		.Update =[this](float _DeltaTime){}
		,
		.End = []() {}
		}
	);
	FSM.ChangeState("Default");
}


void MapEditor::Render(float _Delta)
{

}
void MapEditor::Save(GameEngineSerializer& _Ser)
{
	SaveNum = MoveMarks.size();
	_Ser.Write(SaveNum);
	for (int i = 0; i < MoveMarks.size(); i++)
	{		
		_Ser.Write(MoveMarks[i]->GetTransform()->GetWorldPosition().ix());
		_Ser.Write(MoveMarks[i]->GetTransform()->GetWorldPosition().iy());	
	}
}
void MapEditor::Load(GameEngineSerializer& _Ser)
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
		
		_Ser.Read(x);
		_Ser.Read(y);
		NewComponent->GetTransform()->SetWorldPosition({ static_cast<float>(x),static_cast<float>(y) });		
		NewComponent->GetTransform()->SetLocalScale({5.f,5.f,1.f });
		MoveMarks[i]=NewComponent;
		float4 CheckPos = NewComponent->GetTransform()->GetWorldPosition() - MapUpP;
		GetTIleInfo(CheckPos)->IsMove = false;
				
		int X = -1;
		int Y = -1;
		X = static_cast<int>((CheckPos.x / TileSizeH.x + -CheckPos.y / TileSizeH.y) / 2);
		Y = static_cast<int>((-CheckPos.y / TileSizeH.y - (CheckPos.x / TileSizeH.x)) / 2);
		//GlobalValue::AStart.SetPathData({ X, Y }, -1);
		GlobalValue::Collision->SetAt(X, Y);		
		//_Ser.Read(static_cast<int>(Pos.x));		
	}
	GlobalValue::JpsP.Init(GlobalValue::Collision);
}

float4 MapEditor::ConvertPosToTileXY(float4 _Pos)
{
	float4 CheckPos= _Pos - MapUpP;

	int X = -1;
	int Y = -1;
	X = static_cast<int>((CheckPos.x / TileSizeH.x + -CheckPos.y / TileSizeH.y) / 2);
	Y = static_cast<int>((-CheckPos.y / TileSizeH.y - (CheckPos.x / TileSizeH.x)) / 2);
	float4 Pos = { static_cast<float>(X) , static_cast<float>(Y) };
	return Pos;
}

float4 MapEditor::ConvertTileXYToPos(size_t _X, size_t _Y)
{
	return TileInfos[_Y][_X].Pos;
}