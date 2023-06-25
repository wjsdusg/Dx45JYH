#pragma once
#include "Minion.h"

// Ό³Έν :

class Gangsi : public Minion
{
public:
	// constrcuter destructer
	Gangsi();
	~Gangsi();

	// delete Function
	Gangsi(const Gangsi& _Other) = delete;
	Gangsi(Gangsi&& _Other) noexcept = delete;
	Gangsi& operator=(const Gangsi& _Other) = delete;
	Gangsi& operator=(Gangsi&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:





};

