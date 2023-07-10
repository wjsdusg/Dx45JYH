#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFSM.h>
#include <GameEngineCore/GameEngineButton.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineBase/GameEngineSerializer.h>
class DTileInfo
{
public:
	float4 Pos;
	size_t Index = 0;
	bool IsMove = true;
	bool ISMonsterCreate = false;

};
class MonsterData
{
public:
	int Type = 0;
};

union TileXY
{
public:
	struct
	{
		int X;
		int Y;
	};
	__int64 XY;
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

	void CreateTileEditor(int _X, int _Y, const float4& _TileSize);

	void Clear();

	size_t GetTIleIndex(const float4& _Pos);

	float4 PosToTilePos(float4 _Pos);

	DTileInfo* GetDTileInfo(const float4& _Pos);

	bool IsOver(int _X, int _Y) const;

	std::map<__int64, std::list<MonsterData>> MonsterWave;

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
protected:
	void Render(float _Delta) override;

private:
	bool IsTilemapCulling = false;

	std::vector<std::vector<DTileInfo>> DTileInfos;
	float4 MapCount;
	float4 TileSize;
	float4 TileSizeH;
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
	void CreateMonster(float4 _Pos,MonsterData _MonsterIndex);
	int x;
	int y;
	int SaveNum = 0;
};

