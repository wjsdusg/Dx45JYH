#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :

class GotoDefenseMapZone : public GameEngineActor
{
public:
	
	GotoDefenseMapZone();
	~GotoDefenseMapZone();

	// delete Function
	GotoDefenseMapZone(const GotoDefenseMapZone& _Other) = delete;
	GotoDefenseMapZone(GotoDefenseMapZone&& _Other) noexcept = delete;
	GotoDefenseMapZone& operator=(const GotoDefenseMapZone& _Other) = delete;
	GotoDefenseMapZone& operator=(GotoDefenseMapZone&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:
	std::shared_ptr<class GameEngineSpriteRenderer> Render0;
	std::shared_ptr<class GameEngineCollision> Collision;
	float Time = 0;



};

