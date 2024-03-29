#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class DefenseMap : public GameEngineActor
{
	friend class DefenseMapEditor;
public:
	// constrcuter destructer
	DefenseMap();
	~DefenseMap();

	// delete Function
	DefenseMap(const DefenseMap& _Other) = delete;
	DefenseMap(DefenseMap&& _Other) noexcept = delete;
	DefenseMap& operator=(const DefenseMap& _Other) = delete;
	DefenseMap& operator=(DefenseMap&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:
	static DefenseMap* MainDefenseMap;
	std::shared_ptr<class GameEngineSpriteRenderer> Render0;
	std::shared_ptr<class GameEngineUIRenderer> Render1;
	


};

