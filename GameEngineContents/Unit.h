#pragma once
#include "Object.h"
// Ό³Έν :

class Unit : public Object
{
	friend class DragBox;
public:
	// constrcuter destructer
	Unit();
	~Unit();

	// delete Function
	Unit(const Unit& _Other) = delete;
	Unit(Unit&& _Other) noexcept = delete;
	Unit& operator=(const Unit& _Other) = delete;
	Unit& operator=(Unit&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime);
	virtual void Render(float _DeltaTime) {}
	float4 MovePointTowardsTarget(float4 _Pos1, float4 _Pos2, float _Speed, float _Delta);
	float4 MousePickPos = { 0,0 };
	float4 TargetPos = { 0,0 };
	bool IsMove = false;
	bool IsFlip = false;
	float Speed = 100.f;
	float attackRange = 0;
	float AngleBetween = 0;
	float PreAngle = 0;
	float AttackRange = 0;
	void StateInit() override;
	static std::vector<std::shared_ptr<Unit>> Units;
	std::shared_ptr<GameEngineCollision> TargetCol = nullptr;
private:
	
	static float DoubleClickTimer;

};

