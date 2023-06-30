#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :

class Mouse : public GameEngineActor
{
	friend class Unit;
public:
	static Mouse* NewMainMouse;
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
	void GetMoveMark(float4 _Pos);
	
	std::shared_ptr<class GameEngineCollision> Collision;
	
protected:
	void Start();
	void Update(float _DeltaTime);
	void Render(float _DeltaTime);

private:
	std::shared_ptr<class GameEngineUIRenderer> Render0;
	std::shared_ptr<class GameEngineSpriteRenderer> MouseMarkRender;
	float4 MousePos = float4::Zero;
	CollisionData MouseData;
	float DoubleClickTimer= 0;
	std::shared_ptr<class Unit> CopyUnit = nullptr;
	bool AnimationEnd = false;

};

