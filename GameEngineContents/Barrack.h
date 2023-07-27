#pragma once
#include "Building.h"

// Ό³Έν :

class Barrack : public Building
{
public:
	friend class Optionsheet;
	// constrcuter destructer
	Barrack();
	~Barrack();

	// delete Function
	Barrack(const Barrack& _Other) = delete;
	Barrack(Barrack&& _Other) noexcept = delete;
	Barrack& operator=(const Barrack& _Other) = delete;
	Barrack& operator=(Barrack&& _Other) noexcept = delete;
	static Barrack* MainBarrack;
	void SummonPosLoad(GameEngineSerializer& _Ser);
	void DoorPosLoad(GameEngineSerializer& _Ser);
	void TransunitToMap();
	void RespawnPosLoad(GameEngineSerializer& _Ser);
	void GotoDengeon();
protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:	

	int SaveNum = 0;
	std::vector<float4> SummonPos;
	std::vector<std::shared_ptr<Unit>> BarrackUnits;
	std::vector<std::shared_ptr<Unit>> DoorUnits;
	std::vector<int> LevelInfos;
	std::vector<float4> DoorPos;
	std::vector<float4> RespawnPos;
	int leve = 0;
	void CreateUnit(int _Level);
	void Synthesis();
	std::shared_ptr<class GameEngineSpriteRenderer> DoorRender;
	std::shared_ptr<class GameEngineCollision> DoorCollision;
	void MoveDoorPos(std::shared_ptr<Unit> _CopyUnit);
};

