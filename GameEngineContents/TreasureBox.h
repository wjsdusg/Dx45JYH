#pragma once
#include "Building.h"

// Ό³Έν :

class TreasureBox : public Building
{
public:
	friend class Optionsheet;
	// constrcuter destructer
	TreasureBox();
	~TreasureBox();

	// delete Function
	TreasureBox(const TreasureBox& _Other) = delete;
	TreasureBox(TreasureBox&& _Other) noexcept = delete;
	TreasureBox& operator=(const TreasureBox& _Other) = delete;
	TreasureBox& operator=(TreasureBox&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:
	int Gage = 0;
	float RealGage = 0;



};

