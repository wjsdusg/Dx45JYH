#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class DefenseMap : public GameEngineActor
{
public:
	// constrcuter destructer
	DefenseMap();
	~DefenseMap();

	// delete Function
	DefenseMap(const DefenseMap& _Other) = delete;
	DefenseMap(DefenseMap&& _Other) noexcept = delete;
	DefenseMap& operator=(const DefenseMap& _Other) = delete;
	DefenseMap& operator=(DefenseMap&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:

	std::shared_ptr<class GameEngineSpriteRenderer> Render0;
	std::shared_ptr<class GameEngineTileMapRenderer> TileMap;


};

