#pragma once
#include "Hero.h"

// Ό³Έν :

class Tokugawa : public Hero
{
public:
	// constrcuter destructer
	Tokugawa();
	~Tokugawa();

	// delete Function
	Tokugawa(const Tokugawa& _Other) = delete;
	Tokugawa(Tokugawa&& _Other) noexcept = delete;
	Tokugawa& operator=(const Tokugawa& _Other) = delete;
	Tokugawa& operator=(Tokugawa&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:





};

