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
	friend class UIButton;
	friend class PlayLevel;
	friend class Optionsheet;
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
	void SetTeam(Team _Team)
	{
		MyTeam = _Team;
	}
	inline std::shared_ptr<class GameEngineCollision> GetCollsion()
	{
		return Collision;
	}
protected:
	void Start();
	void Update(float _DeltaTime);
	void Render(float _DeltaTime) {}
	void ObjectDeath();
	std::shared_ptr<class GameEngineSpriteRenderer> Render0;
	std::shared_ptr<class GameEngineSpriteRenderer> SelectionCircle;
	std::shared_ptr<class GameEngineCollision> Collision;
	std::shared_ptr<class GameEngineCollision> FOVCollision;
	std::shared_ptr<class GameEngineCollision> EnemyFOVCollision;
	
	GameEngineFSM FSM;
	
	float Angle = 0;
	Team MyTeam = Team::Max;
	Field MyField = Field::Max;
	virtual void StateInit() {};
	float FOV = 300.f;
	float FightFOV = 300.f;	
	static std::vector<std::shared_ptr<Object>> Objects;
	int HP = 0;
	int CurHp = 0;
	int ATK = 0;
	int Shield = 0;
	float AttackSpeed = 1.f;
	float AttackRange = 0;
	static int AddHp;
	static int AddATK;
	static float AddAttackSpeed;
	static float AddAttackRange;
	static int AddShield;
private:
	void ObjectsSetTile();


};

