#pragma once
#include "Object.h"
// ���� :

class Unit : public Object
{
	friend class DragBox;
	friend class Mouse;
public:
	// constrcuter destructer
	Unit();
	~Unit();

	// delete Function
	Unit(const Unit& _Other) = delete;
	Unit(Unit&& _Other) noexcept = delete;
	Unit& operator=(const Unit& _Other) = delete;
	Unit& operator=(Unit&& _Other) noexcept = delete;
	static std::vector<std::shared_ptr<Unit>> GetUnits();
	
	void SetIsClick(bool _Check)
	{
		IsClick = _Check;
	}
	bool GetIsClick()
	{
		return IsClick;
	}
protected:
	void Start();
	void Update(float _DeltaTime);
	virtual void Render(float _DeltaTime) {}
	float4 MovePointTowardsTarget(float4 _Pos1, float4 _Pos2, float _Speed, float _Delta);
	float4 MousePickPos = { 0,0 };
	float4 TargetPos = { 0,0 };
	float4 PrePos = { 0,0 };
	bool IsMove = false;
	bool IsFlip = false;
	bool AnimationEnd = false;
	bool IsHold = false;
	float Speed = 100.f;
	float attackRange = 0;
	float AngleBetween = 0;
	float PreAngle = 0;
	float AttackRange = 0;
	float AttackSpeed = 1.f;
	void StateInit() override;
	static std::vector<std::shared_ptr<Unit>> Units;
	std::shared_ptr<GameEngineCollision> TargetCol = nullptr;
private:
	

};

