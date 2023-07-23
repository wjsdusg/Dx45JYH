#pragma once
#include "Object.h"
#include "Unit.h"
// Ό³Έν :

class Building : public Object
{
	friend class DragBox;
	friend class Mouse;
	friend class UIButton;
	friend class PlayLevel;
	friend class Optionsheet;
public:
	// constrcuter destructer
	Building();
	~Building();

	// delete Function
	Building(const Building& _Other) = delete;
	Building(Building&& _Other) noexcept = delete;
	Building& operator=(const Building& _Other) = delete;
	Building& operator=(Building&& _Other) noexcept = delete;
	

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
	float4 TargetPos = { 0,0 };	
	void StateInit() override;	
	void SetTileCollsion();
	void ArrEnemyunit();
	std::shared_ptr<GameEngineCollision> TargetCol = nullptr;
	int IndexX = -1;
	int IndexY = -1;
	std::vector<float4> TileCollsionSetPos;
	std::vector<std::shared_ptr<Unit>> EnemyUnits;
	int EnemyNum = -1;
private:		
	float CalAngle(float4 _Pos1, float4 _Pos2);
		
	
};

