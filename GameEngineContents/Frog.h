#pragma once
#include "Minion.h"

// Ό³Έν :

class Frog : public Minion
{
public:
	// constrcuter destructer
	Frog();
	~Frog();

	// delete Function
	Frog(const Frog& _Other) = delete;
	Frog(Frog&& _Other) noexcept = delete;
	Frog& operator=(const Frog& _Other) = delete;
	Frog& operator=(Frog&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:





};

