#pragma once
#include "Minion.h"

// Ό³Έν :

class Snowdemon : public Minion
{
public:
	// constrcuter destructer
	Snowdemon();
	~Snowdemon();

	// delete Function
	Snowdemon(const Snowdemon& _Other) = delete;
	Snowdemon(Snowdemon&& _Other) noexcept = delete;
	Snowdemon& operator=(const Snowdemon& _Other) = delete;
	Snowdemon& operator=(Snowdemon&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:





};

