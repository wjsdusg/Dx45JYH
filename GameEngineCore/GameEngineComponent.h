#pragma once
#include "GameEngineUpdateObject.h"

// ���� :
class GameEngineComponent : public GameEngineUpdateObject
{
	friend class GameEngineActor;

public:
	// constrcuter destructer
	GameEngineComponent();
	~GameEngineComponent();

	// delete Function
	GameEngineComponent(const GameEngineComponent& _Other) = delete;
	GameEngineComponent(GameEngineComponent&& _Other) noexcept = delete;
	GameEngineComponent& operator=(const GameEngineComponent& _Other) = delete;
	GameEngineComponent& operator=(GameEngineComponent&& _Other) noexcept = delete;

protected:

private:
	class GameEngineActor* Actor;

	void SetActor(class GameEngineActor* _Actor);

};

