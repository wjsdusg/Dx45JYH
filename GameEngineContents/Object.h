#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFSM.h>
#include <GameEngineCore/GameEngineButton.h>
// Ό³Έν :
class Object : public GameEngineActor
{
public:
	// constrcuter destructer
	Object();
	~Object();

	// delete Function
	Object(const Object& _Other) = delete;
	Object(Object&& _Other) noexcept = delete;
	Object& operator=(const Object& _Other) = delete;
	Object& operator=(Object&& _Other) noexcept = delete;

protected:
	virtual void Start() {}
	virtual void Update(float _DeltaTime) {}
	virtual void Render(float _DeltaTime) {}
	std::shared_ptr<class GameEngineSpriteRenderer> Render0;
	std::shared_ptr<class GameEngineSpriteRenderer> SelectionCircle;
	float Angle = 0.0f;
	std::shared_ptr<class GameEngineCollision> Collsion;
	std::shared_ptr<GameEngineButton> Button;
	GameEngineFSM FSM;
	bool IsClick = false;
	CollisionData MouseData;
private:




};

