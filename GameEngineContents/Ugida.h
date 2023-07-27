#pragma once
#include "Hero.h"

// Ό³Έν :

class Ugida : public Hero
{
public:
	// constrcuter destructer
	Ugida();
	~Ugida();

	// delete Function
	Ugida(const Ugida& _Other) = delete;
	Ugida(Ugida&& _Other) noexcept = delete;
	Ugida& operator=(const Ugida& _Other) = delete;
	Ugida& operator=(Ugida&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:





};

