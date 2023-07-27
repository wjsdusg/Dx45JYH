#pragma once
#include "Hero.h"

// Ό³Έν :

class Seisho : public Hero
{
public:
	// constrcuter destructer
	Seisho();
	~Seisho();

	// delete Function
	Seisho(const Seisho& _Other) = delete;
	Seisho(Seisho&& _Other) noexcept = delete;
	Seisho& operator=(const Seisho& _Other) = delete;
	Seisho& operator=(Seisho&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:





};

