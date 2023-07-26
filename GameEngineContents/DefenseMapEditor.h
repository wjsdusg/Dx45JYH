#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFSM.h>
#include <GameEngineCore/GameEngineButton.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineBase/GameEngineSerializer.h>
class DefenseTileInfo
{
public:
	float4 Pos;
	size_t Index = 0;
	bool IsMove = true;
	bool ISMonsterCreate = false;

};
// Ό³Έν :
class DefenseMapEditor : public GameEngineActor
{
	friend class PlayLevel;
public:
	// constrcuter destructer
	DefenseMapEditor();
	~DefenseMapEditor();

	// delete Function
	DefenseMapEditor(const DefenseMapEditor& _Other) = delete;
	DefenseMapEditor(DefenseMapEditor&& _Other) noexcept = delete;
	DefenseMapEditor& operator=(const DefenseMapEditor& _Other) = delete;
	DefenseMapEditor& operator=(DefenseMapEditor&& _Other) noexcept = delete;

	static float4 ConvertPosToTileXY(float4 _Pos);

	static float4 ConvertTileXYToPos(size_t _X, size_t _Y);

	static float4 ConvertPosToTilePos(float4 _Pos);
	void CreateTileEditor(int _X, int _Y, const float4& _TileSize);

	void Clear();

	size_t GetTIleIndex(const float4& _Pos);


	DefenseTileInfo* GetDefenseTileInfo(const float4& _Pos);

	bool IsOver(int _X, int _Y) const;

	inline float4 GetCount() const
	{
		return MapCount;
	}
	inline void OnRender0()
	{
		Render0->On();
	}
	void Save(GameEngineSerializer& _Ser);
	void Load(GameEngineSerializer& _Ser);
	void RespawnPosLoad(GameEngineSerializer& _Ser);
	static std::vector<float4> RespawnPos;
protected:
	void Render(float _Delta) override;

private:
	float4 PosToTilePos(float4 _Pos);
	bool IsTilemapCulling = false;

	static std::vector<std::vector<DefenseTileInfo>> DefenseTileInfos;
	static float4 TileSizeH;
	float4 MapCount;
	float4 TileSize;
	void Start() override;
	void Update(float _DeltaTime) override;
	std::shared_ptr<class GameEngineSpriteRenderer> Render0;
	std::vector<std::shared_ptr<class GameEngineComponent>> MoveMarks;
	void FSMInit();
	class GameEngineFSM FSM;
	std::shared_ptr<class GameEngineComponent> NewObject;
	std::shared_ptr<class GameEngineFontRenderer> FontRender0;
	std::shared_ptr<class GameEngineFontRenderer> FontRender1;
	std::shared_ptr<class GameEngineFontRenderer> FontRender2;
	std::shared_ptr<class GameEngineFontRenderer> FontRender3;

	int x;
	int y;
	int SaveNum = 0;
};

