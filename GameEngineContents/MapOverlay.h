#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :

class MapOverlay : public GameEngineActor
{
	friend class Object;
public:
	// constrcuter destructer
	MapOverlay();
	~MapOverlay();

	// delete Function
	MapOverlay(const MapOverlay& _Other) = delete;
	MapOverlay(MapOverlay&& _Other) noexcept = delete;
	MapOverlay& operator=(const MapOverlay& _Other) = delete;
	MapOverlay& operator=(MapOverlay&& _Other) noexcept = delete;
	std::map<std::shared_ptr<class GameEngineCollision>, std::shared_ptr<class GameEngineSpriteRenderer>> GetColNRenders()
	{
		return ColNRenders;
	}
protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:
	std::shared_ptr<class GameEngineSpriteRenderer> Render0;
	std::shared_ptr<class GameEngineTileMapRenderer> TileMap;
	 
	std::map<std::shared_ptr<class GameEngineCollision>, std::shared_ptr<class GameEngineSpriteRenderer>> ColNRenders;

	
};

