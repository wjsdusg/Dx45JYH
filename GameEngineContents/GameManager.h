#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFSM.h>
#include <GameEngineCore/GameEngineButton.h>
#include "ContentsEnum.h"

// Ό³Έν :

class GameManager : public GameEngineActor
{
	
public:
	
	GameManager();
	~GameManager();

	// delete Function
	GameManager(const GameManager& _Other) = delete;
	GameManager(GameManager&& _Other) noexcept = delete;
	GameManager& operator=(const GameManager& _Other) = delete;
	GameManager& operator=(GameManager&& _Other) noexcept = delete;
	
protected:
	void Start();
	void Update(float _DeltaTime);
	void Render(float _DeltaTime) {}
	
	std::shared_ptr<class GameEngineUIRenderer> MoneyRender;
	std::shared_ptr<class GameEngineUIRenderer> MonsterRender;
	std::shared_ptr<class GameEngineFontUIRenderer> FontRender0;
	std::shared_ptr<class GameEngineUIRenderer> Render1;
	std::shared_ptr<class GameEngineUIRenderer> Render1Select;
	std::shared_ptr<class GameEngineFontUIRenderer> FontRender1;
	std::shared_ptr<class GameEngineFontUIRenderer> FontRender2;

	
private:
	void StateInit();
	GameEngineFSM FSM;
	int RandomNum=0;
	int num = 0;
	int Round = 1;

};

