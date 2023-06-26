#pragma once
#include "Hero.h"

// Ό³Έν :

class Asako : public Hero
{
public:
	// constrcuter destructer
	Asako();
	~Asako();

	// delete Function
	Asako(const Asako& _Other) = delete;
	Asako(Asako&& _Other) noexcept = delete;
	Asako& operator=(const Asako& _Other) = delete;
	Asako& operator=(Asako&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:





};

