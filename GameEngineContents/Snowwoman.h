#pragma once
#include "Minion.h"

// Ό³Έν :

class Snowwoman : public Minion
{
public:
	// constrcuter destructer
	Snowwoman();
	~Snowwoman();

	// delete Function
	Snowwoman(const Snowwoman& _Other) = delete;
	Snowwoman(Snowwoman&& _Other) noexcept = delete;
	Snowwoman& operator=(const Snowwoman& _Other) = delete;
	Snowwoman& operator=(Snowwoman&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:





};

