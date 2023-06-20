#pragma once
#include "Minion.h"

// Ό³Έν :

class Monster_01 : public Minion
{
public:
	// constrcuter destructer
	Monster_01();
	~Monster_01();

	// delete Function
	Monster_01(const Monster_01& _Other) = delete;
	Monster_01(Monster_01&& _Other) noexcept = delete;
	Monster_01& operator=(const Monster_01& _Other) = delete;
	Monster_01& operator=(Monster_01&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:





};

