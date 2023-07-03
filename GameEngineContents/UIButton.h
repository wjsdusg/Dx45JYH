#pragma once

#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :

class UIButton : public GameEngineActor
{
	friend class PlayLevel;
public:
	// constrcuter destructer
	UIButton();
	~UIButton();

	// delete Function
	UIButton(const UIButton& _Other) = delete;
	UIButton(UIButton&& _Other) noexcept = delete;
	UIButton& operator=(const UIButton& _Other) = delete;
	UIButton& operator=(UIButton&& _Other) noexcept = delete;
	
protected:
	void Start();
	void Update(float _DeltaTime);
	void Render(float _DeltaTime);

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Render0;
	std::shared_ptr<class GameEngineCollision> Collision;
	std::shared_ptr<class GameEngineTileMapRenderer> TileMap;
};

