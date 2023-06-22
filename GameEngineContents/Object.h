#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFSM.h>
#include <GameEngineCore/GameEngineButton.h>
#include "ContentsEnum.h"
#include "MapOverlay.h"
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
	bool IsClick = false;


protected:
	void Start();
	 void Update(float _DeltaTime);
	 void Render(float _DeltaTime) {}
	std::shared_ptr<class GameEngineSpriteRenderer> Render0;
	std::shared_ptr<class GameEngineSpriteRenderer> SelectionCircle;
	float Angle = 0.0f;
	std::shared_ptr<class GameEngineCollision> Collision;
	std::shared_ptr<class GameEngineCollision> FOVCollision;
	std::shared_ptr<GameEngineButton> Button;
	GameEngineFSM FSM;
	CollisionData MouseData;
	int Id;
	Team MyTeam = Team::Max;
	virtual void StateInit() {};
	float FOV = 300.f;
	float FightFOV = 300.f;
	static std::list<std::shared_ptr<Object>> Objects;
private:
	void ObjectsSetTile();


};

