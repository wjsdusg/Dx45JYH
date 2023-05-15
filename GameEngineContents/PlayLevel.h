#pragma once
#include <GameEngineCore\GameEngineLevel.h>

// ���� :
class PlayLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	PlayLevel();
	~PlayLevel();

	// delete Function
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;

	std::shared_ptr<class GameEngineVideo> Video;

protected:
	void Update(float _DeltaTime) override;
	void Start() override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;


private:
	void PlayerCreate();


};

