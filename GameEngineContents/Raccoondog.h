#pragma once
#include "Minion.h"

// Ό³Έν :

class Raccoondog : public Minion
{
public:
	// constrcuter destructer
	Raccoondog();
	~Raccoondog();

	// delete Function
	Raccoondog(const Raccoondog& _Other) = delete;
	Raccoondog(Raccoondog&& _Other) noexcept = delete;
	Raccoondog& operator=(const Raccoondog& _Other) = delete;
	Raccoondog& operator=(Raccoondog&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:





};

