#pragma once
#include <GameEngineCore\GameEngineLevel.h>
#include <GameEngineBase/GameEngineAstar.h>
#include "ContentsEnum.h"
// Ό³Έν :
class PlayLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	PlayLevel();
	~PlayLevel();
	static PlayLevel* MainPlayLevel;
	// delete Function
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;
	Field GetField()
	{
		return MyField;
	}
	void SetField(Field _Field)
	{
		MyField= _Field;
	}
protected:
	void Update(float _DeltaTime) override;
	void Start() override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;
	
private:
	void OutlineCheck(float4& _Pos);
	void PlayerCreate();
	Field MyField = Field::Max;

};

