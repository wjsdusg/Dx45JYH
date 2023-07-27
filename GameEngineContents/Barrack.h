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
	void SummonPosLoad(GameEngineSerializer& _Ser);
protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:	

	int SaveNum = 0;
	std::vector<float4> SummonPos;
	std::vector<std::shared_ptr<Unit>> BarrackUnits;
	std::vector<int> LevelInfos;
	int leve = 0;
	void CreateUnit(int _Level);
	void Synthesis();
};

