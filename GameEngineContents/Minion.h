#pragma once
#include "Unit.h"
// Ό³Έν :

class Minion : public Unit
{
	friend class PlayLevel;

public:
	// constrcuter destructer
	Minion();
	~Minion();

	// delete Function
	Minion(const Minion& _Other) = delete;
	Minion(Minion&& _Other) noexcept = delete;
	Minion& operator=(const Minion& _Other) = delete;
	Minion& operator=(Minion&& _Other) noexcept = delete;
	static void OutSideTargetPosLoad(GameEngineSerializer& _Ser);
	static void InSideTargetPosLoad(GameEngineSerializer& _Ser);
	static int MinionNum;
protected:
	void Start();
	void Update(float _DeltaTime);
	virtual void Render(float _DeltaTime) {}
	static std::vector<float4> OutSideTargetPos;
	static std::vector<float4> InSideTargetPos;
private:
	std::vector<float4> MPathPos;
	void InsideStateInit();
	void OutsideStateInit();
	std::shared_ptr<class GameEngineFontRenderer> FontRender0;
	static bool IsOutside;
	
	static int GetMoney;
};

