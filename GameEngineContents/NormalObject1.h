#pragma once
#include "Building.h"

// Ό³Έν :

class NormalObject1 : public Building
{
public:
	friend class Optionsheet;
	// constrcuter destructer
	NormalObject1();
	~NormalObject1();

	// delete Function
	NormalObject1(const NormalObject1& _Other) = delete;
	NormalObject1(NormalObject1&& _Other) noexcept = delete;
	NormalObject1& operator=(const NormalObject1& _Other) = delete;
	NormalObject1& operator=(NormalObject1&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:

	



};

