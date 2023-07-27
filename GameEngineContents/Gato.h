#pragma once
#include "Hero.h"

// Ό³Έν :

class Gato : public Hero
{
public:
	// constrcuter destructer
	Gato();
	~Gato();

	// delete Function
	Gato(const Gato& _Other) = delete;
	Gato(Gato&& _Other) noexcept = delete;
	Gato& operator=(const Gato& _Other) = delete;
	Gato& operator=(Gato&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:





};

