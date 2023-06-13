#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineSprite.h"
#include <map>
#include "EngineContentRenderingStruct.h"

enum class TileMapMode
{
	Rect,
	Iso
};

class Tile
{
public:
	GameEngineSprite* Sprite;
	int Index = 0;
};

// ���� :
class GameEngineTileMapRenderer : public GameEngineRenderer
{
public:
	// constrcuter destructer
	GameEngineTileMapRenderer();
	~GameEngineTileMapRenderer();

	// delete Function
	GameEngineTileMapRenderer(const GameEngineTileMapRenderer& _Other) = delete;
	GameEngineTileMapRenderer(GameEngineTileMapRenderer&& _Other) noexcept = delete;
	GameEngineTileMapRenderer& operator=(const GameEngineTileMapRenderer& _Other) = delete;
	GameEngineTileMapRenderer& operator=(GameEngineTileMapRenderer&& _Other) noexcept = delete;

	ColorOption ColorOptionValue;

	void CreateTileMap(int _X, int _Y, const float4& _TileSize, TileMapMode Mode = TileMapMode::Rect);

	void Clear();

	void SetTile(int _X, int _Y, const std::string_view& _SpriteName = "Error", int _Index = 0);

	void SetTile(const float4& _Pos, const std::string_view& _SpriteName = "Error", int _Index = 0);

	bool IsOver(int _X, int _Y) const;

	inline float4 GetCount() const
	{
		return MapCount;
	}

	inline void TilemapCullingOn()
	{
		IsTilemapCulling = true;
	}

	inline void TilemapCullingOff()
	{
		IsTilemapCulling = false;
	}

protected:
	void Render(float _Delta) override;

private:
	bool IsTilemapCulling = false;

	std::vector<std::vector<Tile>> Tiles;
	float4 MapCount;
	float4 AtlasData;
	float4 TileSize;
	float4 TileSizeH;

	TileMapMode Mode = TileMapMode::Rect;

	void Start() override;
};

