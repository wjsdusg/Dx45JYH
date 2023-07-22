#pragma once
#include "Building.h"

// Ό³Έν :

class RuinObject : public Building
{
public:
	friend class Optionsheet;
	// constrcuter destructer
	RuinObject();
	~RuinObject();

	// delete Function
	RuinObject(const RuinObject& _Other) = delete;
	RuinObject(RuinObject&& _Other) noexcept = delete;
	RuinObject& operator=(const RuinObject& _Other) = delete;
	RuinObject& operator=(RuinObject&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;
	

private:

	std::shared_ptr<class GameEngineFontRenderer> FontRender0;



};

