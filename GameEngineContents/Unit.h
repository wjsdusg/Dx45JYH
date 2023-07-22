#pragma once
#include "Object.h"
#include <GameEngineBase/GameEngineAstar.h>
#include <GameEngineBase/JPSHeap.h>
// Ό³Έν :

class Unit : public Object
{
	friend class DragBox;
	friend class Mouse;
	friend class UIButton;
	friend class PlayLevel;
	friend class Optionsheet;
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
	float4 InterTargetPos = { 0,0 };
	float4 ShortTargetPos = { 0,0 };
	float4 PrePos = { 0,0 };
	bool IsMove = false;
	bool IsFlip = false;
	bool AnimationEnd = false;
	bool IsHold=false;
	bool IsA=false;
	bool IsM=false;
	bool IsP=false;
	float Speed = 100.f;	
	static float AddSpeed;
	float AngleBetween = 0;
	float PreAngle = 0;
	
	
	int UnitID = -1;
	void StateInit() override;
	static std::vector<std::shared_ptr<Unit>> Units;
	std::shared_ptr<GameEngineCollision> TargetCol = nullptr;
	int IndexX = -1;
	int IndexY = -1;
	float TestDistance;
private:
	std::list<PathIndex> PathResult;
	std::list<JPSCoord> JPSPathResult;
	std::list<float4> PathPos;
	
	void PathCal();
	float CalAngle(float4 _Pos1, float4 _Pos2);
	
	bool IsNextTileCollision();
	float4 ReturnIndexPlusPos();
	
};

