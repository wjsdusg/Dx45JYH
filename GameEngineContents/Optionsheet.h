#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFSM.h>
// Ό³Έν :
class Optionsheet : public GameEngineActor
{
public:
	// constrcuter destructer
	Optionsheet();
	~Optionsheet();

	// delete Function
	Optionsheet(const Optionsheet& _Other) = delete;
	Optionsheet(Optionsheet&& _Other) noexcept = delete;
	Optionsheet& operator=(const Optionsheet& _Other) = delete;
	Optionsheet& operator=(Optionsheet&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:
	std::shared_ptr<class GameEngineUIRenderer> Render0;
	std::shared_ptr<class GameEngineUIRenderer> Render0Select;
	std::shared_ptr<class GameEngineFontUIRenderer> FontRender0;
	std::shared_ptr<class GameEngineUIRenderer> Render1;
	std::shared_ptr<class GameEngineUIRenderer> Render1Select;
	std::shared_ptr<class GameEngineFontUIRenderer> FontRender1;
	std::shared_ptr<class GameEngineUIRenderer> Render2;
	std::shared_ptr<class GameEngineUIRenderer> Render2Select;
	std::shared_ptr<class GameEngineFontUIRenderer> FontRender2;
	std::shared_ptr<class GameEngineUIRenderer> ColRender;
	std::shared_ptr<class GameEngineCollision> Collision;

	std::shared_ptr<class GameEngineComponent> NewObject;

	class GameEngineFSM FSM;
	void FSMInit();
	void FucntionsInit();
	std::vector<std::function<void()>> Functions;
	std::vector<std::string> OptionsString;
	std::vector<std::function<void()>> EpicFunctions;
	std::vector<std::string> EpicOptionsString;
	std::vector<int> Selectednumber;
	static int Count;
};

