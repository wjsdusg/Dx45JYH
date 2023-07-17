#pragma once
#include "Minion.h"

// Ό³Έν :

class Ksword : public Minion
{
public:
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


private:

	std::shared_ptr<class GameEngineFontRenderer> FontRender0;



};

