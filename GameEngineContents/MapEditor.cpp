#include "PrecompileHeader.h"
#include "MapEditor.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "Mouse.h"
extern float4 TileScale;
MapEditor::MapEditor()
{
}

MapEditor::~MapEditor()
{
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
}

void MapEditor::Update(float _DeltaTime)
{
	float4 Pos= Mouse::NewMainMouse->Collision->GetTransform()->GetLocalPosition();
	float4 sd = PosToTilePos(Pos);
	Render0->GetTransform()->SetWorldPosition(sd);
  
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
			vPos.x = (x * TileSizeH.x) - (y * TileSizeH.x);
			vPos.y = -(x * TileSizeH.y) - (y * TileSizeH.y);
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

void MapEditor::Render(float _Delta)
{

}


size_t MapEditor::GetTIleIndex(const float4& _Pos)
{
	int X = -1;
	int Y = -1;
	X = static_cast<int>((_Pos.x / TileSizeH.x + -_Pos.y / TileSizeH.y) / 2);
	Y = static_cast<int>((-_Pos.y / TileSizeH.y - (_Pos.x / TileSizeH.x)) / 2);
	
	if (true == TileInfos.empty())
	{
		MsgAssert("CreateTileMap을 먼저 호출해주셔야 합니다.");
		return -1;
	}

	// 인덱스 오버
	if (true == IsOver(X, Y))
	{
		MsgAssert("타일맵 크기를 초과해 접근하려 했습니다");
		return -1;
	}
	
	return TileInfos[X][Y].Index;
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


