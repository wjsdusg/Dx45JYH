#pragma once
#include "Minion.h"

// Ό³Έν :

class Gatpha : public Minion
{
public:
	// constrcuter destructer
	Gatpha();
	~Gatpha();

	// delete Function
	Gatpha(const Gatpha& _Other) = delete;
	Gatpha(Gatpha&& _Other) noexcept = delete;
	Gatpha& operator=(const Gatpha& _Other) = delete;
	Gatpha& operator=(Gatpha&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:





};

