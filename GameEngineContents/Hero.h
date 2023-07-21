#pragma once
#include "Unit.h"
// Ό³Έν :

class Hero : public Unit
{
	
public:
	friend class Optionsheet;
	// constrcuter destructer
	Hero();
	~Hero();

	// delete Function
	Hero(const Hero& _Other) = delete;
	Hero(Hero&& _Other) noexcept = delete;
	Hero& operator=(const Hero& _Other) = delete;
	Hero& operator=(Hero&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime);
	virtual void Render(float _DeltaTime) {}
	static int AddHp;
	static int AddATK;
	static int AddShield;
private:



};

