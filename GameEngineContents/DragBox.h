#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :

class DragBox : public GameEngineActor
{
	friend class Mouse;
public:
	// constrcuter destructer
	DragBox();
	~DragBox();

	// delete Function
	DragBox(const DragBox& _Other) = delete;
	DragBox(DragBox&& _Other) noexcept = delete;
	DragBox& operator=(const DragBox& _Other) = delete;
	DragBox& operator=(DragBox&& _Other) noexcept = delete;
	inline void SetMousePos(float4 _Pos)
	{
		MousePos = _Pos;
	}
	inline void SetMouseMovePos(float4 _Pos)
	{
		MouseMovePos = _Pos;
	}
	bool AllCollision();
protected:
	void Start();
	void Update(float _DeltaTime);
	void Render(float _DeltaTime);
		
private:
	std::shared_ptr<class GameEngineSpriteRenderer> Render0;
	std::shared_ptr<class GameEngineCollision> Collision;
	float4 MousePos;
	float4 MouseMovePos;
	float Area=0;
	bool check = false;

};

