#pragma once
#include "Minion.h"

// Ό³Έν :

class SwordPirate : public Minion
{
public:
	// constrcuter destructer
	SwordPirate();
	~SwordPirate();

	// delete Function
	SwordPirate(const SwordPirate& _Other) = delete;
	SwordPirate(SwordPirate&& _Other) noexcept = delete;
	SwordPirate& operator=(const SwordPirate& _Other) = delete;
	SwordPirate& operator=(SwordPirate&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:





};

