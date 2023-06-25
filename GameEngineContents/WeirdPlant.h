#pragma once
#include "Minion.h"

// Ό³Έν :

class WeirdPlant : public Minion
{
public:
	// constrcuter destructer
	WeirdPlant();
	~WeirdPlant();

	// delete Function
	WeirdPlant(const WeirdPlant& _Other) = delete;
	WeirdPlant(WeirdPlant&& _Other) noexcept = delete;
	WeirdPlant& operator=(const WeirdPlant& _Other) = delete;
	WeirdPlant& operator=(WeirdPlant&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:





};

