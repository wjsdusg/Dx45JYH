#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class UIPannel : public GameEngineActor
{
public:
	// constrcuter destructer
	UIPannel();
	~UIPannel();

	// delete Function
	UIPannel(const UIPannel& _Other) = delete;
	UIPannel(UIPannel&& _Other) noexcept = delete;
	UIPannel& operator=(const UIPannel& _Other) = delete;
	UIPannel& operator=(UIPannel&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	
private:
	float Angle = 0.0f;
	std::shared_ptr<class GameEngineSpriteRenderer> Render0;
	

	std::shared_ptr<class GameEngineCollision> Collsion;

};

