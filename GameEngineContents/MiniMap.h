#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class MiniMap : public GameEngineActor
{
public:
	// constrcuter destructer
	MiniMap();
	~MiniMap();

	// delete Function
	MiniMap(const MiniMap& _Other) = delete;
	MiniMap(MiniMap&& _Other) noexcept = delete;
	MiniMap& operator=(const MiniMap& _Other) = delete;
	MiniMap& operator=(MiniMap&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:

	std::shared_ptr<class GameEngineSpriteRenderer> Render0;



};

