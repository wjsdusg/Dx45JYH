#pragma once
#include "Hero.h"

// Ό³Έν :

class Wakizaka : public Hero
{
public:
	// constrcuter destructer
	Wakizaka();
	~Wakizaka();

	// delete Function
	Wakizaka(const Wakizaka& _Other) = delete;
	Wakizaka(Wakizaka&& _Other) noexcept = delete;
	Wakizaka& operator=(const Wakizaka& _Other) = delete;
	Wakizaka& operator=(Wakizaka&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:





};

