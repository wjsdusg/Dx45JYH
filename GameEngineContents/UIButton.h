#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFSM.h>
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
	
	static UIButton* MainUIButton;
protected:
	void Start();
	void Update(float _DeltaTime);
	void Render(float _DeltaTime);

private:
	std::shared_ptr<class GameEngineUIRenderer> Render0;
	std::shared_ptr<class GameEngineUIRenderer> Render1;
	std::shared_ptr<class GameEngineUIRenderer> Render2;
	std::shared_ptr<class GameEngineUIRenderer> Render3;
	std::shared_ptr<class GameEngineUIRenderer> Render4;
	std::shared_ptr<class GameEngineUIRenderer> Render5;
	
	std::shared_ptr<class GameEngineUIRenderer> ColRender;
	std::shared_ptr<class GameEngineCollision> Collision;
	std::shared_ptr<class GameEngineTileMapRenderer> TileMap;
	class GameEngineFSM FSM;
	void FSMInit();
	float x = 55.f;
	float y = 46.f;
	
	
};

