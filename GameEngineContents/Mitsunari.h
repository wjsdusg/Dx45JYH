#pragma once
#include "Hero.h"

// Ό³Έν :

class Mitsunari : public Hero
{
public:
	// constrcuter destructer
	Mitsunari();
	~Mitsunari();

	// delete Function
	Mitsunari(const Mitsunari& _Other) = delete;
	Mitsunari(Mitsunari&& _Other) noexcept = delete;
	Mitsunari& operator=(const Mitsunari& _Other) = delete;
	Mitsunari& operator=(Mitsunari&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:





};

