#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class Ksword : public GameEngineActor
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

	std::shared_ptr<class GameEngineSpriteRenderer> Render0;



};

