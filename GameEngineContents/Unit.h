#pragma once
#include "Object.h"
// Ό³Έν :

class Unit : public Object
{
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
	virtual void Start() {}
	void Update(float _DeltaTime);
	virtual void Render(float _DeltaTime) {}
	float4 MovePointTowardsTarget(float4 _Pos1, float4 _Pos2, float _Speed, float _Delta);

	float4 MousePickPos = { 0,0 };
	bool IsMove = false;
private:




};

