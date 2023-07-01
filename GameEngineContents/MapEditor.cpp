#include "PrecompileHeader.h"
#include "MapEditor.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineFontRenderer.h>

#include "Mouse.h"
extern float4 TileScale;
extern float4 MapUpP;
MapEditor::MapEditor()
{
}

MapEditor::~MapEditor()
{
}

void MapEditor::Update(float _DeltaTime)
{
	float4 Pos= Mouse::NewMainMouse->Collision->GetTransform()->GetLocalPosition();
	float4 sd = PosToTilePos(Pos);
	Render0->GetTransform()->SetWorldPosition(sd);

	FSM.Update(_DeltaTime);
	NewObject->GetTransform()->SetWorldPosition(GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition());
	MoveMarks;
	/*for (std::shared_ptr<class GameEngineComponent> NewComponent : MoveMarks)
	{
		GameEngineDebug::DrawBox(GetLevel()->GetMainCamera().get(), NewComponent->GetTransform());
	}*/
	for (int i = 0; i < MoveMarks.size(); i++)
	{
		GameEngineDebug::DrawBox(GetLevel()->GetMainCamera().get(), MoveMarks[i]->GetTransform());
	}
	
	{
		Pos -= MapUpP;
		std::string str3 = "MousePos " + Pos.ToString();;
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
		//
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
	GameEngineFont::Load("휴먼둥근헤드라인");
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
		FontRender1->GetTransform()->SetLocalPosition({ -GameEngineWindow::GetScreenSize().x / 2, GameEngineWindow::GetScreenSize().y / 2-20 });	
	}
	{
		FontRender2 = CreateComponent<GameEngineFontRenderer>();
		FontRender2->GetTransform()->SetParent(NewObject->GetTransform());
		FontRender2->SetFont("휴먼둥근헤드라인");
		FontRender2->SetScale({ 20.f });
		FontRender2->GetTransform()->SetLocalPosition({ -GameEngineWindow::GetScreenSize().x / 2, GameEngineWindow::GetScreenSize().y / 2 - 40 });
	}
}

void MapEditor::CreateTileEditor(int _X, int _Y, const float4& _TileSize)
{
	TileSize = _TileSize;
	TileSize.z = 1.0f;
	TileSizeH = TileSize.half();

	MapCount.x = static_cast<float>(_X);
	MapCount.y = static_cast<float>(_Y);

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
			vPos.x = (x * TileSizeH.x) - (y * TileSizeH.x)+GetTransform()->GetLocalPosition().x;
			vPos.y = -(x * TileSizeH.y) - (y * TileSizeH.y) + GetTransform()->GetLocalPosition().y;
			vPos.y -= TileSizeH.y;
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
		return -1;
	}

	// 인덱스 오버
	if (true == IsOver(X, Y))
	{
		//MsgAssert("타일맵 크기를 초과해 접근하려 했습니다");
		return -1;
	}
	
	return TileInfos[X][Y].Index;
}

TileInfo* MapEditor::GetTIleInfo(const float4& _Pos)
{
	int X = -1;
	int Y = -1;
	X = static_cast<int>((_Pos.x / TileSizeH.x + -_Pos.y / TileSizeH.y) / 2);
	Y = static_cast<int>((-_Pos.y / TileSizeH.y - (_Pos.x / TileSizeH.x)) / 2);

	if (true == TileInfos.empty())
	{
		//MsgAssert("CreateTileMap을 먼저 호출해주셔야 합니다.");
		return nullptr;
	}

	// 인덱스 오버
	if (true == IsOver(X, Y))
	{
		//MsgAssert("타일맵 크기를 초과해 접근하려 했습니다");
		return nullptr;
	}

	return &TileInfos[X][Y];
}
float4 MapEditor::PosToTilePos(float4 _Pos)
{
	int X = -1;
	int Y = -1;
	X = static_cast<int>((_Pos.x / TileSizeH.x + -_Pos.y / TileSizeH.y) / 2);
	Y = static_cast<int>((-_Pos.y / TileSizeH.y - (_Pos.x / TileSizeH.x)) / 2);
	float4 ReturnPos;
	ReturnPos.x = (X * TileSizeH.x) - (Y * TileSizeH.x);
	ReturnPos.y = -(X * TileSizeH.y) - (Y * TileSizeH.y);
	ReturnPos.y -= TileSizeH.y;
	
	return ReturnPos;

}

void MapEditor::FSMInit()
{
	FSM.CreateState(
		{ .Name = "IsMove",
		.Start = [this]() {},
		.Update = [this](float _DeltaTime)
		{			
			int a = 0;
			if (GameEngineInput::IsUp("EngineMouseLeft"))
			{
				float4 Pos = Mouse::NewMainMouse->Collision->GetTransform()->GetLocalPosition() - MapUpP;
				TileInfo NewTileInfo = *GetTIleInfo(Pos);
				NewTileInfo.IsMove = false;
				std::shared_ptr<GameEngineComponent> NewComponent = CreateComponent<GameEngineComponent>();
				NewComponent->GetTransform()->SetWorldPosition(PosToTilePos(Pos));
				NewComponent->GetTransform()->SetLocalScale({ 300.f,300.f,1.f });
				MoveMarks.push_back(NewComponent);
			}
		},
		.End = []() {}
		}
	);

	FSM.ChangeState("IsMove");
}



void MapEditor::Render(float _Delta)
{

}
