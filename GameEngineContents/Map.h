#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Map : public GameEngineActor
{
public:
	// constrcuter destructer
	Map();
	~Map();

	// delete Function
	Map(const Map& _Other) = delete;
	Map(Map&& _Other) noexcept = delete;
	Map& operator=(const Map& _Other) = delete;
	Map& operator=(Map&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:
	
	std::shared_ptr<class GameEngineSpriteRenderer> Render0;
	std::shared_ptr<class GameEngineTileMapRenderer> TileMap;


};

