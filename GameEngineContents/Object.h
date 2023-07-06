#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFSM.h>
#include <GameEngineCore/GameEngineButton.h>
#include "ContentsEnum.h"
#include "MapOverlay.h"
// Ό³Έν :

class Object : public GameEngineActor
{
	friend class Mouse;
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

	inline std::shared_ptr<class GameEngineCollision> GetCollsion()
	{
		return Collision;
	}
protected:
	void Start();
	void Update(float _DeltaTime);
	void Render(float _DeltaTime) {}
	std::shared_ptr<class GameEngineSpriteRenderer> Render0;
	std::shared_ptr<class GameEngineSpriteRenderer> SelectionCircle;
	std::shared_ptr<class GameEngineCollision> Collision;
	std::shared_ptr<class GameEngineCollision> FOVCollision;
	std::shared_ptr<class GameEngineCollision> EnemyFOVCollision;
	std::shared_ptr<GameEngineButton> Button;
	GameEngineFSM FSM;
	
	float Angle = 0.0f;
	Team MyTeam = Team::Max;
	Field MyField = Field::Max;
	virtual void StateInit() {};
	float FOV = 300.f;
	float FightFOV = 300.f;
	
	static std::list<std::shared_ptr<Object>> Objects;
private:
	void ObjectsSetTile();


};

