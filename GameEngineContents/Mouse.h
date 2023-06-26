#pragma once
#include "Mouse.h"
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :

class Mouse : public GameEngineActor
{
	
public:
	static Mouse* MainMouse;
	// constrcuter destructer
	Mouse();
	~Mouse();

	// delete Function
	Mouse(const Mouse& _Other) = delete;
	Mouse(Mouse&& _Other) noexcept = delete;
	Mouse& operator=(const Mouse& _Other) = delete;
	Mouse& operator=(Mouse&& _Other) noexcept = delete;
	float4 GetMousePos()
	{
		return MousePos;
	}
	
	
protected:
	void Start();
	void Update(float _DeltaTime);
	void Render(float _DeltaTime);

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Render0;
	std::shared_ptr<class GameEngineCollision> Collision;
	float4 MousePos = float4::Zero;
	

};

