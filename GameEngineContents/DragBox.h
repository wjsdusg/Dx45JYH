#pragma once
#include "DragBox.h"
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :

class DragBox : public GameEngineActor
{
	friend class PlayLevel;
public:
	// constrcuter destructer
	DragBox();
	~DragBox();

	// delete Function
	DragBox(const DragBox& _Other) = delete;
	DragBox(DragBox&& _Other) noexcept = delete;
	DragBox& operator=(const DragBox& _Other) = delete;
	DragBox& operator=(DragBox&& _Other) noexcept = delete;
	void SetMousePos(float4 _Pos)
	{
		MousePos = _Pos;
	}
	void SetMouseMovePos(float4 _Pos)
	{
		MouseMovePos = _Pos;
	}
	void AllCollision();
protected:
	void Start();
	void Update(float _DeltaTime);
	void Render(float _DeltaTime);
		
private:
	std::shared_ptr<class GameEngineSpriteRenderer> Render0;
	std::shared_ptr<class GameEngineCollision> Collision;
	float4 MousePos;
	float4 MouseMovePos;
	bool check = false;

};

