#pragma once
#include "Unit.h"

// Ό³Έν :

class Ksword : public Unit
{
public:
	friend class Optionsheet;
	
	// constrcuter destructer
	Ksword();
	~Ksword();

	// delete Function
	Ksword(const Ksword& _Other) = delete;
	Ksword(Ksword&& _Other) noexcept = delete;
	Ksword& operator=(const Ksword& _Other) = delete;
	Ksword& operator=(Ksword&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;
	static int AddHp;
	static int AddATK;
	static int AddShield;

private:

	std::shared_ptr<class GameEngineFontRenderer> FontRender0;



};

