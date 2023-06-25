#pragma once
#include "Minion.h"

// Ό³Έν :

class Tiger : public Minion
{
public:
	// constrcuter destructer
	Tiger();
	~Tiger();

	// delete Function
	Tiger(const Tiger& _Other) = delete;
	Tiger(Tiger&& _Other) noexcept = delete;
	Tiger& operator=(const Tiger& _Other) = delete;
	Tiger& operator=(Tiger&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:





};

