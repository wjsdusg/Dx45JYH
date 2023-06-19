#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineUIRenderer;
class MiniMap : public GameEngineActor
{
	friend class PlayLevel;
	friend class Object;
public:
	// constrcuter destructer
	MiniMap();
	~MiniMap();

	// delete Function
	MiniMap(const MiniMap& _Other) = delete;
	MiniMap(MiniMap&& _Other) noexcept = delete;
	MiniMap& operator=(const MiniMap& _Other) = delete;
	MiniMap& operator=(MiniMap&& _Other) noexcept = delete;
	static  MiniMap* MainMiniMap;
protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:
	std::shared_ptr<class GameEngineUIRenderer> Render0;
	std::shared_ptr<class GameEngineUIRenderer> Render1;
	std::shared_ptr<class GameEngineUIRenderer> MiniMapOverlay;
	std::vector<std::shared_ptr<class GameEngineUIRenderer>> MiniPoints;

};

