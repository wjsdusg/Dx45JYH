#pragma once
#include "Minion.h"

// Ό³Έν :

class Onghwa : public Minion
{
public:
	// constrcuter destructer
	Onghwa();
	~Onghwa();

	// delete Function
	Onghwa(const Onghwa& _Other) = delete;
	Onghwa(Onghwa&& _Other) noexcept = delete;
	Onghwa& operator=(const Onghwa& _Other) = delete;
	Onghwa& operator=(Onghwa&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:





};

