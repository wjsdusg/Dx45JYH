#pragma once
#include "Unit.h"
// Ό³Έν :

class Minion : public Unit
{

public:
	// constrcuter destructer
	Minion();
	~Minion();

	// delete Function
	Minion(const Minion& _Other) = delete;
	Minion(Minion&& _Other) noexcept = delete;
	Minion& operator=(const Minion& _Other) = delete;
	Minion& operator=(Minion&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime);
	virtual void Render(float _DeltaTime) {}

private:



};

