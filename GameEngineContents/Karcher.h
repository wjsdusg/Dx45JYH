#pragma once
#include "Unit.h"

// Ό³Έν :

class Karcher : public Unit
{
public:
	friend class Optionsheet;
	// constrcuter destructer
	Karcher();
	~Karcher();

	// delete Function
	Karcher(const Karcher& _Other) = delete;
	Karcher(Karcher&& _Other) noexcept = delete;
	Karcher& operator=(const Karcher& _Other) = delete;
	Karcher& operator=(Karcher&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;
	static int AddHp;
	static int AddATK;
	static int AddShield;

private:
	
	std::shared_ptr<GameEngineComponent> TestComponent = nullptr;



};

