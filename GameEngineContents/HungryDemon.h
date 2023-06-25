#pragma once
#include "Minion.h"

// Ό³Έν :

class HungryDemon : public Minion
{
public:
	// constrcuter destructer
	HungryDemon();
	~HungryDemon();

	// delete Function
	HungryDemon(const HungryDemon& _Other) = delete;
	HungryDemon(HungryDemon&& _Other) noexcept = delete;
	HungryDemon& operator=(const HungryDemon& _Other) = delete;
	HungryDemon& operator=(HungryDemon&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:





};

