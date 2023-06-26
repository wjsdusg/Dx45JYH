#pragma once
#include "Hero.h"

// Ό³Έν :

class Gonisi : public Hero
{
public:
	// constrcuter destructer
	Gonisi();
	~Gonisi();

	// delete Function
	Gonisi(const Gonisi& _Other) = delete;
	Gonisi(Gonisi&& _Other) noexcept = delete;
	Gonisi& operator=(const Gonisi& _Other) = delete;
	Gonisi& operator=(Gonisi&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:





};

